#include "macros.h"
#include "moves.h"
#include "board.h"



// Bit Manipulation
inline int BitCount(U64 x);


// Evaluation
inline int MaterialScore(const U64 kBB[13]);
inline int PositionScore(const U64 kBB[13]);
inline int Evaluate(const U64 kBB[13]);


// Search
inline int Minimax( Board& b, const int kDepth, int alpha, int beta, const bool kSide );


// Play Bot
void PlayBot();