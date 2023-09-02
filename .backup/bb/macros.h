#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>



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
#define GET_MOVE_CAPTURE(move) ((move & 125829120ULL) >> 23)


// Constants
const int kNPositions = 10;
const int kNTests = 100;

const U64 kNotAFile = 18374403900871474942ULL;
const U64 kNotHFile = 9187201950435737471ULL;
const U64 kNotABFile = 18229723555195321596ULL;
const U64 kNotGHFile = 4557430888798830399ULL;

const U64 capture_mask = 8388607ULL;

const int kMaterialScore[13] = { 0, 1000, 3000, 3000, 5000, 9000, 100000, -1000, -3000, -3000, -5000, -9000, -100000 };
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

const int kBoardRegular[kNPositions][8][8] = {

	{
		{5000, 1000, 0, 0, 0, -1000, 0, -5000},
		{0, 1000, 0, 0, 0, 0, -1000, -3000},
		{3100, 1000, 3000, 0, 0, 0, 0, -3100},
		{9000, 0, 0, 3000, 0, -1000, 0, -9000},
		{100000, 0, 0, 1000, 0, 0, -1000, -100000},
		{3100, 1000, 0, 0, 0, -3000, -1000, -3100},
		{0, 1000, 0, 0, 0, 0, -1000, 0},
		{5000, 1000, 0, 0, 0, 0, -1000, -5000}
	},
	
	{
		{5000, 1000, 0, 0, 0, 0, -1000, -5000},
		{3000, 1000, 0, 0, 3100, 0, -1000, 0},
		{3100, 1000, 0, 0, 0, -3000, -1000, -3100},
		{9000, 1000, 0, 0, 0, -3000, -1000, -9000},
		{5000, 0, 0, 0, 3000, 0, -3100, -100000},
		{0, 1000, 0, 0, 0, 0, -1000, 0},
		{100000, 1000, 0, 0, 0, 0, -1000, 0},
		{0, 1000, 0, 0, 0, 0, -1000, -5000}
	},

	{
		{5000, 1000, 0, 0, 0, 0, -1000, -5000},
		{0, 0, 0, 0, 0, 0, -1000, -3000},
		{3100, 0, 1000, 3100, 0, 0, -1000, -3100},
		{9000, 0, 0, 1000, 0, 0, 0, -9000},
		{0, 0, 0, 0, 0, -1000, -3100, -100000},
		{5000, 1000, 3000, 0, 0, 0, -1000, 0},
		{100000, 1000, 0, 0, 0, 0, -1000, 0},
		{0, 1000, 0, 0, 0, 0, -1000, -5000}
	},

	{
		{5000, 1000, 0, 0, 0, 0, -1000, -5000},
		{3000, 1000, 0, 0, 0, 0, -1000, 0},
		{3100, 1000, 0, 0, 0, -1000, 0, 0},
		{9000, 0, 0, 1000, -1000, 0, -3000, -9000},
		{0, 3100, 0, 0, 1000, -1000, -3000, -100000},
		{5000, 1000, 3000, 0, -3100, 0, -1000, -3100},
		{100000, 1000, 0, 0, 0, 0, -1000, 0},
		{0, 1000, 0, 0, 0, 0, -1000, -5000}
	},

	{
		{5000, 1000, 0, 0, 0, 0, -1000, -5000},
		{0, 1000, 0, 0, 0, 0, -1000, -3000},
		{3100, 1000, 3000, 0, 0, -1000, 0, 0},
		{0, 1000, 0, 0, -1000, 0, 0, -9000},
		{100000, 0, 0, 1000, 0, -1000, 0, -100000},
		{3100, 1000, 9000, 0, 0, 0, -1000, -3100},
		{0, 1000, 0, 0, 0, 0, -1000, -3000},
		{5000, 0, 1000, 0, 0, 0, -1000, -5000}
	},

	{
	
	},

	{
	
	},

	{
	
	},

	{
	
	},

	{
	
	}
};
const int kBoardTactic[kNPositions][8][8] = {

	{
		{5000, 1000, 0, 0, 0, 0, -1000, -5000},
		{3000, 1000, 0, 0, 0, 0, -1000, 0},
		{3100, 1000, 0, -3000, 0, 0, -1000, -3100},
		{9000, 1000, 0, 0, 0, 0, -1000, -9000},
		{0, 0, 0, 0, 5000, 0, -3100, -100000},
		{3100, 1000, 0, 0, 0, 0, -1000, 0},
		{100000, 1000, 0, 0, 0, 0, -1000, 0},
		{0, 1000, 0, 0, 0, 0, -1000, -5000}
	},

	{
		{5000, 1000, 0, 0, 0, -1000, 0, -5000},
		{0, 1000, 3000, 0, 0, 0, -1000, -3000},
		{0, 1000, 3000, 0, 0, 0, 0, -3100},
		{9000, 0, 0, 0, -1000, 0, 0, -9000},
		{100000, 0, 3100, 1000, -1000, 0, 0, -100000},
		{3100, 1000, 0, 0, 0, -3000, -1000, -3100},
		{0, 1000, 0, 0, 0, 0, -1000, 0},
		{5000, 1000, 0, 0, 0, 0, -1000, -5000}
	},

	{
		{5000, 1000, 0, 0, 0, 0, -1000, -5000},
		{0, 1000, 0, 0, 0, 0, -1000, 0},
		{0, 0, 1000, -1000, 0, 0, 0, 0},
		{9000, 3000, 0, 1000, -1000, 0, -9000, 0},
		{100000, 0, 1000, 0, -3000, 0, -1000, -100000},
		{3100, 1000, 3000, 3100, -3100, -3000, -1000, -3100},
		{0, 1000, 0, 0, 0, 0, -1000, 0},
		{5000, 1000, 0, 0, 0, 0, -1000, -5000}
	},

	{
		{0, 1000, 0, 0, 0, -1000, 0, -5000},
		{0, 1000, 3000, -1000, 0, -9000, 0, 0},
		{100000, 1000, 0, 0, 0, 0, 0, 0},
		{5000, 9000, 0, 0, 0, -1000, -3000, 0},
		{0, 3000, 3100, 1000, -1000, -3100, -3100, 0},
		{3100, 0, 1000, 0, 0, -3000, -1000, -5000},
		{0, 0, 0, 0, 1000, 0, -1000, -100000},
		{5000, 1000, 0, 0, 0, 0, -1000, 0}
	},

	{
		{5000, 0, 0, 1000, 0, -1000, 0, -5000},
		{0, 1000, 0, 0, 0, -1000, 0, 0},
		{3100, 9000, 1000, 3100, -3100, -3000, -1000, -3100},
		{0, 3000, 1000, 0, 0, -1000, 0, -9000},
		{5000, 0, 0, 1000, -1000, 0, 0, 0},
		{0, 1000, 3000, 0, 0, -3000, -1000, -5000},
		{100000, 1000, 0, 0, 0, 0, -1000, -100000},
		{0, 0, 1000, 0, 0, -1000, 0, 0}
	},

	{
	
	},

	{
	
	},

	{
	
	},

	{
	
	},

	{
	
	}
};
const int kBoardSmall[kNPositions][8][8] = {

	{
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1000, 0, 0, 0, 0},
		{-3100, 0, 0, 0, 3100, 0, 0, 0},
		{0, 0, 0, 0, -3000, 0, 0, 0},
		{0, 0, 0, 0, 0, -100000, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{3000, -1000, 0, 0, 0, 0, 0, 0},
		{0, 0, 100000, 0, 0, 0, -1000, 0}
	},

	{
		{0, -5000, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 3100, 0, 0, 0, 0},
		{0, 0, 100000, 1000, 0, -100000, 0, 0},
		{0, 0, 1000, 0, 0, -1000, 0, 0},
		{0, 0, 0, 1000, -1000, 0, 0, 0}
	},

	{
		{0, 0, -1000, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1000, 100000, 0, 0, 0, 0},
		{0, 0, 0, 0, -3000, 0, 0, 0},
		{0, 0, 0, 0, -100000, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1000, 3000, 0, 0, 0}
	},

	{
		{0, 0, 0, 0, 0, 0, 9000, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, -1000, 0, 0},
		{100000, 1000, 0, 0, -3100, -100000, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, -5000},
		{0, 0, 0, 0, 0, 0, 0, 0}
	},

	{
		{0, 0, 0, 1000, 0, 0, 5000, 0},
		{0, -5000, 0, 0, 0, -1000, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{100000, 0, 1000, 0, -100000, -1000, 0, 0},
		{0, 1000, 0, 0, -1000, 0, 0, 0}
	},

	{
	
	},

	{
	
	},

	{
	
	},

	{
	
	},

	{
	
	}
};


// Board
struct Board {
  U64 bb[13];
	void Initialize( const int kBoardType, const int kBoardIndex );
};