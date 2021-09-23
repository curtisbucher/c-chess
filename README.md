<p align = "center">
  <img src="https://www.curtisbucher.com/uploads/mechanica_turk.jpeg" alt="The Mechanical Turk" />
</p>

<h6 align="center"> The mechanical turk, the world's "first" chess computer. In reality, the machine was a hoax.</h6>

<h1 align="center">C Chess</h1> <h3 align="center">or <i>Brothersbane</i> </h3> <p align="center"><i>A chess engine written in C, designed to demolish my brother in a chess match.</i> </p>

### Principles

To increase efficiency, as well as to provide additional challenge to myself, I am designing *Brothersbane* from the ground up to be as low-level as possible, squeezing the most possible function from the least number of operations. While the performance increase from such a goal is likely negligible, it provides interesting constraints on my implementation. In researching ways to implement such a chess algorithm, I came accross the concept of "bitboard representation."

#### Bitboard Representation

Brothersbane uses bitboard representation to store and manipulate the digital chessboard. Using bitboard representation, a chess board is represented as a series of 12 unsigned 64-bit integers, one integer for each of the six peices in both colors. Each bit of a 64 bit board "mask" represents a square of the chessboard. This is demonstrated in the image below.

<p align = "center">
  <img src="https://www.chessprogramming.org/images/3/37/Bitboard.gif" alt="Bitboard Representation" />
</p>

As you can see, each of the "bitboards" surrounding the chessboard corresponds to a peice and color on play area. While this bitboard representation may take up slightly more memory than other representations, its power comes from the board's ability to be manipulated efficienty with simple, 64-bit binary integer operations.

For example, let's say we wanted to move our D2 pawn to D4:
<p align = "center">
  <img src="https://backscattering.de/web-boardimage/board.svg?fen=rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR%20w%20KQkq%20-%200%201&orientation=white&lastMove=d2d4" alt="D2D4" />
</p>

All we would have to do would be to XOR our white pawn bitboard with a bitboard containing the starting and ending squares.

<p align = "center">
  <img width="30%" src="https://backscattering.de/web-boardimage/board.svg?fen=8/8/8/8/8/8/PPPPPPPP/8%20w%20-%20-%200%201&orientation=white"/> ^ 
  <img width="30%" src="https://backscattering.de/web-boardimage/board.svg?fen=8/8/8/8/8/8/8/8&orientation=white&lastMove=d2d4"/> = 
  <img width="30%" src="https://backscattering.de/web-boardimage/board.svg?fen=8/8/8/8/3P4/8/PPP1PPPP/8%20w%20-%20-%200%201&orientation=white" /> 
</p>

There are dozens of other clever setwise operations used to perform complex computation on a board state. As I progress, I hope to explain them all in detail, but for now many of them can be found at [www.chessprogramming.org](https://www.chessprogramming.org/General_Setwise_Operations).

### Progress

* Implemented bitboard representation, stores full board state (minus *En Passant f*or now)
* Implemented move generation functions for each peice using a variety of setwise operations. (minus *En Passant* and castling for now).
* Rudementary move generation picks randomly from list of possible moves, while I am working on a more sophisticated algorithm using alpha-beta pruning.

Currently, the game is playable but not very good. The rudementary AI picks a random move from a list of legal moves.

*Currently working on more sophisticated algorithm using alpha beta pruning.*

### Screenshots

![c-chess_ss](https://www.curtisbucher.com/uploads/c-chess_ss.png)

