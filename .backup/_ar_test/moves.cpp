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



inline bool CastleDiagonalInCheck(Board& b, const int kPosX, const bool kSide) {

  if (kSide) {
    for (int x = kPosX, y = 0; x > -1 && y < 8; --x, ++y) {
      if (!b.board[x][y]) continue;
      else if (b.board[x][y] == -3000 || b.board[x][y] == -9000) return false;
      else break;
    }

    for (int x = kPosX, y = 0; x < 8 && y < 8; ++x, ++y) {
      if (!b.board[x][y]) continue;
      else if (b.board[x][y] == -3000 || b.board[x][y] == -9000) return false;
      else break;
    }

    for (int y = 0; y < 8; ++y) {
      if (!b.board[kPosX][y]) continue;
      else if (b.board[kPosX][y] == -5000 || b.board[kPosX][y] == -9000) return false;
      else break;
    }
  }

  else {
    for (int x = kPosX, y = 7; x > -1 && y > -1; --x, --y) {
      if (!b.board[x][y]) continue;
      else if (b.board[x][y] == 3000 || b.board[x][y] == 9000) return false;
      else break;
    }

    for (int x = kPosX, y = 7; x < 8 && y > -1; ++x, --y) {
      if (!b.board[x][y]) continue;
      else if (b.board[x][y] == 3000 || b.board[x][y] == 9000) return false;
      else break;
    }

    for (int y = 7; y > -1; --y) {
      if (!b.board[kPosX][y]) continue;
      else if (b.board[kPosX][y] == 5000 || b.board[kPosX][y] == 9000) return false;
      else break;
    }
  }

  return true;
}

inline void AddMove(Move moves[100], Move move) {
  moves[moves[99].from_x++] = move;
}


inline void WPawnMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  // Promotion
  if (kPosY == 6) {
    if (kPosX + 1 < 8 && b.board[kPosX + 1][kPosY + 1] < 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 1, b.board[kPosX + 1][kPosY + 1], false, false, 3000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 1, b.board[kPosX + 1][kPosY + 1], false, false, 3100, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 1, b.board[kPosX + 1][kPosY + 1], false, false, 5000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 1, b.board[kPosX + 1][kPosY + 1], false, false, 9000, 0));
    }
    if (kPosX - 1 > -1 && b.board[kPosX - 1][kPosY + 1] < 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 1, b.board[kPosX - 1][kPosY + 1], false, false, 3000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 1, b.board[kPosX - 1][kPosY + 1], false, false, 3100, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 1, b.board[kPosX - 1][kPosY + 1], false, false, 5000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 1, b.board[kPosX - 1][kPosY + 1], false, false, 9000, 0));
    }

    if (!b.board[kPosX][kPosY + 1]) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY + 1, 0, false, false, 3000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY + 1, 0, false, false, 3100, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY + 1, 0, false, false, 5000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY + 1, 0, false, false, 9000, 0));
    }
  }

  else {
    if (kPosX + 1 < 8 && b.board[kPosX + 1][kPosY + 1] < 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 1, b.board[kPosX + 1][kPosY + 1]));
    }
    if (kPosX - 1 > -1 && b.board[kPosX - 1][kPosY + 1] < 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 1, b.board[kPosX - 1][kPosY + 1]));
    }

    if (!b.board[kPosX][kPosY + 1]) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY + 1, 0));

      // Double Pawn Move
      if (kPosY == 1 && !b.board[kPosX][kPosY + 2]) {
        AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY + 2, 0, false, true, 0, 0));
      }
    }

    // En Passant
    if (b.en_passant_x != -1 && b.en_passant_y == kPosY) {
      if (kPosX == b.en_passant_x + 1) {
        AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY + 1, 1000, true, false, 0, 0));

      }
      else if (kPosX == b.en_passant_x - 1) {
        AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY + 1, 1000, true, false, 0, 0));
      }
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


  // Castle
  if (b.w_l_castle && !b.board[1][0] && !b.board[2][0] && !b.board[3][0]) {
    if (CastleDiagonalInCheck(b, 1, true) && CastleDiagonalInCheck(b, 2, true) && CastleDiagonalInCheck(b, 3, true) && CastleDiagonalInCheck(b, 4, true) &&
      !(b.board[0][1] == -1000 || b.board[1][1] == -1000 || b.board[2][1] == -1000 || b.board[3][1] == -1000 || b.board[4][1] == -1000 || b.board[5][1] == -1000) &&
      !(b.board[0][2] == -3000 || b.board[1][2] == -3000 || b.board[2][2] == -3000 || b.board[3][2] == -3000 || b.board[4][2] == -3000 || b.board[5][2] == -3000) &&
      !(b.board[0][1] == -3000 || b.board[1][1] == -3000 || b.board[2][1] == -3000 || b.board[3][1] == -3000 || b.board[4][1] == -3000 || b.board[5][1] == -3000 || b.board[6][1] == -3000) &&
      !(b.board[1][1] == -100000 || b.board[2][1] == -100000)) {

      AddMove(moves, Move(kPosX, kPosY, kPosX - 2, kPosY, 0, false, false, 0, 1));
    }
  }

  if (b.w_r_castle && !b.board[5][0] && !b.board[6][0]) {
    if (CastleDiagonalInCheck(b, 4, true) && CastleDiagonalInCheck(b, 5, true) && CastleDiagonalInCheck(b, 6, true) &&
      !(b.board[3][1] == -1000 || b.board[4][1] == -1000 || b.board[5][1] == -1000 || b.board[6][1] == -1000 || b.board[7][1] == -1000) &&
      !(b.board[3][2] == -3000 || b.board[4][2] == -3000 || b.board[5][2] == -3000 || b.board[6][2] == -3000 || b.board[7][2] == -3000) &&
      !(b.board[2][1] == -3000 || b.board[3][1] == -3000 || b.board[4][1] == -3000 || b.board[6][1] == -3000 || b.board[7][1] == -3000) &&
      !(b.board[6][1] == -100000)) {

      AddMove(moves, Move(kPosX, kPosY, kPosX + 2, kPosY, 0, false, false, 0, 2));
    }
  }
}

inline void BPawnMoves(Board& b, Move moves[100], const int kPosX, const int kPosY) {

  // Promotion
  if (kPosY == 1) {
    if (kPosX + 1 < 8 && b.board[kPosX + 1][kPosY - 1] > 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 1, b.board[kPosX + 1][kPosY - 1], false, false, -3000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 1, b.board[kPosX + 1][kPosY - 1], false, false, -3100, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 1, b.board[kPosX + 1][kPosY - 1], false, false, -5000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 1, b.board[kPosX + 1][kPosY - 1], false, false, -9000, 0));
    }
    if (kPosX - 1 > -1 && b.board[kPosX - 1][kPosY - 1] > 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 1, b.board[kPosX - 1][kPosY - 1], false, false, -3000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 1, b.board[kPosX - 1][kPosY - 1], false, false, -3100, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 1, b.board[kPosX - 1][kPosY - 1], false, false, -5000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 1, b.board[kPosX - 1][kPosY - 1], false, false, -9000, 0));
    }

    if (!b.board[kPosX][kPosY - 1]) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY - 1, 0, false, false, -3000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY - 1, 0, false, false, -3100, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY - 1, 0, false, false, -5000, 0));
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY - 1, 0, false, false, -9000, 0));
    }
  }

  else {
    if (kPosX + 1 < 8 && b.board[kPosX + 1][kPosY - 1] > 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 1, b.board[kPosX + 1][kPosY - 1]));
    }
    if (kPosX - 1 > -1 && b.board[kPosX - 1][kPosY - 1] > 0) {
      AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 1, b.board[kPosX - 1][kPosY - 1]));
    }

    if (!b.board[kPosX][kPosY - 1]) {
      AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY - 1, 0));

      // Double Pawn Move
      if (kPosY == 6 && !b.board[kPosX][kPosY - 2]) {
        AddMove(moves, Move(kPosX, kPosY, kPosX, kPosY - 2, 0, false, true, 0, 0));
      }
    }

    // En Passant
    if (b.en_passant_x != -1 && b.en_passant_y == kPosY) {
      if (kPosX == b.en_passant_x + 1) {
        AddMove(moves, Move(kPosX, kPosY, kPosX - 1, kPosY - 1, -1000, true, false, 0, 0));
      }
      else if (kPosX == b.en_passant_x - 1) {
        AddMove(moves, Move(kPosX, kPosY, kPosX + 1, kPosY - 1, -1000, true, false, 0, 0));
      }
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


  // Castle
  if (b.b_l_castle && !b.board[1][7] && !b.board[2][7] && !b.board[3][7]) {
    if (CastleDiagonalInCheck(b, 1, false) && CastleDiagonalInCheck(b, 2, false) && CastleDiagonalInCheck(b, 3, false) && CastleDiagonalInCheck(b, 4, false) &&
      !(b.board[0][6] == 1000 || b.board[1][6] == 1000 || b.board[2][6] == 1000 || b.board[3][6] == 1000 || b.board[4][6] == 1000 || b.board[5][6] == 1000) &&
      !(b.board[0][5] == 3000 || b.board[1][5] == 3000 || b.board[2][5] == 3000 || b.board[3][5] == 3000 || b.board[4][5] == 3000 || b.board[5][5] == 3000) &&
      !(b.board[0][6] == 3000 || b.board[1][6] == 3000 || b.board[2][6] == 3000 || b.board[3][6] == 3000 || b.board[4][6] == 3000 || b.board[5][6] == 3000 || b.board[6][6] == 3000) &&
      !(b.board[1][6] == 100000 || b.board[2][6] == 100000)) {

      AddMove(moves, Move(kPosX, kPosY, kPosX - 2, kPosY, 0, false, false, 0, 3));
    }
  }

  if (b.b_r_castle && !b.board[5][7] && !b.board[6][7]) {
    if (CastleDiagonalInCheck(b, 4, false) && CastleDiagonalInCheck(b, 5, false) && CastleDiagonalInCheck(b, 6, false) &&
      !(b.board[3][6] == 1000 || b.board[4][6] == 1000 || b.board[5][6] == 1000 || b.board[6][6] == 1000 || b.board[7][6] == 1000) &&
      !(b.board[3][5] == 3000 || b.board[4][5] == 3000 || b.board[5][5] == 3000 || b.board[6][5] == 3000 || b.board[7][5] == 3000) &&
      !(b.board[2][6] == 3000 || b.board[3][6] == 3000 || b.board[4][6] == 3000 || b.board[6][6] == 3000 || b.board[7][6] == 3000) &&
      !(b.board[6][6] == 100000)) {

      AddMove(moves, Move(kPosX, kPosY, kPosX + 2, kPosY, 0, false, false, 0, 4));
    }
  }
}