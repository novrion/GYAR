#include "macros.h"


// Constants
const U64 kCaptureMask = 8388607ULL;

const U64 kEnPassantMask = 960ULL;

const U64 kWShortCastleMask = 959ULL;
const U64 kWLongCastleMask = 895ULL;
const U64 kWBothCastleMask = 831ULL;

const U64 kBShortCastleMask = 767ULL;
const U64 kBLongCastleMask = 511ULL;
const U64 kBBothCastleMask = 255ULL;

const std::map<char, int> kIPiece = {
  {'P', 1},
  {'N', 2},
  {'B', 3},
  {'R', 4},
  {'Q', 5},
  {'K', 6},

  {'p', 7},
  {'n', 8},
  {'b', 9},
  {'r', 10},
  {'q', 11},
  {'k', 12}
};



void MakeMove(U64 bb[13], U64& move, const bool KSide);
void UndoMove(U64 bb[13], const U64 kMove, const bool kSide, const U64 kUtil);

