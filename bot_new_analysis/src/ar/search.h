#include "macros.h"
#include "moves.h"
#include "board.h"



void PlayBot();

// Evaluation
inline int Evaluate(const Board& b);

// Search
inline int Minimax(Board& b, const int kDepth, const bool kSide);