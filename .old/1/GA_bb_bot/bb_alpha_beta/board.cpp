#include "beta.h"

using namespace std;


const U64 capture_mask = 8388607ULL;

const int board_regular[kNPositions][8][8] = {

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

const int board_tactic[kNPositions][8][8] = {

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

const int board_small[kNPositions][8][8] = {

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


static inline void iterateBoard( Board& b, const int position[8][8] ) {

	for (int i = 0; i < 13; ++i) {
		b.bb[i] = 0ULL;
	}

	int square;

	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {

			square = (7 - y) * 8 + x;

			switch (position[x][y]) {

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

void Board::initialize( int board_type, int board_index ) {

	if (board_type == 0) {
		iterateBoard(*this, board_regular[board_index]);
	}

	else if (board_type == 1) {
		iterateBoard(*this, board_tactic[board_index]);
	}

	else {
		iterateBoard(*this, board_small[board_index]);
	}
}




void makeMove( U64 bb[13], U64& move, bool colour ) {

	int source = get_move_from( move );
	int target = get_move_to( move );
	int piece = get_move_piece( move );
	int capture = get_move_capture( move );

	if (!capture) {

		pop_bit( bb[piece], source );
		set_bit( bb[piece], target );
	}

	else {

		pop_bit( bb[piece], source );
		set_bit( bb[piece], target );


		if (colour) {
			for (int i = 7; i < 13; i++) {
				if (1ULL << target & bb[i]) {
					pop_bit( bb[i], target );
					move &= capture_mask;
					move |= (i << 23);
					break;
				}
			}
		}

		else {
			for (int i = 1; i < 7; i++) {
				if (1ULL << target & bb[i]) {
					pop_bit( bb[i], target );
					move &= capture_mask;
					move |= (i << 23);
					break;
				}
			}
		}
	}
}