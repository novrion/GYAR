#include "board.h"

using namespace std;



// Make Move
void MakeMove( U64 bb[13], U64& move, const bool KSide ) {

	int source = GET_MOVE_SOURCE( move );
	int target = GET_MOVE_TARGET( move );
	int piece = GET_MOVE_PIECE( move );
	int capture = GET_MOVE_CAPTURE( move );


	if (!capture) {
		POP_BIT( bb[piece], source );
		SET_BIT( bb[piece], target );
	}

	else {
		POP_BIT( bb[piece], source );
		SET_BIT( bb[piece], target );

		if (KSide) {
			for (int i = 7; i < 13; i++) {
				if (1ULL << target & bb[i]) {
					POP_BIT( bb[i], target );
					move &= capture_mask;
					move |= (i << 23);
					break;
				}
			}
		}

		else {
			for (int i = 1; i < 7; i++) {
				if (1ULL << target & bb[i]) {
					POP_BIT( bb[i], target );
					move &= capture_mask;
					move |= (i << 23);
					break;
				}
			}
		}
	}
}

// Undo Move
void UndoMove( U64 bb[13], const U64 kMove ) {

	int source = GET_MOVE_SOURCE( kMove );
	int target = GET_MOVE_TARGET( kMove );
	int piece = GET_MOVE_PIECE( kMove );
	int capture = GET_MOVE_CAPTURE( kMove );


	if (!capture) {
		POP_BIT( bb[piece], target );
		SET_BIT( bb[piece], source );
	}

	else {
		POP_BIT( bb[piece], target );
		SET_BIT( bb[piece], source );

		SET_BIT( bb[capture], target );
	}
}


// Initialization
inline void IterateBoard( Board& b, const int kPosition[8][8] ) {

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

void Board::Initialize( const int kBoardType, const int kBoardIndex ) {

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