#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <map>
#include <bit>



// Macro
#define U64 unsigned long long
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (bitboard ^= (1ULL << square))

#define _w_block(x) (x[1] | x[2] | x[3] | x[4] | x[5] | x[6])
#define _b_block(x) (x[7] | x[8] | x[9] | x[10] | x[11] | x[12])


// Encode
#define encode_move(source, target, piece, capture, promotion, _2pawn, en_passant, castle) \
(source) | (target << 6) | (piece << 12) | (_2pawn << 16) | (en_passant << 17) | (castle << 18) | (promotion << 19) | (capture << 23) \


// Decode
#define get_move_from(move) (move & 63ULL)
#define get_move_to(move) ((move & 4032ULL) >> 6)
#define get_move_piece(move) ((move & 61440ULL) >> 12)
#define get_move_capture(move) ((move & 125829120ULL) >> 23)


const int kNPositions = 10;
const int kNTests = 100;



// Board
struct Board {

	Board() {

		// (white)	Pawn, Horse, Bishop, Rook, Queen, King
		bb[1] = 71776119061217280ULL;
		bb[2] = 4755801206503243776ULL;
		bb[3] = 2594073385365405696ULL;
		bb[4] = 9295429630892703744ULL;
		bb[5] = 576460752303423488ULL;
		bb[6] = 1152921504606846976ULL;

		// (black)	Pawn, Horse, Bishop, Rook, Queen, King
		bb[7] = 65280ULL;
		bb[8] = 66ULL;
		bb[9] = 36ULL;
		bb[10] = 129ULL;
		bb[11] = 8ULL;
		bb[12] = 16ULL;

		// (utility)
		bb[0] = 0ULL;
	}

	U64 bb[13];

	void initialize(const int board_type, const int board_index);
};


// Generate Moves
void generateMoves(U64 bb[13], int colour, U64 moves[100]);

static inline void pawnMoves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);
static inline void knightMoves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);
static inline void kingMoves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);

static inline void bishopMoves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);
static inline void rookMoves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);
static inline void queenMoves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);


// Make Move
void makeMove(U64 bb[13], U64& move, bool colour);


// Search
static inline int minimax(Board& b, int depth, int alpha, int beta, bool colour);


void playBot();