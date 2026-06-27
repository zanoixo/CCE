import io
import re
import chess.pgn

pgn = """ 1. e3 {+0.41/14 0.15s} d5 2. d4 {+0.17/14 0.15s} Nc6 3. Nf3 {+0.49/14 0.15s} Nf6
4. Bb5 {+0.62/14 0.15s} Be6 5. b3 {+0.86/14 0.15s} Qd6 6. c4 {+1.61/14 0.15s}
dxc4 7. O-O {+2.39/15 0.15s, Black disconnects} 1-0"""

pgn = re.sub(r"\{[^}]*\}", "", pgn)

game = chess.pgn.read_game(io.StringIO(pgn))
board = game.board()

moves = []
for move in game.mainline_moves():
    moves.append(move.uci())
    board.push(move)

print("position startpos moves", " ".join(moves))