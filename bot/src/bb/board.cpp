#include "board.h"


const std::map<char, int> kIPiece = {
	{'P', 1},
	{'N', 2},
	{'B', 3},
	{'R', 4},
	{'Q', 5},
	{'K', 6},

	{'p', 7},
	{'n', 8},
	{'b', 9},
	{'r', 10},
	{'q', 11},
	{'k', 12}
};



void MakeMove(U64 bb[13], U64& move, const bool kSide) {

	int source = GET_MOVE_SOURCE(move);
	int target = GET_MOVE_TARGET(move);
	int piece = GET_MOVE_PIECE(move);

	int double_pawn = GET_MOVE_2_PAWN(move);
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

		POP_BIT(bb[capture], target);
	}

	else if (castle) {

		if (target == 58) {

			POP_BIT(bb[6], 60);
			SET_BIT(bb[6], 58);

			POP_BIT(bb[4], 56);
			SET_BIT(bb[4], 59);
		}

		else if (target == 62) {

			POP_BIT(bb[6], 60);
			SET_BIT(bb[6], 62);

			POP_BIT(bb[4], 63);
			SET_BIT(bb[4], 61);
		}


		else if (target == 2) {

			POP_BIT(bb[12], 4);
			SET_BIT(bb[12], 2);

			POP_BIT(bb[10], 0);
			SET_BIT(bb[10], 3);
		}

		else {

			POP_BIT(bb[12], 4);
			SET_BIT(bb[12], 6);

			POP_BIT(bb[10], 7);
			SET_BIT(bb[10], 5);
		}
	}

	else if (promotion) {

		POP_BIT(bb[piece], source);
		SET_BIT(bb[promotion], target);
	}

	else if (en_passant) {

		POP_BIT(bb[piece], source);
		SET_BIT(bb[piece], target);

		if (kSide) POP_BIT(bb[7], target + 8);
		else POP_BIT(bb[1], target - 8);
	}

	else if (double_pawn) {

		POP_BIT(bb[piece], source);
		SET_BIT(bb[piece], target);

		bb[0] |= target;
	}

	else {

		POP_BIT(bb[piece], source);
		SET_BIT(bb[piece], target);
	}
}

void UndoMove(U64 bb[13], const U64 kMove, const bool kSide, const U64 kUtil) {

	bb[0] = kUtil;

	int source = GET_MOVE_SOURCE(kMove);
	int target = GET_MOVE_TARGET(kMove);
	int piece = GET_MOVE_PIECE(kMove);

	int en_passant = GET_MOVE_EN_PASSANT(kMove);
	int castle = GET_MOVE_CASTLE(kMove);

	int promotion = GET_MOVE_PROMOTION(kMove);
	int capture = GET_MOVE_CAPTURE(kMove);



	if (castle) {

		if (target == 58) {
			POP_BIT(bb[6], 58);
			SET_BIT(bb[6], 60);

			POP_BIT(bb[4], 59);
			SET_BIT(bb[4], 56);
		}

		else if (target == 62) {
			POP_BIT(bb[6], 62);
			SET_BIT(bb[6], 60);

			POP_BIT(bb[4], 61);
			SET_BIT(bb[4], 63);
		}


		else if (target == 2) {
			POP_BIT(bb[12], 2);
			SET_BIT(bb[12], 4);

			POP_BIT(bb[10], 3);
			SET_BIT(bb[10], 0);
		}

		else {
			POP_BIT(bb[12], 6);
			SET_BIT(bb[12], 4);

			POP_BIT(bb[10], 5);
			SET_BIT(bb[10], 7);
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


inline int NotationToSquare(const char letter, const char number) {
	return (letter - 97) + (8 - (number - '0')) * 8;
}

inline void ParseFen(Board& b, const char kFen[80]) {

	for (int i = 0; i < 13; ++i) {
		b.bb[i] = 0ULL;
	}

	int stage = 0;
	int square = 0;

	for (int i = 0; i < 100; ++i) {

		if (kFen[i] == ' ') ++stage;


		if (!stage) {

			if (kFen[i] == '/') continue;
			else if (kFen[i] > 47 && kFen[i] < 58) square += kFen[i] - '0';
			else {
				b.bb[kIPiece.at(kFen[i])] |= 1ULL << square;
				++square;
			}
		}

		else if (stage == 1) {
			kFen[++i] == 'w' ? b.bb[0] |= 1ULL << 10 : 0;
		}

		else if (stage == 2) {

			if (kFen[i] == 'K') b.bb[0] |= 1ULL << 6;
			else if (kFen[i] == 'Q') b.bb[0] |= 1ULL << 7;
			else if (kFen[i] == 'k') b.bb[0] |= 1ULL << 8;
			else if (kFen[i] == 'q') b.bb[0] |= 1ULL << 9;
		}

		else if (stage == 3) {

			if (kFen[i + 1] == '-') break;
			else {
				b.bb[0] |= NotationToSquare(kFen[i + 1], kFen[i + 2]);
				break;
			}
		}
	}
}

void Board::Initialize(const char kFen[80]) {
	ParseFen(*this, kFen);
}