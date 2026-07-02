import io
import re
import chess.pgn

pgn = """ 1. e4 {4.9s} Nc6 {-0.34/22 5.0s} 2. d4 {4.9s} e6 {-0.58/23 5.0s} 3. Nc3 {4.9s}
d5 {-0.69/22 5.0s} 4. e5 {4.9s} Na5 {-0.79/22 5.0s} 5. Nf3 {4.9s}
c5 {-0.71/22 5.0s} 6. Bg5 {4.9s} Be7 {-0.73/22 5.0s} 7. Bxe7 {4.9s}
Qxe7 {-0.92/24 5.0s} 8. Nb5 {4.9s} Kf8 {-1.89/23 5.0s} 9. Nd6 {4.9s}
b6 {-1.87/23 5.0s} 10. c4 {4.9s} dxc4 {-2.01/24 5.0s} 11. dxc5 {4.9s}
Nh6 {-2.47/22 5.0s} 12. cxb6 {4.9s} axb6 {-1.67/22 5.0s} 13. Rc1 {4.9s}
g6 {-1.62/22 5.0s} 14. b4 {4.9s} cxb3 {-0.76/24 5.0s} 15. Nxc8 {4.9s}
Qb4+ {-0.77/24 5.0s} 16. Qd2 {4.9s} Qxd2+ {-0.71/25 5.0s} 17. Nxd2 {4.9s}
Kg7 {-0.72/24 5.0s} 18. Nxb6 {4.9s} Rab8 {-2.85/24 5.0s} 19. Nd7 {4.9s}
Rb7 {-2.60/22 5.0s} 20. Nc5 {4.9s} b2 {-3.90/21 5.0s} 21. Rb1 {4.9s}
Rb6 {-3.82/23 5.0s} 22. Be2 {4.9s} Rc6 {-3.88/22 5.0s} 23. Nd3 {4.9s}
Rd8 {-3.62/22 5.0s} 24. h3 {4.9s} g5 {-3.55/23 5.0s} 25. Nxb2 {4.9s}
Nf5 {-3.98/22 5.0s} 26. Nf3 {4.9s} Nd4 {-3.25/22 5.0s} 27. Rd1 {4.9s}
Nc2+ {-4.03/23 5.0s, White makes an illegal move: a9a9} 0-1"""

pgn = re.sub(r"\{[^}]*\}", "", pgn)

game = chess.pgn.read_game(io.StringIO(pgn))
board = game.board()

moves = []
for move in game.mainline_moves():
    moves.append(move.uci())
    board.push(move)

print("position startpos moves", " ".join(moves))