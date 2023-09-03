#include "macros.h"
#include "moves.h"
#include "board.h"



// Evaluation
inline int Evaluate(Board& b);


// Search
inline int Minimax(Board& b, const int kDepth, int alpha, int beta, const bool kSide);


// Play Bot
void PlayBot();