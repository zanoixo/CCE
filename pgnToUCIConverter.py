import io
import re
import chess.pgn

pgn = """1. e4 {book} e5 {book} 2. Nc3 {book} Nf6 {book} 3. f4 {book} d5 {book}
4. fxe5 {book} Nxe4 5. Nf3 Nc6 6. Bb5 Bb4 7. O-O O-O 8. Nxe4 dxe4 9. Bxc6 bxc6
10. c3 Bc5+ 11. d4 exd3+ 12. Kh1 Qd5 13. b4 Bb6 14. Bf4 Be6 15. Qd2 c5 16. Ng5
Bf5 17. Bg3 Bd7 18. Rf3 Bb5 19. a4 Bc4 20. a5 cxb4 21. axb6 bxc3 22. Qxc3 cxb6
23. Rf4 b5 24. Rd4 Qb7 25. Ne4 Rad8 26. Nd6 Qb6 27. Bf2 a6 28. Rd1 h6 29. Be3
Qb8 30. Nxc4 bxc4 31. Rxc4 Rfe8 32. Bd4 Rd5 33. Ra4 Qb5 34. Rb4 Qd7 35. Rxd3
Rexe5 36. Bxe5 Rxd3 37. Rb8+ Kh7 38. Qc2 Qd5 39. Rb6 g6 40. Kg1 Rd1+ 41. Kf2
Rd2+ 42. Qxd2 Qxd2+ 43. Kf1 Qd3+ 44. Kf2 Qd2+ 45. Kf1 Qd3+ 46. Kf2 f6 47. Bxf6
Qd5 48. Kf1 Qf5+ 49. Ke2 Qd5 50. Kf1 Kg8 51. h3 Qc4+ 52. Ke1 Qc5 53. Bd8 a5
54. Rxg6+ Kh7 55. Rf6 Qe3+ 56. Kf1 Qd3+ 57. Kg1 Qxd8 58. Rf7+ Kg6 59. Rf4 Qd6
60. Rg4+ Kf5 61. Kh1 a4 62. Rg8 a3 63. Ra8 Qd1+ 64. Kh2 Qd6+ 65. Kh1
Qd1+"""

pgn = re.sub(r"\{[^}]*\}", "", pgn)

game = chess.pgn.read_game(io.StringIO(pgn))
board = game.board()

moves = []
for move in game.mainline_moves():
    moves.append(move.uci())
    board.push(move)

print("position startpos moves", " ".join(moves))