#include "macros.h"


const U64 kCaptureMask = 8388607ULL;

const U64 kEnPassantMask = 960ULL;

const U64 kWShortCastleMask = 959ULL;
const U64 kWLongCastleMask = 895ULL;
const U64 kWBothCastleMask = 831ULL;

const U64 kBShortCastleMask = 767ULL;
const U64 kBLongCastleMask = 511ULL;
const U64 kBBothCastleMask = 255ULL;



void MakeMove(U64 bb[13], U64& move, const bool KSide);
void UndoMove(U64 bb[13], const U64 kMove, const bool kSide, const U64 kUtil);

// Initialization
inline int NotationToSquare(const char letter, const char number);
inline void ParseFen(Board& b, const char kFen[80]);


//void Board::Initialize(const char kFen[80]);