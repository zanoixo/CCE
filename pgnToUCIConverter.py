import io
import re
import chess.pgn

pgn = """1. Nf3 Nf6 2. Nc3 Nc6 { A05 Zukertort Opening } 3. d4 e6 4. e4 Bb4 5. d5 Nxe4 6. dxc6 Nxc3 7. Qd4 Nd5+ 8. c3 Be7 9. cxd7+ Bxd7 10. Qxg7 Bf6 11. Qh6 Nxc3 12. Be3 Nd5 13. O-O-O Qe7 14. Kb1 Nxe3 15. fxe3 O-O-O 16. Bd3 Bc6 17. Rhf1 Bxb2 18. Kxb2 Qb4+ 19. Kc1 Qc3+ 20. Kb1 Qb4+ 21. Kc1 Qc3+ 22. Kb1 Qb4+ 23. Kc1 { The game is a draw. } 1/2-1/2"""

pgn = re.sub(r"\{[^}]*\}", "", pgn)

game = chess.pgn.read_game(io.StringIO(pgn))
board = game.board()

moves = []
for move in game.mainline_moves():
    moves.append(move.uci())
    board.push(move)

print("position startpos moves", " ".join(moves))