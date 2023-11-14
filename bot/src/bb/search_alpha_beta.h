#include "macros.h"
#include "moves.h"
#include "board.h"



void PlayBot();

// Bit Manipulation
inline int BitCount(U64 x);

// Evaluation
inline int MaterialScore(const U64 kBB[13]);
inline int PositionScore(const U64 kBB[13]);
inline int Evaluate(const U64 kBB[13]);

// Updates all moves to get their captured piece. *Only for Move Order search*
inline void GetMoveCaptures(Board& b, U64 moves[100], const bool kSide);

// Search
inline int Minimax(Board& b, const int kDepth, int alpha, int beta, const bool kSide);