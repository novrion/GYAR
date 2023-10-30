#include "macros.h"



void GenerateMoves(Board& b, Move moves[100], const bool kSide);

// Checks diagonals (angled and straight) from a certain square and if it is attacked. Used for determining if castling should be allowed.
inline bool CastleDiagonalInCheck(Board& b, const int kPosX, const bool kSide);

inline void AddMove(Move moves[100], const Move kMove);

inline void WPawnMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);
inline void WKnightMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);
inline void WBishopMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);
inline void WRookMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);
inline void WQueenMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);
inline void WKingMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);

inline void BPawnMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);
inline void BKnightMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);
inline void BBishopMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);
inline void BRookMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);
inline void BQueenMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);
inline void BKingMoves(Board& b, Move moves[100], const int kPosX, const int kPosY);