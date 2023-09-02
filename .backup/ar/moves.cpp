#include "moves.h"

using namespace std;



void GenerateMoves(Board& b, Move moves[100], const bool kSide) {

  if (kSide) {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (b.board[x][y] == 0) continue;
        else if (b.board[x][y] == 1000) WPawnMoves(b, moves, x, y);
        else if (b.board[x][y] == 3000) WKnightMoves(b, moves, x, y);
        else if (b.board[x][y] == 3100) WBishopMoves(b, moves, x, y);
        else if (b.board[x][y] == 5000) WRookMoves(b, moves, x, y);
        else if (b.board[x][y] == 9000) WQueenMoves(b, moves, x, y);
        else if (b.board[x][y] == 100000) WKingMoves(b, moves, x, y);
      }
    }
  }

  else {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (b.board[x][y] == 0) continue;
        else if (b.board[x][y] == -1000) BPawnMoves(b, moves, x, y);
        else if (b.board[x][y] == -3000) BKnightMoves(b, moves, x, y);
        else if (b.board[x][y] == -3100) BBishopMoves(b, moves, x, y);
        else if (b.board[x][y] == -5000) BRookMoves(b, moves, x, y);
        else if (b.board[x][y] == -9000) BQueenMoves(b, moves, x, y);
        else if (b.board[x][y] == -100000) BKingMoves(b, moves, x, y);
      }
    }
  }
}



inline void AddMove(Move moves[100], Move move) {
  moves[moves[99].from_x++] = move;
}


inline void WPawnMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  if (kPosX + 1 < 8 && kPosY + 1 < 8 && b.board[kPosX + 1][kPosY + 1] < 0) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 1, b.board[kPosX + 1][kPosY + 1]));
  }
  if (kPosX - 1 > -1 && kPosY + 1 < 8 && b.board[kPosX - 1][kPosY + 1] < 0) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 1, b.board[kPosX - 1][kPosY + 1]));
  }

  if (kPosY + 1 < 8 && !b.board[kPosX][kPosY + 1]) {
    AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY + 1, 0));

    if (kPosY == 1 && !b.board[kPosX][kPosY + 2]) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY + 2, 0));
    }
  }
}
inline void WKnightMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  if (kPosX + 1 < 8 && kPosY + 2 < 8 && b.board[kPosX + 1][kPosY + 2] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 2, b.board[kPosX + 1][kPosY + 2]));
  }

  if (kPosX - 1 > -1 && kPosY + 2 < 8 && b.board[kPosX - 1][kPosY + 2] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 2, b.board[kPosX - 1][kPosY + 2]));
  }

  if (kPosX + 2 < 8 && kPosY + 1 < 8 && b.board[kPosX + 2][kPosY + 1] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 2, kPosY + 1, b.board[kPosX + 2][kPosY + 1]));
  }

  if (kPosX - 2 > -1 && kPosY + 1 < 8 && b.board[kPosX - 2][kPosY + 1] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 2, kPosY + 1, b.board[kPosX - 2][kPosY + 1]));
  }

  if (kPosX + 2 < 8 && kPosY - 1 > -1 && b.board[kPosX + 2][kPosY - 1] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 2, kPosY - 1, b.board[kPosX + 2][kPosY - 1]));
  }

  if (kPosX - 2 > -1 && kPosY - 1 > -1 && b.board[kPosX - 2][kPosY - 1] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 2, kPosY - 1, b.board[kPosX - 2][kPosY - 1]));
  }

  if (kPosX + 1 < 8 && kPosY - 2 > -1 && b.board[kPosX + 1][kPosY - 2] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 2, b.board[kPosX + 1][kPosY - 2]));
  }

  if (kPosX - 1 > -1 && kPosY - 2 > -1 && b.board[kPosX - 1][kPosY - 2] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 2, b.board[kPosX - 1][kPosY - 2]));
  }
}
inline void WBishopMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  // Up Right
  for (int x = kPosX + 1, y = kPosY + 1; x < 8 && y < 8; x++, y++) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Up Left
  for (int x = kPosX - 1, y = kPosY + 1; x > -1 && y < 8; x--, y++) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down Right
  for (int x = kPosX + 1, y = kPosY - 1; x < 8 && y > -1; x++, y--) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down Left
  for (int x = kPosX - 1, y = kPosY - 1; x > -1 && y > -1; x--, y--) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }
}
inline void WRookMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  // Up
  for (int y = kPosY + 1; y < 8; y++) {

    if (b.board[kPosX][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, 0));
    }

    else if (b.board[kPosX][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, b.board[kPosX][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down
  for (int y = kPosY - 1; y > -1; y--) {

    if (b.board[kPosX][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, 0));
    }

    else if (b.board[kPosX][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, b.board[kPosX][y]));
      break;
    }

    else {
      break;
    }
  }

  // Right
  for (int x = kPosX + 1; x < 8; x++) {

    if (b.board[x][kPosY] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, 0));
    }

    else if (b.board[x][kPosY] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, b.board[x][kPosY]));
      break;
    }

    else {
      break;
    }
  }

  // Left
  for (int x = kPosX - 1; x > -1; x--) {

    if (b.board[x][kPosY] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, 0));
    }

    else if (b.board[x][kPosY] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, b.board[x][kPosY]));
      break;
    }

    else {
      break;
    }
  }
}
inline void WQueenMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  // Up Right
  for (int x = kPosX + 1, y = kPosY + 1; x < 8 && y < 8; x++, y++) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Up Left
  for (int x = kPosX - 1, y = kPosY + 1; x > -1 && y < 8; x--, y++) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down Right
  for (int x = kPosX + 1, y = kPosY - 1; x < 8 && y > -1; x++, y--) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down Left
  for (int x = kPosX - 1, y = kPosY - 1; x > -1 && y > -1; x--, y--) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Up
  for (int y = kPosY + 1; y < 8; y++) {

    if (b.board[kPosX][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, 0));
    }

    else if (b.board[kPosX][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, b.board[kPosX][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down
  for (int y = kPosY - 1; y > -1; y--) {

    if (b.board[kPosX][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, 0));
    }

    else if (b.board[kPosX][y] < 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, b.board[kPosX][y]));
      break;
    }

    else {
      break;
    }
  }

  // Right
  for (int x = kPosX + 1; x < 8; x++) {

    if (b.board[x][kPosY] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, 0));
    }

    else if (b.board[x][kPosY] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, b.board[x][kPosY]));
      break;
    }

    else {
      break;
    }
  }

  // Left
  for (int x = kPosX - 1; x > -1; x--) {

    if (b.board[x][kPosY] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, 0));
    }

    else if (b.board[x][kPosY] < 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, b.board[x][kPosY]));
      break;
    }

    else {
      break;
    }
  }
}
inline void WKingMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  // Up
  if (kPosY + 1 < 8 && b.board[kPosX][kPosY + 1] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY + 1, b.board[kPosX][kPosY + 1]));
  }

  // Up Right
  if (kPosX + 1 < 8 && kPosY + 1 < 8 && b.board[kPosX + 1][kPosY + 1] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 1, b.board[kPosX + 1][kPosY + 1]));
  }

  // Up Left
  if (kPosX - 1 > -1 && kPosY + 1 < 8 && b.board[kPosX - 1][kPosY + 1] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 1, b.board[kPosX - 1][kPosY + 1]));
  }

  // Right
  if (kPosX + 1 < 8 && b.board[kPosX + 1][kPosY] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY, b.board[kPosX + 1][kPosY]));
  }

  // Left
  if (kPosX - 1 > -1 && b.board[kPosX - 1][kPosY] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY, b.board[kPosX - 1][kPosY]));
  }

  // Down
  if (kPosY - 1 > -1 && b.board[kPosX][kPosY - 1] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY - 1, b.board[kPosX][kPosY - 1]));
  }

  // Down Right
  if (kPosX + 1 < 8 && kPosY - 1 > -1 && b.board[kPosX + 1][kPosY - 1] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 1, b.board[kPosX + 1][kPosY - 1]));
  }

  // Down Left
  if (kPosX - 1 > -1 && kPosY - 1 > -1 && b.board[kPosX - 1][kPosY - 1] < 1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 1, b.board[kPosX - 1][kPosY - 1]));
  }
}

inline void BPawnMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  if (kPosX + 1 < 8 && kPosY - 1 > -1 && b.board[kPosX + 1][kPosY - 1] > 0) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 1, b.board[kPosX + 1][kPosY - 1]));
  }
  if (kPosX - 1 > -1 && kPosY - 1 > -1 && b.board[kPosX - 1][kPosY - 1] > 0) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 1, b.board[kPosX - 1][kPosY - 1]));
  }

  if (kPosY - 1 > -1 && !b.board[kPosX][kPosY - 1]) {
    AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY - 1, 0));

    if (kPosY == 6 && !b.board[kPosX][kPosY - 2]) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY - 2, 0));
    }
  }
}
inline void BKnightMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  if (kPosX + 1 < 8 && kPosY + 2 < 8 && b.board[kPosX + 1][kPosY + 2] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 2, b.board[kPosX + 1][kPosY + 2]));
  }

  if (kPosX - 1 > -1 && kPosY + 2 < 8 && b.board[kPosX - 1][kPosY + 2] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 2, b.board[kPosX - 1][kPosY + 2]));
  }

  if (kPosX + 2 < 8 && kPosY + 1 < 8 && b.board[kPosX + 2][kPosY + 1] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 2, kPosY + 1, b.board[kPosX + 2][kPosY + 1]));
  }

  if (kPosX - 2 > -1 && kPosY + 1 < 8 && b.board[kPosX - 2][kPosY + 1] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 2, kPosY + 1, b.board[kPosX - 2][kPosY + 1]));
  }

  if (kPosX + 2 < 8 && kPosY - 1 > -1 && b.board[kPosX + 2][kPosY - 1] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 2, kPosY - 1, b.board[kPosX + 2][kPosY - 1]));
  }

  if (kPosX - 2 > -1 && kPosY - 1 > -1 && b.board[kPosX - 2][kPosY - 1] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 2, kPosY - 1, b.board[kPosX - 2][kPosY - 1]));
  }

  if (kPosX + 1 < 8 && kPosY - 2 > -1 && b.board[kPosX + 1][kPosY - 2] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 2, b.board[kPosX + 1][kPosY - 2]));
  }

  if (kPosX - 1 > -1 && kPosY - 2 > -1 && b.board[kPosX - 1][kPosY - 2] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 2, b.board[kPosX - 1][kPosY - 2]));
  }
}
inline void BBishopMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  // Up Right
  for (int x = kPosX + 1, y = kPosY + 1; x < 8 && y < 8; x++, y++) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Up Left
  for (int x = kPosX - 1, y = kPosY + 1; x > -1 && y < 8; x--, y++) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down Right
  for (int x = kPosX + 1, y = kPosY - 1; x < 8 && y > -1; x++, y--) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down Left
  for (int x = kPosX - 1, y = kPosY - 1; x > -1 && y > -1; x--, y--) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }
}
inline void BRookMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  // Up
  for (int y = kPosY + 1; y < 8; y++) {

    if (b.board[kPosX][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, 0));
    }

    else if (b.board[kPosX][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, b.board[kPosX][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down
  for (int y = kPosY - 1; y > -1; y--) {

    if (b.board[kPosX][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, 0));
    }

    else if (b.board[kPosX][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, b.board[kPosX][y]));
      break;
    }

    else {
      break;
    }
  }

  // Right
  for (int x = kPosX + 1; x < 8; x++) {

    if (b.board[x][kPosY] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, 0));
    }

    else if (b.board[x][kPosY] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, b.board[x][kPosY]));
      break;
    }

    else {
      break;
    }
  }

  // Left
  for (int x = kPosX - 1; x > -1; x--) {

    if (b.board[x][kPosY] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, 0));
    }

    else if (b.board[x][kPosY] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, b.board[x][kPosY]));
      break;
    }

    else {
      break;
    }
  }
}
inline void BQueenMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  // Up Right
  for (int x = kPosX + 1, y = kPosY + 1; x < 8 && y < 8; x++, y++) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Up Left
  for (int x = kPosX - 1, y = kPosY + 1; x > -1 && y < 8; x--, y++) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down Right
  for (int x = kPosX + 1, y = kPosY - 1; x < 8 && y > -1; x++, y--) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down Left
  for (int x = kPosX - 1, y = kPosY - 1; x > -1 && y > -1; x--, y--) {

    if (b.board[x][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, 0));
    }

    else if (b.board[x][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, y, b.board[x][y]));
      break;
    }

    else {
      break;
    }
  }

  // Up
  for (int y = kPosY + 1; y < 8; y++) {

    if (b.board[kPosX][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, 0));
    }

    else if (b.board[kPosX][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, b.board[kPosX][y]));
      break;
    }

    else {
      break;
    }
  }

  // Down
  for (int y = kPosY - 1; y > -1; y--) {

    if (b.board[kPosX][y] == 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, 0));
    }

    else if (b.board[kPosX][y] > 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, y, b.board[kPosX][y]));
      break;
    }

    else {
      break;
    }
  }

  // Right
  for (int x = kPosX + 1; x < 8; x++) {

    if (b.board[x][kPosY] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, 0));
    }

    else if (b.board[x][kPosY] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, b.board[x][kPosY]));
      break;
    }

    else {
      break;
    }
  }

  // Left
  for (int x = kPosX - 1; x > -1; x--) {

    if (b.board[x][kPosY] == 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, 0));
    }

    else if (b.board[x][kPosY] > 0) {
      AddMove(moves, Move(kPosX, kPosY, x, kPosY, b.board[x][kPosY]));
      break;
    }

    else {
      break;
    }
  }
}
inline void BKingMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  // Up
  if (kPosY + 1 < 8 && b.board[kPosX][kPosY + 1] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY + 1, b.board[kPosX][kPosY + 1]));
  }

  // Up Right
  if (kPosX + 1 < 8 && kPosY + 1 < 8 && b.board[kPosX + 1][kPosY + 1] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 1, b.board[kPosX + 1][kPosY + 1]));
  }

  // Up Left
  if (kPosX - 1 > -1 && kPosY + 1 < 8 && b.board[kPosX - 1][kPosY + 1] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 1, b.board[kPosX - 1][kPosY + 1]));
  }

  // Right
  if (kPosX + 1 < 8 && b.board[kPosX + 1][kPosY] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY, b.board[kPosX + 1][kPosY]));
  }

  // Left
  if (kPosX - 1 > -1 && b.board[kPosX - 1][kPosY] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY, b.board[kPosX - 1][kPosY]));
  }

  // Down
  if (kPosY - 1 > -1 && b.board[kPosX][kPosY - 1] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY - 1, b.board[kPosX][kPosY - 1]));
  }

  // Down Right
  if (kPosX + 1 < 8 && kPosY - 1 > -1 && b.board[kPosX + 1][kPosY - 1] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 1, b.board[kPosX + 1][kPosY - 1]));
  }

  // Down Left
  if (kPosX - 1 > -1 && kPosY - 1 > -1 && b.board[kPosX - 1][kPosY - 1] > -1) {
    AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 1, b.board[kPosX - 1][kPosY - 1]));
  }
}