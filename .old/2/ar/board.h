#include "macros.h"



// Make Move
void MakeMove(Board& b, Move& move);

// Undo Move
void UndoMove(Board& b, Move& move);



// Initialization
inline void IterateBoard(Board& b, const int kPosition[8][8]);