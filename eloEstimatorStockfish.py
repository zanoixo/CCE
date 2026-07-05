import subprocess
import sys
import os
import signal
import re
import threading
from datetime import datetime
from pathlib import Path

# ── Configuration ─────────────────────────────────────────────────────────────
REPO        = Path(__file__).parent.resolve()
ENGINE      = REPO / "bin/engine"
STOCKFISH   = "stockfish"
CUTECHESS   = "cutechess-cli"

TIME_CONTROL    = "st=1"  # fixed 5 seconds per move
GAMES_PER_MATCH = 100       # games per Elo level (more = more accurate)
CONCURRENCY     = 10        # parallel games

SF_LOW          = 1000     # lowest Stockfish Elo to test
SF_HIGH         = 3000     # highest Stockfish Elo to test
CONVERGE_RANGE  = 50       # stop when range is smaller than this
WIN_THRESHOLD   = 0.55     # score above this → CCE is stronger
LOSS_THRESHOLD  = 0.45     # score below this → CCE is weaker
# ─────────────────────────────────────────────────────────────────────────────

LOG_FILE = f"./eloEstimatorLogs/elo_result_{datetime.now().strftime('%Y%m%d_%H%M%S')}.log"

# ── Colours ───────────────────────────────────────────────────────────────────
USE_COLOR = sys.stdout.isatty()

def c(code, text):
    return f"\033[{code}m{text}\033[0m" if USE_COLOR else text

def bold(t):   return c("1",    t)
def cyan(t):   return c("0;36", t)
def green(t):  return c("0;32", t)
def yellow(t): return c("1;33", t)
def red(t):    return c("0;31", t)

# ── Logging ───────────────────────────────────────────────────────────────────
def log(msg=""):
    line = msg if isinstance(msg, str) else str(msg)
    print(line)
    clean = re.sub(r'\033\[[0-9;]*m', '', line)
    with open(LOG_FILE, "a") as f:
        f.write(clean + "\n")

def info(msg):  log(f"{cyan('[INFO]')}  {msg}")
def ok(msg):    log(f"{green('[ OK ]')}  {msg}")
def warn(msg):  log(f"{yellow('[WARN]')}  {msg}")
def err(msg):   log(f"{red('[ERR ]')}  {msg}")

# ── Subprocess handle (for Ctrl+C cleanup) ────────────────────────────────────
current_proc = None

def handle_signal(sig, frame):
    log()
    log("Interrupted — stopping...")
    if current_proc and current_proc.poll() is None:
        current_proc.terminate()
    sys.exit(1)

signal.signal(signal.SIGINT,  handle_signal)
signal.signal(signal.SIGTERM, handle_signal)

# ── Show board position for illegal-move games ────────────────────────────────
def show_illegal_positions(pgn_file: str, illegal_games: list):
    log()
    log(bold("── Illegal Move Details ──────────────────────────────────"))

    try:
        with open(pgn_file) as f:
            pgn_content = f.read()
    except FileNotFoundError:
        warn(f"PGN not found: {pgn_file}")
        return

    try:
        import chess
        import chess.pgn
        import io
        use_chess = True
    except ImportError:
        use_chess = False
        warn("Install python-chess for board display:  pip install chess")

    pgn_blocks = [b.strip() for b in re.split(r'(?=\[Event )', pgn_content) if b.strip()]

    for white_eng, black_eng, mv in illegal_games:
        log()
        log(red(f"ILLEGAL MOVE ({mv})  —  {white_eng} vs {black_eng}"))

        # Prefer block whose Termination header mentions "illegal"
        match_block = None
        for block in pgn_blocks:
            wm = re.search(r'\[White "([^"]+)"\]', block)
            bm = re.search(r'\[Black "([^"]+)"\]', block)
            tm = re.search(r'\[Termination "([^"]+)"\]', block)
            if wm and bm and wm.group(1) == white_eng and bm.group(1) == black_eng:
                if tm and 'illegal' in tm.group(1).lower():
                    match_block = block
                    break
                if match_block is None:
                    match_block = block  # fallback: first game between these two

        if not match_block:
            warn("  Could not find matching game in PGN.")
            continue

        if use_chess:
            try:
                game = chess.pgn.read_game(io.StringIO(match_block))
                board = game.board()
                for move in game.mainline_moves():
                    board.push(move)
                log(f"  Position before illegal move ({mv}):")
                log(str(board))
                log(f"  FEN: {board.fen()}")
            except Exception as e:
                warn(f"  python-chess error: {e}")
                use_chess = False

        if not use_chess:
            moves_m = re.search(r'\n\n(.+)', match_block, re.DOTALL)
            if moves_m:
                log(f"  Moves: {moves_m.group(1).strip()[:600]}")

        log(f"  Full PGN: {pgn_file}")


# ── Play a match and return (score, wdl_string) ───────────────────────────────
def play_match(sf_elo: int) -> tuple[float, str]:
    global current_proc

    cce_work_dir = str(ENGINE.parent.parent)
    pgn_file = str(LOG_FILE).replace(".log", f"_sf{sf_elo}.pgn")

    if TIME_CONTROL.startswith("st="):
        tc_args = ["-each", "proto=uci", TIME_CONTROL, "timemargin=2000"]
    else:
        tc_args = ["-each", "proto=uci", f"tc={TIME_CONTROL}", "timemargin=2000"]

    cmd = [
        str(CUTECHESS),
        "-engine", "name=CCE",           f"cmd={ENGINE}", f"dir={cce_work_dir}",
        "-engine", f"name=SF{sf_elo}",   f"cmd={STOCKFISH}",
                   "option.UCI_LimitStrength=true",
                   f"option.UCI_Elo={sf_elo}",
        *tc_args,
        "-games",  str(GAMES_PER_MATCH),
        "-rounds", "1",
        "-concurrency", str(CONCURRENCY),
        "-recover",
        "-pgnout", pgn_file,
    ]

    current_proc = subprocess.Popen(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,
    )

    output_lines = []
    game_re = re.compile(r'^Finished game (\d+)')
    illegal_games = []

    def stream():
        for line in current_proc.stdout:
            line = line.rstrip()
            output_lines.append(line)

            m = game_re.match(line)
            if not m:
                continue

            gnum      = m.group(1)
            players_m = re.search(r'\((\S+) vs (\S+)\)', line)
            result_m  = re.search(r'\): (1-0|0-1|1/2-1/2)', line)
            reason_m  = re.search(r'\{(.+?)\}', line)

            if players_m and result_m:
                white_eng = players_m.group(1)
                black_eng = players_m.group(2)
                result    = result_m.group(1)
                reason    = reason_m.group(1) if reason_m else ""

                illegal_m = re.search(r'[Ii]llegal move \((\S+)\)', reason)
                if illegal_m:
                    mv = illegal_m.group(1)
                    log(f"    {red(f'Game {gnum}/{GAMES_PER_MATCH}: ILLEGAL MOVE ({mv})')}  {{{reason}}}")
                    illegal_games.append((white_eng, black_eng, mv))
                elif result == "1-0":
                    winner = green(f"{white_eng} wins") if white_eng == "CCE" else red(f"{white_eng} wins")
                    log(f"    Game {gnum}/{GAMES_PER_MATCH}: {winner}  {{{reason}}}")
                elif result == "0-1":
                    winner = green(f"{black_eng} wins") if black_eng == "CCE" else red(f"{black_eng} wins")
                    log(f"    Game {gnum}/{GAMES_PER_MATCH}: {winner}  {{{reason}}}")
                else:
                    log(f"    Game {gnum}/{GAMES_PER_MATCH}: {cyan('Draw')}  {{{reason}}}")
            else:
                raw = re.search(r'\): (.+)$', line)
                log(f"    Game {gnum}/{GAMES_PER_MATCH}: {raw.group(1) if raw else line}")

    t = threading.Thread(target=stream, daemon=True)
    t.start()
    current_proc.wait()
    t.join()
    current_proc = None

    if illegal_games:
        show_illegal_positions(pgn_file, illegal_games)

    full_output = "\n".join(output_lines)

    # Parse final score line: "Score of CCE vs SF2000: 30 - 18 - 2  [0.620] 50"
    score_line = None
    for line in reversed(output_lines):
        if line.startswith("Score of CCE"):
            score_line = line
            break

    if not score_line:
        err("Could not find score line in cutechess-cli output.")
        err("Raw output:")
        log(full_output)
        sys.exit(1)

    score_match = re.search(r'\[([0-9.]+)\]', score_line)
    wdl_match   = re.search(r'(\d+ - \d+ - \d+)', score_line)

    if not score_match:
        err(f"Could not parse score from: {score_line}")
        sys.exit(1)

    score = float(score_match.group(1))
    wdl   = wdl_match.group(1) if wdl_match else "? - ? - ?"

    return score, wdl

# ── Main ──────────────────────────────────────────────────────────────────────
def main():

    log()
    log(bold("┌──────────────────────────────────────────┐"))
    log(bold("│        CCE  Elo  Estimator               │"))
    log(bold("└──────────────────────────────────────────┘"))
    log()
    info(f"Engine:       {ENGINE}")
    info(f"Stockfish:    {STOCKFISH}")
    info(f"Time control: {TIME_CONTROL}")
    info(f"Games/match:  {GAMES_PER_MATCH}")
    info(f"Search range: Elo {SF_LOW} – {SF_HIGH}")
    info(f"Log file:     {LOG_FILE}")
    log()

    low      = SF_LOW
    high     = SF_HIGH
    best_elo = (low + high) // 2
    history  = []

    iteration = 0
    while (high - low) > CONVERGE_RANGE:
        iteration += 1
        mid = (low + high) // 2

        log(bold(f"── Iteration {iteration} ──────────────────────────────────"))
        info(f"Range: [{low} – {high}]  →  testing Elo {mid}")
        info(f"Playing {GAMES_PER_MATCH} games, please wait...")

        score, wdl = play_match(mid)
        pct = score * 100
        history.append((mid, wdl, pct))

        if score > WIN_THRESHOLD:
            ok(   f"CCE scored {pct:.1f}% → stronger than SF {mid} → raising floor")
            low      = mid
            best_elo = mid
        elif score < LOSS_THRESHOLD:
            warn( f"CCE scored {pct:.1f}% → weaker than SF {mid}   → lowering ceiling")
            high     = mid
        else:
            ok(   f"CCE scored {pct:.1f}% → within target range (45–55%) → converged!")
            best_elo = mid
            break

        log()

    # ── Final report ──────────────────────────────────────────────────────────
    log()
    log(bold("┌──────────────────────────────────────────┐"))
    log(bold("│              RESULTS                     │"))
    log(bold("├──────────────────────────────────────────┤"))
    for sf_elo, wdl, pct in history:
        log(f"{bold('│')}  SF {sf_elo} : {wdl}  [{pct:.1f}%]")
    log(bold("├──────────────────────────────────────────┤"))
    log(f"{bold('│')}  {green(f'Estimated CCE Elo:  ~{best_elo}')}")
    log(f"{bold('│')}  Final range:        [{low} – {high}]")
    log(f"{bold('│')}  Total iterations:   {iteration}")
    log(f"{bold('│')}  Total games:        {iteration * GAMES_PER_MATCH}")
    log(bold("└──────────────────────────────────────────┘"))
    log()
    log(f"Full log saved to: {LOG_FILE}")

if __name__ == "__main__":
    main()