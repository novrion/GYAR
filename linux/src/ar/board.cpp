#include "board.h"


const std::map<char, int> kIPiece = {
  {'P', 1000},
  {'N', 3000},
  {'B', 3100},
  {'R', 5000},
  {'Q', 9000},
  {'K', 100000},

  {'p', -1000},
  {'n', -3000},
  {'b', -3100},
  {'r', -5000},
  {'q', -9000},
  {'k', -100000}
};



void MakeMove(Board& b, Move& move) {

  // Reset En Passant Square
  b.en_passant_x = -1;

  // Update Rook Moved Flag
  if ((b.w_r_castle || b.w_l_castle) && b.board[move.from_x][move.from_y] == 5000) {
    if (move.from_x == 0) b.w_l_castle = false;
    else if (move.from_x == 7) b.w_r_castle = false;
  }
  else if ((b.b_r_castle || b.b_l_castle) && b.board[move.from_x][move.from_y] == -5000) {
    if (move.from_x == 0) b.b_l_castle = false;
    else if (move.from_x == 7) b.b_r_castle = false;
  }

  // Update King Moved Flag
  if (b.board[move.from_x][move.from_y] == 100000) {
    b.w_l_castle = false;
    b.w_r_castle = false;
  }
  else if (b.board[move.from_x][move.from_y] == -100000) {
    b.b_l_castle = false;
    b.b_r_castle = false;
  }



  if (move.castle) {

    if (move.castle == 1) {
      b.board[4][0] = 0;
      b.board[2][0] = 100000;

      b.board[0][0] = 0;
      b.board[3][0] = 5000;
    }

    else if (move.castle == 2) {
      b.board[4][0] = 0;
      b.board[6][0] = 100000;

      b.board[7][0] = 0;
      b.board[5][0] = 5000;
    }


    else if (move.castle == 3) {
      b.board[4][7] = 0;
      b.board[2][7] = -100000;

      b.board[0][7] = 0;
      b.board[3][7] = -5000;
    }

    else {
      b.board[4][7] = 0;
      b.board[6][7] = -100000;

      b.board[7][7] = 0;
      b.board[5][7] = -5000;
    }
  }

  else if (move.promotion) {

    b.board[move.to_x][move.to_y] = move.promotion;
    b.board[move.from_x][move.from_y] = 0;
  }

  else if (move.en_passant) {

    b.board[move.to_x][move.to_y] = b.board[move.from_x][move.from_y];
    b.board[move.from_x][move.from_y] = 0;

    b.board[move.to_x][move.from_y] = 0;
  }

  else if (move.double_pawn) {

    b.en_passant_x = move.to_x;
    b.en_passant_y = move.to_y;

    b.board[move.to_x][move.to_y] = b.board[move.from_x][move.from_y];
    b.board[move.from_x][move.from_y] = 0;
  }

  else {

    b.board[move.to_x][move.to_y] = b.board[move.from_x][move.from_y];
    b.board[move.from_x][move.from_y] = 0;
  }
}

void UndoMove(Board& b, Move& move, const int en_passant_x, const int en_passant_y, const bool w_l_castle, const bool w_r_castle, const bool b_l_castle, const bool b_r_castle) {

  b.en_passant_x = en_passant_x;
  b.en_passant_y = en_passant_y;

  b.w_l_castle = w_l_castle;
  b.w_r_castle = w_r_castle;

  b.b_l_castle = b_l_castle;
  b.b_r_castle = b_r_castle;



  if (move.castle) {

    if (move.castle == 1) {
      b.board[4][0] = 0;
      b.board[2][0] = 100000;

      b.board[0][0] = 0;
      b.board[3][0] = 5000;
    }

    else if (move.castle == 2) {
      b.board[4][0] = 0;
      b.board[6][0] = 100000;

      b.board[7][0] = 0;
      b.board[5][0] = 5000;
    }


    else if (move.castle == 3) {
      b.board[4][7] = 0;
      b.board[2][7] = -100000;

      b.board[0][7] = 0;
      b.board[3][7] = -5000;
    }

    else if (move.castle == 4) {
      b.board[4][7] = 0;
      b.board[6][7] = -100000;

      b.board[7][7] = 0;
      b.board[5][7] = -5000;
    }
  }

  else if (move.promotion) {

    if (move.to_y == 7) {
      b.board[move.from_x][move.from_y] = 1000;
    }
    else {
      b.board[move.from_x][move.from_y] = -1000;
    }

    b.board[move.to_x][move.to_y] = move.capture;
  }

  else if (move.en_passant) {

    if (move.to_y > move.from_y) {
      b.board[move.to_x][move.to_y] = 0;
      b.board[move.from_x][move.from_y] = 1000;
      b.board[move.to_x][move.from_y] = -1000;
    }
    else {
      b.board[move.to_x][move.to_y] = 0;
      b.board[move.from_x][move.from_y] = -1000;
      b.board[move.to_x][move.from_y] = 1000;
    }
  }

  else {

    b.board[move.from_x][move.from_y] = b.board[move.to_x][move.to_y];
    b.board[move.to_x][move.to_y] = move.capture;
  }
}


inline void ParseFen(Board& b, const char kFen[80]) {

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) { 
      b.board[i][j] = 0;
    }
  }

  b.side = false;
  b.en_passant_x = -1;
  b.w_l_castle = false;
  b.w_r_castle = false;
  b.b_l_castle = false;
  b.b_r_castle = false;

  int stage = 0;
  int x = 0, y = 7;

  for (int i = 0; i < 80; ++i) {

    if (kFen[i] == ' ') ++stage;


    if (!stage) {

      if (kFen[i] == '/') {
        --y;
        x = 0;
        continue;
      }
      else if (kFen[i] > 47 && kFen[i] < 58) x += kFen[i] - '0';
      else {
        b.board[x++][y] = kIPiece.at(kFen[i]);
      }
    }

    else if (stage == 1) {
      kFen[++i] == 'w' ? b.side = true : 0;
    }

    else if (stage == 2) {

      if (kFen[i] == 'K') b.w_r_castle = true;
      else if (kFen[i] == 'Q') b.w_l_castle = true;
      else if (kFen[i] == 'k') b.b_r_castle = true;
      else if (kFen[i] == 'q') b.b_l_castle = true;
    }

    else if (stage == 3) {

      if (kFen[i + 1] == '-') break;
      else {
        b.en_passant_x = kFen[i + 1] - 97;
        b.en_passant_y = kFen[i + 2] - '0' - 1;
        break;
      }
    }
  }
}

void Board::Initialize(const char kFen[80]) {
  ParseFen(*this, kFen);
}