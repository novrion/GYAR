#include "macros.h"


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



void MakeMove(Board& b, Move& move);
void UndoMove(Board& b, Move& move, const int en_passant_x, const int en_passant_y, const bool w_l_castle, const bool w_r_castle, const bool b_l_castle, const bool b_r_castle);