import io
import re
import chess.pgn

pgn = """[Event "rated blitz game"]
[Site "https://lichess.org/game/LbwOZpfo"]
[Date "2026.10.31"]
[Round "-"]
[White "CCE_V2"]
[Black "bfiedler-bot"]
[Result "1/2-1/2"]
[GameId "LbwOZpfo"]
[UTCDate "2026.10.31"]
[UTCTime "17:52:03"]
[WhiteElo "1923"]
[BlackElo "1864"]
[WhiteRatingDiff "-2"]
[BlackRatingDiff "+1"]
[WhiteTitle "BOT"]
[BlackTitle "BOT"]
[Variant "Standard"]
[TimeControl "60+4"]
[ECO "D02"]
[Opening "Queen's Pawn Game: Chigorin Variation"]
[Termination "Normal"]
[Annotator "lichess.org"]

1. Nf3 { [%clk 0:01:00] } 1... d5 { [%clk 0:01:00] } 2. d4 { [%clk 0:00:59] } 2... Nc6 { [%clk 0:00:59] } { D02 Queen's Pawn Game: Chigorin Variation } 3. Nc3 { [%clk 0:00:58] } 3... Nf6 { [%clk 0:00:58] } 4. Ne5 { [%clk 0:00:57] } 4... e6 { [%clk 0:00:57] } 5. Nxc6 { [%clk 0:00:56] } 5... bxc6 { [%clk 0:00:56] } 6. e3 { [%clk 0:00:55] } 6... Bd6 { [%clk 0:00:55] } 7. Bd3 { [%clk 0:00:54] } 7... O-O { [%clk 0:00:54] } 8. O-O { [%clk 0:00:52] } 8... e5 { [%clk 0:00:53] } 9. dxe5 { [%clk 0:00:51] } 9... Bxe5 { [%clk 0:00:52] } 10. Qd2 { [%clk 0:00:50] } 10... Bg4 { [%clk 0:00:51] } 11. f4 { [%clk 0:00:49] } 11... Bd6 { [%clk 0:00:51] } 12. f5 { [%clk 0:00:49] } 12... Bh5 { [%clk 0:00:50] } 13. h3 { [%clk 0:00:48] } 13... Bg3 { [%clk 0:00:49] } 14. Ne2 { [%clk 0:00:47] } 14... Bxe2 { [%clk 0:00:48] } 15. Qxe2 { [%clk 0:00:47] } 15... Qe7 { [%clk 0:00:47] } 16. Qf3 { [%clk 0:00:46] } 16... Be5 { [%clk 0:00:46] } 17. Rd1 { [%clk 0:00:46] } 17... Rad8 { [%clk 0:00:45] } 18. Rb1 { [%clk 0:00:45] } 18... Ne4 { [%clk 0:00:44] } 19. a3 { [%clk 0:00:45] } 19... Ng3 { [%clk 0:00:43] } 20. Bd2 { [%clk 0:00:44] } 20... Ne4 { [%clk 0:00:42] } 21. Bc1 { [%clk 0:00:44] } 21... Qh4 { [%clk 0:00:41] } 22. Ra1 { [%clk 0:00:44] } 22... a5 { [%clk 0:00:40] } 23. Ra2 { [%clk 0:00:44] } 23... Bg3 { [%clk 0:00:39] } 24. Be2 { [%clk 0:00:43] } 24... Bf2+ { [%clk 0:00:38] } 25. Kf1 { [%clk 0:00:43] } 25... Bg3 { [%clk 0:00:37] } 26. Kg1 { [%clk 0:00:43] } 26... c5 { [%clk 0:00:36] } 27. Bb5 { [%clk 0:00:43] } 27... Bf2+ { [%clk 0:00:36] } 28. Kf1 { [%clk 0:00:43] } 28... h6 { [%clk 0:00:35] } 29. Bc6 { [%clk 0:00:43] } 29... Nf6 { [%clk 0:00:34] } 30. b3 { [%clk 0:00:42] } 30... Ne4 { [%clk 0:00:33] } 31. Rd3 { [%clk 0:00:42] } 31... g6 { [%clk 0:00:32] } 32. c4 { [%clk 0:00:42] } 32... gxf5 { [%clk 0:00:31] } 33. cxd5 { [%clk 0:00:42] } 33... Bg3 { [%clk 0:00:30] } 34. Bb2 { [%clk 0:00:42] } 34... Qg5 { [%clk 0:00:29] } 35. Ba1 { [%clk 0:00:42] } 35... Qg6 { [%clk 0:00:28] } 36. Rc2 { [%clk 0:00:42] } 36... Rd6 { [%clk 0:00:27] } 37. Qd1 { [%clk 0:00:42] } 37... Rxc6 { [%clk 0:00:26] } 38. dxc6 { [%clk 0:00:42] } 38... Qxc6 { [%clk 0:00:25] } 39. Qf3 { [%clk 0:00:42] } 39... Qg6 { [%clk 0:00:24] } 40. Rc4 { [%clk 0:00:42] } 40... Kh7 { [%clk 0:00:24] } 41. Bc3 { [%clk 0:00:42] } 41... c6 { [%clk 0:00:23] } 42. Bxa5 { [%clk 0:00:42] } 42... Ra8 { [%clk 0:00:22] } 43. b4 { [%clk 0:00:42] } 43... Qe6 { [%clk 0:00:21] } 44. Rc1 { [%clk 0:00:42] } 44... Nf2 { [%clk 0:00:20] } 45. Rdc3 { [%clk 0:00:42] } 45... Ne4 { [%clk 0:00:19] } 46. R3c2 { [%clk 0:00:42] } 46... Qf6 { [%clk 0:00:18] } 47. Rd1 { [%clk 0:00:42] } 47... cxb4 { [%clk 0:00:17] } 48. Bxb4 { [%clk 0:00:41] } 48... Re8 { [%clk 0:00:16] } 49. Kg1 { [%clk 0:00:41] } 49... Qe6 { [%clk 0:00:15] } 50. Rdc1 { [%clk 0:00:41] } 50... Qe5 { [%clk 0:00:15] } 51. Bc3 { [%clk 0:00:41] } 51... Nxc3 { [%clk 0:00:14] } 52. Rxc3 { [%clk 0:00:41] } 52... f4 { [%clk 0:00:13] } 53. exf4 { [%clk 0:00:41] } 53... Bxf4 { [%clk 0:00:12] } 54. Rf1 { [%clk 0:00:41] } 54... Rd8 { [%clk 0:00:11] } 55. Kh1 { [%clk 0:00:41] } 55... Rd4 { [%clk 0:00:11] } 56. g3 { [%clk 0:00:41] } 56... Bg5 { [%clk 0:00:10] } 57. h4 { [%clk 0:00:41] } 57... Bxh4 { [%clk 0:00:10] } 58. Qxf7+ { [%clk 0:00:41] } 58... Qg7 { [%clk 0:00:09] } 59. Qxg7+ { [%clk 0:00:41] } 59... Kxg7 { [%clk 0:00:09] } 60. gxh4 { [%clk 0:00:41] } 60... Rxh4+ { [%clk 0:00:09] } 61. Kg2 { [%clk 0:00:41] } 61... Rd4 { [%clk 0:00:08] } 62. Rxc6 { [%clk 0:00:41] } 62... h5 { [%clk 0:00:08] } 63. Rb1 { [%clk 0:00:41] } 63... Rd7 { [%clk 0:00:08] } 64. Kh3 { [%clk 0:00:41] } 64... Ra7 { [%clk 0:00:08] } 65. Rb3 { [%clk 0:00:41] } 65... Rd7 { [%clk 0:00:07] } 66. Kh4 { [%clk 0:00:41] } 66... Rd4+ { [%clk 0:00:07] } 67. Kxh5 { [%clk 0:00:41] } 67... Rd5+ { [%clk 0:00:07] } 68. Kg4 { [%clk 0:00:41] } 68... Rd4+ { [%clk 0:00:07] } 69. Kf3 { [%clk 0:00:41] } 69... Rd7 { [%clk 0:00:07] } 70. Rb8 { [%clk 0:00:41] } 70... Rf7+ { [%clk 0:00:07] } 71. Ke4 { [%clk 0:00:41] } 71... Ra7 { [%clk 0:00:07] } 72. Kf4 { [%clk 0:00:41] } 72... Kf7 { [%clk 0:00:07] } 73. Kg5 { [%clk 0:00:41] } 73... Ra5+ { [%clk 0:00:06] } 74. Kh6 { [%clk 0:00:41] } 74... Ke7 { [%clk 0:00:06] } 75. Rb7+ { [%clk 0:00:41] } 75... Kd8 { [%clk 0:00:06] } 76. Rf6 { [%clk 0:00:41] } 76... Ke8 { [%clk 0:00:06] } 77. Rg6 { [%clk 0:00:41] } 77... Kf8 { [%clk 0:00:06] }



"""

pgn = re.sub(r"\{[^}]*\}", "", pgn)

game = chess.pgn.read_game(io.StringIO(pgn))
board = game.board()

moves = []
for move in game.mainline_moves():
    moves.append(move.uci())
    board.push(move)

print("position startpos moves", " ".join(moves))