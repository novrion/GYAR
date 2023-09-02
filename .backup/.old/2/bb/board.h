#include "macros.h"



// Initialization
inline void IterateBoard( Board& b, const int kPosition[8][8] );


// Make Move
void MakeMove( U64 bb[13], U64& move, const bool KSide );
void UndoMove( U64 bb[13], const U64 kMove );