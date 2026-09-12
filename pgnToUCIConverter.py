import io
import re
import chess.pgn

pgn = """1. e4 d5 2. exd5 Nf6 { B01 Scandinavian Defense: Modern Variation } 3. Bb5+ Nbd7 4. Nc3 a6 5. Be2 b5 6. Bf3 Rb8 7. d4 Bb7 8. a3 Nb6 9. Nge2 Nbxd5 10. Nxd5 Bxd5 11. Bxd5 Nxd5 12. Bg5 Qd7 13. O-O e6 14. Ng3 Be7 15. Bxe7 Nxe7 16. Qd3 Rd8 17. Rad1 Nc6 18. Qe3 O-O 19. Rd3 Qe7 20. Rb1 Rd5 21. f4 Rfd8 22. Rbd1 Na5 23. Ne4 Nc4 24. Qc1 Kf8 25. Nc5 e5 26. fxe5 Nxe5 27. R3d2 Ng4 28. g3 Qe3+ 29. Kg2 Qh6 30. Kg1 Rxd4 31. Nd3 c5 32. b3 c4 33. bxc4 bxc4 34. a4 Kg8 35. h3 Qxh3 36. Rg2 cxd3 37. Rxd3 Rxd3 38. cxd3 Re8 39. d4 Ne3 40. Rb2 Qxg3+ 41. Kh1 Nc4 42. Rc2 Re1+ 43. Qxe1 Qxe1+ 44. Kh2 Qh4+ 45. Kg1 Qe1+ 46. Kh2 Qh4+ 47. Kg1 Qe1+ 48. Kh2 { The game is a draw. } 1/2-1/2
"""

pgn = re.sub(r"\{[^}]*\}", "", pgn)

game = chess.pgn.read_game(io.StringIO(pgn))
board = game.board()

moves = []
for move in game.mainline_moves():
    moves.append(move.uci())
    board.push(move)

print("position startpos moves", " ".join(moves))