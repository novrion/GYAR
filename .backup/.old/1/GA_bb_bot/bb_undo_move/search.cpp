#include "beta.h"

using namespace std;
using namespace std::chrono;



const int material_score[13] = { 0, 1000, 3000, 3000, 5000, 9000, 100000, -1000, -3000, -3000, -5000, -9000, -100000 };
const int position[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 3, 3, 2, 1, 0,
	0, 2, 3, 4, 4, 3, 2, 0,
	0, 3, 4, 5, 5, 4, 3, 0,
	0, 3, 4, 5, 5, 4, 3, 0,
	0, 2, 3, 4, 4, 3, 2, 0,
	0, 1, 2, 3, 3, 2, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};



//int nodes = 0;
void playBot() {

	int depth;
	cout << "depth: ";
	cin >> depth;

	Board b{};
	double average_times[3][5] = {};

	for (int board_type = 0; board_type < 3; ++board_type) {
		for (int board_index = 0; board_index < 5; ++board_index) {

			b.initialize( board_type, board_index );

			int evaluation;

			double time_total = 0;

			duration<double> time;
			time_point<high_resolution_clock> start_time;


			for (int i = 0; i < 100; ++i) {

				//nodes = 0;

				start_time = high_resolution_clock::now();

				evaluation = minimax( b, depth, true );

				time = high_resolution_clock::now() - start_time;
				time_total += time.count();

				cout << "[" << i + 1 << "] " << time.count() << "\n";
			}

			average_times[board_type][board_index] = time_total / 100;
			cout << "\n\nAverage time: " << time_total / 100 << " s\n\n";

			//cout << "\n\nnodes: " << nodes;
		}
	}





	cout << "----------------------------------- DATA ------------------------------------------\n\n";
	cout << "Average time taken for each position measured in seconds:\n\n\n";
	for (int i = 0; i < 3; ++i) {

		if (i == 0) cout << "---------- Regular positions ----------\n\n";
		else if (i == 1) cout << "---------- Tactic positions ----------\n\n";
		else cout << "---------- Small positions ----------\n\n";

		for (int j = 0; j < 5; ++j) {
			cout << "[" << j + 1 << "] " << average_times[i][j] << "\n";
		}

		cout << "\n\n";
	}
	cout << "----------------------------------- DATA ------------------------------------------\n\n\n\n";
}



static inline int bitCount( U64 x ) {

	x -= (x >> 1) & 0x5555555555555555;
	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
	x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;

	return ((x * 0x0101010101010101) >> 56);
}
static inline int popLsb( U64& b ) {

	const int s = __builtin_ctzll( b );
	b &= b - 1;

	return s;
}


static inline int materialScore( const U64 bb[13] ) {

	int total = 0;

	for (int board = 1; board < 7; ++board) {
		total += material_score[board] * bitCount( bb[board] );
		total += material_score[board + 6] * bitCount( bb[board + 6] );
	}

	return total;
}
static inline int positionScore( const U64 bb[13] ) {

	int total = 0;
	U64 pieceBitboard;

	for (int i = 1; i < 7; i++) {

		// white pieces
		pieceBitboard = bb[i];

		while (pieceBitboard) {
			int location = popLsb( pieceBitboard );
			total += position[location];
		}


		// black pieces
		pieceBitboard = bb[i + 6];

		while (pieceBitboard) {
			int location = popLsb( pieceBitboard );
			total -= position[location];
		}
	}

	return total;
}


static inline int evaluate( const U64 bb[13] ) {

	int evaluation = 0;

	evaluation += materialScore( bb );
	evaluation += positionScore( bb );

	return evaluation;
}





static inline int minimax( Board& b, int depth, bool colour ) {

	//nodes += 1;

	if (!depth) return evaluate( b.bb );

	int evaluation;

	U64 moves[100];
	moves[99] = 0;
	generateMoves( b.bb, (colour ? 1 : 0), moves );


	if (colour) {

		int maxEval = -999999;

		for (int i = 0; i < moves[99]; ++i) {

			makeMove( b.bb, moves[i], colour );
			evaluation = minimax( b, depth - 1, false );

			/* Undo move */
			undoMove( b.bb, moves[i] );



			if (evaluation > maxEval) maxEval = evaluation;
		}

		return maxEval;
	}


	else {

		int minEval = 999999;

		for (int i = 0; i < moves[99]; ++i) {

			makeMove( b.bb, moves[i], colour );
			evaluation = minimax( b, depth - 1, true );

			/* Undo move */
			undoMove( b.bb, moves[i] );



			if (evaluation < minEval) minEval = evaluation;
		}

		return minEval;
	}
}