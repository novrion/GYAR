#include "board.h"



// Make Move
void MakeMove(Board& b, Move& move) {

  b.board[move.to_x][move.to_y] = b.board[move.from_x][move.from_y];
  b.board[move.from_x][move.from_y] = 0;
}

// Undo Move
void UndoMove(Board& b, Move& move) {

  b.board[move.from_x][move.from_y] = b.board[move.to_x][move.to_y];
  b.board[move.to_x][move.to_y] = move.capture;
}



// Initialization
inline void IterateBoard(Board& b, const int kPosition[8][8]) {

  for (int x = 0; x < 8; ++x) {
    for (int y = 0; y < 8; ++y) {
      b.board[x][y] = kPosition[x][y];
    }
  }
}

void Board::Initialize(const int kBoardType, int kBoardIndex) {

  if (kBoardType == 0) {
    IterateBoard(*this, kBoardRegular[kBoardIndex]);
  }

  else if (kBoardType == 1) {
    IterateBoard(*this, kBoardTactic[kBoardIndex]);
  }

  else {
    IterateBoard(*this, kBoardSmall[kBoardIndex]);
  }
}