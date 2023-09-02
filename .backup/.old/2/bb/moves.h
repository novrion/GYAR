#include "macros.h"



// Bit Manipulation
int PopLsb(U64& b);


// Add Move
inline void AddMove(U64 moves[100], const U64 kMove);


// Move Generation
void GenerateMoves(const U64 kBB[13], U64 moves[100], const bool kSide);

inline void WPawnMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WKnightMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WBishopMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WRookMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WQueenMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WKingMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);

inline void BPawnMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BKnightMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BBishopMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BRookMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BQueenMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BKingMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);