#include "board.h"
#include "a.h"

using namespace std;



void MakeMove(U64 bb[13], U64& move, const bool kSide) {

	int source = GET_MOVE_SOURCE(move);
	int target = GET_MOVE_TARGET(move);
	int piece = GET_MOVE_PIECE(move);

	int _2pawn = GET_MOVE_2_PAWN(move);
	int en_passant = GET_MOVE_EN_PASSANT(move);
	int castle = GET_MOVE_CASTLE(move);

	int promotion = GET_MOVE_PROMOTION(move);
	int capture = GET_MOVE_CAPTURE(move);


	// Reset En Passant Square
	bb[0] &= kEnPassantMask;

	// Update Rook Moved Flag
	if (piece == 4) {

		if (source == 56) bb[0] &= kWLongCastleMask;
		else if (source == 63) bb[0] &= kWShortCastleMask;
	}
	else if (piece == 10) {

		if (source == 0) bb[0] &= kBLongCastleMask;
		else if (source == 7) bb[0] &= kBShortCastleMask;
	}

	// Update King Moved Flag
	if (piece == 6) bb[0] &= kWBothCastleMask;
	else if (piece == 12) bb[0] &= kBBothCastleMask;



	if (capture) {

		POP_BIT(bb[piece], source);

		if (promotion) SET_BIT(bb[promotion], target);
		else SET_BIT(bb[piece], target);


		if (kSide) {
			for (U64 i = 7; i < 13; ++i) {
				if (bb[i] & (1ULL << target)) {
					POP_BIT(bb[i], target);
					move &= kCaptureMask;
					move |= (i << 23);
					break;
				}
			}
		}
		else {
			for (U64 i = 1; i < 7; ++i) {
				if (bb[i] & (1ULL << target)) {
					POP_BIT(bb[i], target);
					move &= kCaptureMask;
					move |= (i << 23);
					break;
				}
			}
		}
	}

	else if (castle) {

		++A::acastle;

		if (kSide) {

			POP_BIT(bb[6], 60);

			if (target > source) {

				bb[0] &= kWBothCastleMask;


				SET_BIT(bb[6], 62);

				POP_BIT(bb[4], 63);
				SET_BIT(bb[4], 61);
			}

			else {

				bb[0] &= kWBothCastleMask;


				SET_BIT(bb[6], 58);

				POP_BIT(bb[4], 56);
				SET_BIT(bb[4], 59);
			}
		}

		else {

			POP_BIT(bb[12], 4);

			if (target > source) {

				bb[0] &= kBBothCastleMask;


				SET_BIT(bb[12], 6);

				POP_BIT(bb[10], 7);
				SET_BIT(bb[10], 5);
			}

			else {

				bb[0] &= kBBothCastleMask;


				SET_BIT(bb[12], 2);

				POP_BIT(bb[10], 0);
				SET_BIT(bb[10], 3);
			}
		}
	}

	else if (en_passant) {

		++A::aen_passant;

		if (kSide) {

			POP_BIT(bb[1], source);
			SET_BIT(bb[1], target);

			POP_BIT(bb[7], target + 8);
		}

		else {

			POP_BIT(bb[7], source);
			SET_BIT(bb[7], target);

			POP_BIT(bb[1], target - 8);
		}
	}

	else if (_2pawn) {

		++A::adouble_pawn;

		POP_BIT(bb[piece], source);
		SET_BIT(bb[piece], target);

		bb[0] |= target;
	}

	else if (promotion) {

		++A::apromotion;

		POP_BIT(bb[piece], source);
		SET_BIT(bb[promotion], target);
	}

	else {

		POP_BIT(bb[piece], source);
		SET_BIT(bb[piece], target);
	}
}

void UndoMove(U64 bb[13], const U64 kMove, const bool kSide, const U64 util) {

	bb[0] = util;

	int source = GET_MOVE_SOURCE(kMove);
	int target = GET_MOVE_TARGET(kMove);
	int piece = GET_MOVE_PIECE(kMove);

	int _2pawn = GET_MOVE_2_PAWN(kMove);
	int en_passant = GET_MOVE_EN_PASSANT(kMove);
	int castle = GET_MOVE_CASTLE(kMove);

	int promotion = GET_MOVE_PROMOTION(kMove);
	int capture = GET_MOVE_CAPTURE(kMove);


	if (castle) {
		if (kSide) {
			if (castle == 1) {
				POP_BIT(bb[6], 58);
				SET_BIT(bb[6], 60);

				POP_BIT(bb[4], 59);
				SET_BIT(bb[4], 56);
			}

			else if (castle == 2) {
				POP_BIT(bb[6], 62);
				SET_BIT(bb[6], 60);

				POP_BIT(bb[4], 61);
				SET_BIT(bb[4], 63);
			}
		}

		else {
			if (castle == 3) {
				POP_BIT(bb[12], 2);
				SET_BIT(bb[12], 4);

				POP_BIT(bb[10], 3);
				SET_BIT(bb[10], 0);
			}

			else if (castle == 4) {
				POP_BIT(bb[12], 6);
				SET_BIT(bb[12], 4);

				POP_BIT(bb[10], 5);
				SET_BIT(bb[10], 7);
			}
		}
	}

	else if (promotion) {
		POP_BIT(bb[promotion], target);
		SET_BIT(bb[piece], source);

		if (capture) SET_BIT(bb[capture], target);
	}

	else if (en_passant) {
		POP_BIT(bb[piece], target);
		SET_BIT(bb[piece], source);

		if (kSide) SET_BIT(bb[7], target + 8);
		else SET_BIT(bb[1], target - 8);
	}

	else if (capture) {
		POP_BIT(bb[piece], target);
		SET_BIT(bb[piece], source);

		SET_BIT(bb[capture], target);
	}

	else {
		POP_BIT(bb[piece], target);
		SET_BIT(bb[piece], source);
	}
}


// Initialization
inline void IterateBoard(Board& b, const int kPosition[8][8]) {

	for (int i = 0; i < 13; ++i) {
		b.bb[i] = 0ULL;
	}

	int square;

	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {

			square = (7 - y) * 8 + x;

			switch (kPosition[x][y]) {

				case 1000:
					b.bb[1] |= 1ULL << square;
					break;

				case 3000:
					b.bb[2] |= 1ULL << square;
					break;

				case 3100:
					b.bb[3] |= 1ULL << square;
					break;

				case 5000:
					b.bb[4] |= 1ULL << square;
					break;

				case 9000:
					b.bb[5] |= 1ULL << square;
					break;

				case 100000:
					b.bb[6] |= 1ULL << square;
					break;





				case -1000:
					b.bb[7] |= 1ULL << square;
					break;

				case -3000:
					b.bb[8] |= 1ULL << square;
					break;

				case -3100:
					b.bb[9] |= 1ULL << square;
					break;

				case -5000:
					b.bb[10] |= 1ULL << square;
					break;

				case -9000:
					b.bb[11] |= 1ULL << square;
					break;

				case -100000:
					b.bb[12] |= 1ULL << square;
					break;



				default:
					0;
			}
		}
	}
}

void Board::Initialize(const int kBoardType, const int kBoardIndex) {

	if (kBoardType == 0) {
		IterateBoard(*this, kBoardRegular[kBoardIndex]);
	}

	else if (kBoardType == 1) {
		IterateBoard(*this, kBoardTactic[kBoardIndex]);
	}

	else {
		IterateBoard(*this, kBoardSmall[kBoardIndex]);
	}
}