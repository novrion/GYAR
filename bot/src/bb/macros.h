#pragma once

#include <stdio.h>
#include <algorithm>
#include <chrono>
#include <map>
#include <cmath>


#define U64 unsigned long long

// Bit Manipulation
#define SET_BIT(bitboard, square) (bitboard |= (1ULL << square))
#define POP_BIT(bitboard, square) (bitboard &= ~(1ULL << square))

// Blockers
#define W_BLOCK(bb) (bb[1] | bb[2] | bb[3] | bb[4] | bb[5] | bb[6])
#define B_BLOCK(bb) (bb[7] | bb[8] | bb[9] | bb[10] | bb[11] | bb[12])

// Encode Move
#define ENCODE_MOVE(source, target, piece, capture, promotion, _2pawn, en_passant, castle) \
(source) | (target << 6) | (piece << 12) | (_2pawn << 16) | (en_passant << 17) | (castle << 18) | (promotion << 19) | (capture << 23) \

#define RESET_MOVE_CAPTURE(move) (move &= 18446744073701163007ULL)
#define SET_MOVE_CAPTURE(move, piece) (move |= piece << 23)

// Decode Move
#define GET_MOVE_SOURCE(move) (move & 63ULL)
#define GET_MOVE_TARGET(move) ((move & 4032ULL) >> 6)
#define GET_MOVE_PIECE(move) ((move & 61440ULL) >> 12)
#define GET_MOVE_2_PAWN(move) (move & 65536ULL)
#define GET_MOVE_EN_PASSANT(move) (move & 131072ULL)
#define GET_MOVE_CASTLE(move) (move & 262144ULL)
#define GET_MOVE_PROMOTION(move) ((move & 7864320ULL) >> 19)
#define GET_MOVE_CAPTURE(move) ((move & 125829120ULL) >> 23)

// Decode Utility
#define GET_UTILITY_EN_PASSANT(utility) (utility & 63ULL)
#define GET_UTILITY_W_SHORT_CASTLE(utility) (utility & 64ULL)
#define GET_UTILITY_W_LONG_CASTLE(utility) (utility & 128ULL)
#define GET_UTILITY_B_SHORT_CASTLE(utility) (utility & 256ULL)
#define GET_UTILITY_B_LONG_CASTLE(utility) (utility & 512ULL)
#define GET_UTILITY_SIDE(utility) (utility & 1024ULL)


const int kNPositions = 10;
const int kNTests = 100;
const int kNMaxFen = 50;

const int kMaterialScore[13] = { 0, 100, 300, 310, 500, 900, 10000, -100, -300, -310, -500, -900, -10000 };
const int kPositionScore[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 3, 3, 2, 1, 0,
	0, 2, 3, 4, 4, 3, 2, 0,
	0, 3, 4, 5, 5, 4, 3, 0,
	0, 3, 4, 5, 5, 4, 3, 0,
	0, 2, 3, 4, 4, 3, 2, 0,
	0, 1, 2, 3, 3, 2, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};



// Board
struct Board {
	U64 bb[13];
	void Initialize(const char kFen[80]);
};