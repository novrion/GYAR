#pragma once

#include <stdio.h>
#include <algorithm>
#include <chrono>
#include <map>
#include <cmath>


const int kNPositions = 10;
const int kNTests = 100;
const int kNMaxFen = 50;

const int kPositionScore[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 2, 3, 3, 2, 1, 0},
  {0, 2, 3, 4, 4, 3, 2, 0},
  {0, 3, 4, 5, 5, 4, 3, 0},
  {0, 3, 4, 5, 5, 4, 3, 0},
  {0, 2, 3, 4, 4, 3, 2, 0},
  {0, 1, 2, 3, 3, 2, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

struct Board {
  int board[8][8];
  void Initialize(const char kFen[100]);

  bool side;

  int en_passant_x;
  int en_passant_y;

  bool w_r_castle;
  bool w_l_castle;

  bool b_r_castle;
  bool b_l_castle;
};

struct Move {

  Move() {

    from_x = -1;
    from_y = 0;
    to_x = 0;
    to_y = 0;

    capture = 0;

    en_passant = false;
    double_pawn = false;

    castle = 0;
    promotion = 0;
  }

  Move(int f_x, int f_y, int t_x, int t_y, int _capture) {

    from_x = f_x;
    from_y = f_y;
    to_x = t_x;
    to_y = t_y;

    capture = _capture;

    // Super important !!!!!!!!!!!!! Has to initialize !!!!!!!!
    en_passant = false;
    double_pawn = false;

    castle = 0;
    promotion = 0;
  }

  Move(int f_x, int f_y, int t_x, int t_y, int _capture, bool _en_passant, bool _double_pawn, int _promotion, int _castle) {

    from_x = f_x;
    from_y = f_y;
    to_x = t_x;
    to_y = t_y;

    capture = _capture;

    en_passant = _en_passant;
    double_pawn = _double_pawn;

    castle = _castle;
    promotion = _promotion;
  }

  int from_x, from_y, to_x, to_y;
  int capture;

  bool en_passant;
  bool double_pawn;

  // 1 = w l; 2 = w r; 3 = b l; 4 = b r;
  int castle;
  int promotion;
};