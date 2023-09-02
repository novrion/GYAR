#include "beta.h"

using namespace std;


const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 not_gh_file = 4557430888798830399ULL;



void generateMoves( U64 bb[13], int colour, U64 moves[100] ) {

	U64 w_block = _w_block( bb );
	U64 b_block = _b_block( bb );

	int square = 0;

	if (colour) {

		U64 w_piece = w_block;
		while (w_piece) {

			square = __builtin_ctzll( w_piece );
			pop_bit( w_piece, square );

			if (bb[1] & 1ULL << square) {
				pawnMoves( square, colour, w_block, b_block, moves );
			}

			else if (bb[2] & 1ULL << square) {
				knightMoves( square, colour, w_block, b_block, moves );
			}

			else if (bb[3] & 1ULL << square) {
				bishopMoves( square, colour, w_block, b_block, moves );
			}

			else if (bb[4] & 1ULL << square) {
				rookMoves( square, colour, w_block, b_block, moves );
			}

			else if (bb[5] & 1ULL << square) {
				queenMoves( square, colour, w_block, b_block, moves );
			}

			else if (bb[6] & 1ULL << square) {
				kingMoves( square, colour, w_block, b_block, moves );
			}
		}
	}

	else {

		U64 b_piece = b_block;
		while (b_piece) {

			square = __builtin_ctzll( b_piece );
			pop_bit( b_piece, square );

			if (bb[7] & 1ULL << square) {
				pawnMoves( square, colour, w_block, b_block, moves );
			}

			else if (bb[8] & 1ULL << square) {
				knightMoves( square, colour, w_block, b_block, moves );
			}

			else if (bb[9] & 1ULL << square) {
				bishopMoves( square, colour, w_block, b_block, moves );
			}

			else if (bb[10] & 1ULL << square) {
				rookMoves( square, colour, w_block, b_block, moves );
			}

			else if (bb[11] & 1ULL << square) {
				queenMoves( square, colour, w_block, b_block, moves );
			}

			else if (bb[12] & 1ULL << square) {
				kingMoves( square, colour, w_block, b_block, moves );
			}
		}

	}
}



// Add Moves
static inline void addMove( U64 moves[100], const U64 move ) {
	moves[moves[99]++] = move;
}



static inline void pawnMoves( int square, int colour, U64 w_block, U64 b_block, U64 moves[100] ) {

	U64 bitboard = 0ULL;
	set_bit( bitboard, square );

	if (colour) {

		if (square / 8 == 1) {
			if (!((bitboard >> 8) & w_block & b_block)) addMove( moves, encode_move( square, square - 8, 1, 0, 0, 5, 0, 0 ) );

			if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) addMove( moves, encode_move( square, square - 7, 1, 1, 6, 0, 0, 0 ) );
			if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) addMove( moves, encode_move( square, square - 9, 1, 1, 6, 0, 0, 0 ) );
		}

		else {

			if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) addMove( moves, encode_move( square, square - 7, 1, 1, 0, 0, 0, 0 ) );
			if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) addMove( moves, encode_move( square, square - 9, 1, 1, 0, 0, 0, 0 ) );

			if (!((bitboard >> 8) & w_block) && !((bitboard >> 8) & b_block)) {

				addMove( moves, encode_move( square, square - 8, 1, 0, 0, 0, 0, 0 ) );
				if (square / 8 == 6 && !((bitboard >> 16) & w_block) && !((bitboard >> 16) & b_block)) addMove( moves, encode_move( square, square - 16, 1, 0, 0, 1, 0, 0 ) );
			}
		}
	}

	else {

		if (square / 8 == 6) {
			if (!((bitboard << 8) & w_block & b_block)) addMove( moves, encode_move( square, square + 8, 7, 0, 11, 0, 0, 0 ) );

			if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) addMove( moves, encode_move( square, square + 7, 7, 1, 11, 0, 0, 0 ) );
			if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) addMove( moves, encode_move( square, square + 9, 7, 1, 11, 0, 0, 0 ) );
		}

		else {

			if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) addMove( moves, encode_move( square, square + 7, 7, 1, 0, 0, 0, 0 ) );
			if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) addMove( moves, encode_move( square, square + 9, 7, 1, 0, 0, 0, 0 ) );

			if (!((bitboard << 8) & w_block) && !((bitboard << 8) & b_block)) {

				addMove( moves, encode_move( square, square + 8, 7, 0, 0, 0, 0, 0 ) );
				if (square / 8 == 1 && !((bitboard << 16) & w_block) && !((bitboard << 16) & b_block)) addMove( moves, encode_move( square, square + 16, 7, 0, 0, 1, 0, 0 ) );
			}
		}
	}
}

static inline void knightMoves( int square, int colour, U64 w_block, U64 b_block, U64 moves[100] ) {

	U64 bitboard = 0ULL;
	set_bit( bitboard, square );

	if (colour) {

		if ((bitboard >> 6 & not_ab_file) && !(bitboard >> 6 & w_block)) {
			if (bitboard >> 6 & b_block) addMove( moves, encode_move( square, square - 6, 2, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 6, 2, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard >> 10 & not_gh_file) && !(bitboard >> 10 & w_block)) {
			if (bitboard >> 10 & b_block) addMove( moves, encode_move( square, square - 10, 2, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 10, 2, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard >> 15 & not_a_file) && !(bitboard >> 15 & w_block)) {
			if (bitboard >> 15 & b_block) addMove( moves, encode_move( square, square - 15, 2, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 15, 2, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard >> 17 & not_h_file) && !(bitboard >> 17 & w_block)) {
			if (bitboard >> 17 & b_block) addMove( moves, encode_move( square, square - 17, 2, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 17, 2, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 6 & not_gh_file) && !(bitboard << 6 & w_block)) {
			if (bitboard << 6 & b_block) addMove( moves, encode_move( square, square + 6, 2, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 6, 2, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 10 & not_ab_file) && !(bitboard << 10 & w_block)) {
			if (bitboard << 10 & b_block) addMove( moves, encode_move( square, square + 10, 2, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 10, 2, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 15 & not_h_file) && !(bitboard << 15 & w_block)) {
			if (bitboard << 15 & b_block) addMove( moves, encode_move( square, square + 15, 2, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 15, 2, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 17 & not_a_file) && !(bitboard << 17 & w_block)) {
			if (bitboard << 17 & b_block) addMove( moves, encode_move( square, square + 17, 2, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 17, 2, 0, 0, 0, 0, 0 ) );
		}
	}

	else {

		if ((bitboard >> 6 & not_ab_file) && !(bitboard >> 6 & b_block)) {
			if (bitboard >> 6 & w_block) addMove( moves, encode_move( square, square - 6, 8, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 6, 8, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard >> 10 & not_gh_file) && !(bitboard >> 10 & b_block)) {
			if (bitboard >> 10 & w_block) addMove( moves, encode_move( square, square - 10, 8, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 10, 8, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard >> 15 & not_a_file) && !(bitboard >> 15 & b_block)) {
			if (bitboard >> 15 & w_block) addMove( moves, encode_move( square, square - 15, 8, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 15, 8, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard >> 17 & not_h_file) && !(bitboard >> 17 & b_block)) {
			if (bitboard >> 17 & w_block) addMove( moves, encode_move( square, square - 17, 8, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 17, 8, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 6 & not_gh_file) && !(bitboard << 6 & b_block)) {
			if (bitboard << 6 & w_block) addMove( moves, encode_move( square, square + 6, 8, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 6, 8, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 10 & not_ab_file) && !(bitboard << 10 & b_block)) {
			if (bitboard << 10 & w_block) addMove( moves, encode_move( square, square + 10, 8, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 10, 8, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 15 & not_h_file) && !(bitboard << 15 & b_block)) {
			if (bitboard << 15 & w_block) addMove( moves, encode_move( square, square + 15, 8, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 15, 8, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 17 & not_a_file) && !(bitboard << 17 & b_block)) {
			if (bitboard << 17 & w_block) addMove( moves, encode_move( square, square + 17, 8, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 17, 8, 0, 0, 0, 0, 0 ) );
		}
	}
}

static inline void kingMoves( int square, int colour, U64 w_block, U64 b_block, U64 moves[100] ) {

	U64 bitboard = 0ULL;
	set_bit( bitboard, square );

	if (colour) {

		if ((bitboard >> 7 & not_a_file) && !(bitboard >> 7 & w_block)) {
			if (bitboard >> 7 & b_block) addMove( moves, encode_move( square, square - 7, 6, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 7, 6, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard >> 8) && !(bitboard >> 8 & w_block)) {
			if (bitboard >> 8 & b_block) addMove( moves, encode_move( square, square - 8, 6, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 8, 6, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard >> 9 & not_h_file) && !(bitboard >> 9 & w_block)) {
			if (bitboard >> 9 & b_block) addMove( moves, encode_move( square, square - 9, 6, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 9, 6, 0, 0, 0, 0, 0 ) );
		}


		if ((bitboard >> 1 & not_h_file) && !(bitboard >> 1 & w_block)) {
			if (bitboard >> 1 & b_block) addMove( moves, encode_move( square, square - 1, 6, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 1, 6, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 1 & not_a_file) && !(bitboard << 1 & w_block)) {
			if (bitboard << 1 & b_block) addMove( moves, encode_move( square, square + 1, 6, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 1, 6, 0, 0, 0, 0, 0 ) );
		}


		if ((bitboard << 7 & not_h_file) && !(bitboard << 7 & w_block)) {
			if (bitboard << 7 & b_block) addMove( moves, encode_move( square, square + 7, 6, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 7, 6, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 8) && !(bitboard << 8 & w_block)) {
			if (bitboard << 8 & b_block) addMove( moves, encode_move( square, square + 8, 6, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 8, 6, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 9 & not_a_file) && !(bitboard << 9 & w_block)) {
			if (bitboard << 9 & b_block) addMove( moves, encode_move( square, square + 9, 6, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 9, 6, 0, 0, 0, 0, 0 ) );
		}
	}

	else {

		if ((bitboard >> 7 & not_a_file) && !(bitboard >> 7 & b_block)) {
			if (bitboard >> 7 & w_block) addMove( moves, encode_move( square, square - 7, 12, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 7, 12, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard >> 8) && !(bitboard >> 8 & b_block)) {
			if (bitboard >> 8 & w_block) addMove( moves, encode_move( square, square - 8, 12, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 8, 12, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard >> 9 & not_h_file) && !(bitboard >> 9 & b_block)) {
			if (bitboard >> 9 & w_block) addMove( moves, encode_move( square, square - 9, 12, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 9, 12, 0, 0, 0, 0, 0 ) );
		}


		if ((bitboard >> 1 & not_h_file) && !(bitboard >> 1 & b_block)) {
			if (bitboard >> 1 & w_block) addMove( moves, encode_move( square, square - 1, 12, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square - 1, 12, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 1 & not_a_file) && !(bitboard << 1 & b_block)) {
			if (bitboard << 1 & w_block) addMove( moves, encode_move( square, square + 1, 12, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 1, 12, 0, 0, 0, 0, 0 ) );
		}


		if ((bitboard << 7 & not_h_file) && !(bitboard << 7 & b_block)) {
			if (bitboard << 7 & w_block) addMove( moves, encode_move( square, square + 7, 12, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 7, 12, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 8) && !(bitboard << 8 & b_block)) {
			if (bitboard << 8 & w_block) addMove( moves, encode_move( square, square + 8, 12, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 8, 12, 0, 0, 0, 0, 0 ) );
		}

		if ((bitboard << 9 & not_a_file) && !(bitboard << 9 & b_block)) {
			if (bitboard << 9 & w_block) addMove( moves, encode_move( square, square + 9, 12, 1, 0, 0, 0, 0 ) );
			else addMove( moves, encode_move( square, square + 9, 12, 0, 0, 0, 0, 0 ) );
		}
	}
}


static inline void bishopMoves( int square, int colour, U64 w_block, U64 b_block, U64 moves[100] ) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				addMove( moves, encode_move( square, x * 8 + y, 3, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 3, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				addMove( moves, encode_move( square, x * 8 + y, 3, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 3, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				addMove( moves, encode_move( square, x * 8 + y, 3, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 3, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				addMove( moves, encode_move( square, x * 8 + y, 3, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 3, 0, 0, 0, 0, 0 ) );
		}
	}

	else {

		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				addMove( moves, encode_move( square, x * 8 + y, 9, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 9, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				addMove( moves, encode_move( square, x * 8 + y, 9, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 9, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				addMove( moves, encode_move( square, x * 8 + y, 9, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 9, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				addMove( moves, encode_move( square, x * 8 + y, 9, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 9, 0, 0, 0, 0, 0 ) );
		}
	}
}

static inline void rookMoves( int square, int colour, U64 w_block, U64 b_block, U64 moves[100] ) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				addMove( moves, encode_move( square, y * 8 + t_file, 4, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, y * 8 + t_file, 4, 0, 0, 0, 0, 0 ) );
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				addMove( moves, encode_move( square, y * 8 + t_file, 4, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, y * 8 + t_file, 4, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				addMove( moves, encode_move( square, t_rank * 8 + x, 4, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, t_rank * 8 + x, 4, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				addMove( moves, encode_move( square, t_rank * 8 + x, 4, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, t_rank * 8 + x, 4, 0, 0, 0, 0, 0 ) );
		}
	}

	else {

		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				addMove( moves, encode_move( square, y * 8 + t_file, 10, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, y * 8 + t_file, 10, 0, 0, 0, 0, 0 ) );
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				addMove( moves, encode_move( square, y * 8 + t_file, 10, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, y * 8 + t_file, 10, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				addMove( moves, encode_move( square, t_rank * 8 + x, 10, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, t_rank * 8 + x, 10, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				addMove( moves, encode_move( square, t_rank * 8 + x, 10, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, t_rank * 8 + x, 10, 0, 0, 0, 0, 0 ) );
		}
	}
}

static inline void queenMoves( int square, int colour, U64 w_block, U64 b_block, U64 moves[100] ) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		// bishop
		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				addMove( moves, encode_move( square, x * 8 + y, 5, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 5, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				addMove( moves, encode_move( square, x * 8 + y, 5, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 5, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				addMove( moves, encode_move( square, x * 8 + y, 5, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 5, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				addMove( moves, encode_move( square, x * 8 + y, 5, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 5, 0, 0, 0, 0, 0 ) );
		}


		// rook
		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				addMove( moves, encode_move( square, y * 8 + t_file, 5, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, y * 8 + t_file, 5, 0, 0, 0, 0, 0 ) );
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				addMove( moves, encode_move( square, y * 8 + t_file, 5, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, y * 8 + t_file, 5, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				addMove( moves, encode_move( square, t_rank * 8 + x, 5, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, t_rank * 8 + x, 5, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				addMove( moves, encode_move( square, t_rank * 8 + x, 5, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, t_rank * 8 + x, 5, 0, 0, 0, 0, 0 ) );
		}
	}

	else {

		// bishop
		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				addMove( moves, encode_move( square, x * 8 + y, 11, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 11, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				addMove( moves, encode_move( square, x * 8 + y, 11, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 11, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				addMove( moves, encode_move( square, x * 8 + y, 11, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 11, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				addMove( moves, encode_move( square, x * 8 + y, 11, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, x * 8 + y, 11, 0, 0, 0, 0, 0 ) );
		}


		// rook
		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				addMove( moves, encode_move( square, y * 8 + t_file, 11, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, y * 8 + t_file, 11, 0, 0, 0, 0, 0 ) );
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				addMove( moves, encode_move( square, y * 8 + t_file, 11, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, y * 8 + t_file, 11, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				addMove( moves, encode_move( square, t_rank * 8 + x, 11, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, t_rank * 8 + x, 11, 0, 0, 0, 0, 0 ) );
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				addMove( moves, encode_move( square, t_rank * 8 + x, 11, 1, 0, 0, 0, 0 ) );
				break;
			}
			addMove( moves, encode_move( square, t_rank * 8 + x, 11, 0, 0, 0, 0, 0 ) );
		}
	}
}