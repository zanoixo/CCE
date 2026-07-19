import io
import re
import chess.pgn

pgn = """[Event "?"]
[Site "?"]
[Date "????.??.??"]
[Round "?"]
[White "?"]
[Black "?"]
[Result "*"]
[Link "https://www.chess.com/analysis/games"]

1. e4 {book} 1... e5 {book} 2. Nf3 {book} 2... Nc6 {book} 3. Bc4 {book} 3... Bc5
{book} 4. c3 {book} 4... Nf6 {book} 5. d3 {book} 5... d6 {book} 6. O-O {0.90s}
6... O-O {0.90s} 7. d4 {0.90s} 7... Bb6 {0.90s} 8. Re1 {0.90s} 8... exd4 {0.90s}
9. cxd4 {0.90s} 9... Bg4 {0.90s} 10. d5 {0.90s} 10... Ne5 {0.90s} 11. Nbd2
{0.90s} 11... Bxf3 {0.90s} 12. gxf3 {0.90s} 12... c6 {0.90s} 13. dxc6 {0.90s}
13... bxc6 {0.90s} 14. Be2 {0.90s} 14... Bc5 {0.90s} 15. Nb3 {0.90s} 15... Bb4
{0.90s} 16. Rf1 {0.90s} 16... Qe7 {0.90s} 17. a3 {0.90s} 17... Bc5 {0.90s} 18.
Nxc5 {0.90s} 18... dxc5 {0.90s} 19. Be3 {0.90s} 19... c4 {0.90s} 20. f4 {0.90s}
20... Ng6 {0.90s} 21. f5 {0.90s} 21... Ne5 {0.90s} 22. Qc2 {0.90s} 22... Rab8
{0.90s} 23. h3 {0.90s} 23... Nd3 {0.90s} 24. Qxc4 {0.90s} 24... Nxb2 {0.90s} 25.
Bc5 {0.90s} 25... Nxc4 {0.90s} 26. Bxe7 {0.90s} 26... Nd2 {0.90s} 27. Bxf8
{0.90s} 27... Rxf8 {0.90s} 28. Rfd1 {0.90s} 28... Ndxe4 {0.90s} 29. Rac1 {0.90s}
29... c5 {0.90s} 30. f3 {0.90s} 30... Ng3 {0.90s} 31. Bd3 {0.90s} 31... Rd8
{0.90s} 32. Rxc5 {0.90s} 32... Kf8 {0.90s} 33. Ra5 {0.90s} 33... Ngh5 {0.90s}
34. Be2 {0.90s} 34... Rxd1+ {0.90s} 35. Bxd1 {0.90s} 35... Ng3 {0.90s} 36. Kf2
{0.90s} 36... Ngh5 {0.90s} 37. Ke3 {0.90s} 37... a6 {0.90s} 38. f4 {0.90s} 38...
Ng3 {0.90s} 39. Bc2 {0.90s} 39... Ke7 {0.90s} 40. Bd3 {0.90s} 40... Ngh5 {0.90s}
41. Bxa6 {0.90s} 41... Nd7 {0.90s} 42. Bd3 {0.90s} 42... Nhf6 {0.90s} 43. Kd4
{0.90s} 43... Ne8 {0.90s} 44. Ra7 {0.90s} 44... Kd6 {0.90s} 45. Bc4 {0.90s}
45... Ke7 {0.90s} 46. Bd3 {0.90s} 46... Kd8 {0.90s} 47. h4 {0.90s} 47... Nd6
{0.90s} 48. Ra8+ {0.90s} 48... Kc7 {0.90s} 49. Rg8 {0.90s} 49... g6 {0.90s} 50.
fxg6 {0.90s} 50... hxg6 {0.90s} 51. Ra8 {0.90s} 51... Nb8 {0.90s} 52. Kc5
{0.90s} 52... Nd7+ {0.90s} 53. Kd4 {0.90s} 53... Nb8 {0.90s} 54. Kd5 {0.90s}
54... Nc8 {0.90s} 55. Kc5 {0.90s} 55... Nd7+ {0.90s} 56. Kd4 {0.90s} 56... Nd6
{0.90s} 57. Ra5 {0.90s} 57... Nf6 {0.90s} 58. Re5 {0.90s} 58... Kc6 {0.90s} 59.
Rc5+ {0.90s} 59... Kd7 {0.90s} 60. Re5 {0.90s} 60... Nh5 {0.90s} 61. f5 {0.90s}
61... Nf4 {0.90s} 62. fxg6 {0.90s} 62... fxg6 {0.90s} 63. Bc2 {0.90s} 63... Ne6+
{0.90s} 64. Kc3 {0.90s} 64... Nf4 {0.90s} 65. Rg5 {0.90s} 65... Ne2+ {0.90s} 66.
Kb4 {0.90s} 66... Nd4 {0.90s} 67. Bxg6 {0.90s} 67... Ke6 {0.90s} 68. h5 {0.90s}
68... Nc6+ {0.90s} 69. Kc5 {0.90s} 69... Ne7 {0.90s} 70. h6 {0.90s} 70... Kf6
{0.90s} 71. Kxd6 {0.90s} 71... Kxg5 {0.90s} 72. Kxe7 {0.90s} 72... Kxg6 {0.90s}
73. a4 {0.90s} 73... Kxh6 {0.90s} 74. a5 {0.90s} 74... Kg5 {0.90s} 75. a6
{0.90s} 75... Kf4 {0.90s} 76. a7 Ke3 {0.90s} 77. a8=Q Kd4 {0.90s} 78. Qf3 Kc4
79. Kd6 Kd4 80. Ke7 Kc4 81. Kd6 Kd4 82. Qb3 Ke4 83. Ke7 Kd4 84. Kd6 Ke4 85. Ke7
Kd4 86. Qb4+ Ke5 87. Qc4 Kf5 88. Qd3+ Ke5 89. Qc4 Kf5 90. Qd3+ Ke5 91. Kf7 Kf4
92. Ke8 Ke5 93. Ke7 Kf4 94. Kf7 Ke5 95. Ke7 Kf4 96. Kf7 Ke5 97. Kg7 Kf4 98. Kg6
Ke5 99. Kf7 Kf4 100. Ke8 Ke5 101. Qc4 Kd6 102. Kd8 Ke5 103. Ke8 Kd6 104. Kd8 Ke5
105. Qb3 Kf6 106. Qa2 Kg5 107. Ke7 Kg4 108. Qb3 Kf4 109. Qa3 Ke5 110. Qa8 Kd4
{0.68s} 111. Qa3 Kc4 112. Kd6 Kd4 113. Ke7 Kc4 114. Kd6 Kd4 115. Qf3 Kc4"""

pgn = re.sub(r"\{[^}]*\}", "", pgn)

game = chess.pgn.read_game(io.StringIO(pgn))
board = game.board()

moves = []
for move in game.mainline_moves():
    moves.append(move.uci())
    board.push(move)

print("position startpos moves", " ".join(moves))