#include "macros.h"



void MakeMove(Board& b, Move& move);
void UndoMove(Board& b, Move& move, const int en_passant_x, const int en_passant_y, const bool w_l_castle, const bool w_r_castle, const bool b_l_castle, const bool b_r_castle);

// Initialization
inline void ParseFen(Board& b, const char kFen[80]);


// void Board::Initialize(const char kFen[80]);