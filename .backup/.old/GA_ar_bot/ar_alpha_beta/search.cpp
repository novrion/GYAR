#include "beta.h"

using namespace std;
using namespace std::chrono;


const int position_matrix[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 2, 3, 3, 2, 1, 0},
	{0, 2, 3, 4, 4, 3, 2, 0},
	{0, 3, 4, 5, 5, 4, 3, 0},
	{0, 3, 4, 5, 5, 4, 3, 0},
	{0, 2, 3, 4, 4, 3, 2, 0},
	{0, 1, 2, 3, 3, 2, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};



//int nodes = 0;
void playBot() {

	int depth;
	cout << "depth: ";
	cin >> depth;

	Board b{};
	double average_times[3][kNPositions] = {};

	for (int board_type = 0; board_type < 3; ++board_type) {
		for (int board_index = 0; board_index < kNPositions; ++board_index) {

			b.initialize( board_type, board_index );

			int evaluation;

			double time_total = 0;

			duration<double> time;
			time_point<high_resolution_clock> start_time;


			for (int i = 0; i < kNTests; ++i) {

				//nodes = 0;

				start_time = high_resolution_clock::now();

				evaluation = minimax( b, depth, -999999, 999999, true );

				time = high_resolution_clock::now() - start_time;
				time_total += time.count();

				cout << "[" << i + 1 << "] " << time.count() << "\n";
			}

			average_times[board_type][board_index] = time_total / kNTests;
			cout << "\n\nAverage time: " << time_total / kNTests << " s\n\n";

			//cout << "\n\nnodes: " << nodes;
		}
	}




	cout << "----------------------------------- DATA ------------------------------------------\n\n";
	cout << "Average time taken for each position measured in seconds:\n\n\n";
	for (int i = 0; i < 3; ++i) {

		if (i == 0) cout << "---------- Regular positions ----------\n\n";
		else if (i == 1) cout << "---------- Tactic positions ----------\n\n";
		else cout << "---------- Small positions ----------\n\n";

		for (int j = 0; j < kNPositions; ++j) {
			cout << "[" << j + 1 << "] " << average_times[i][j] << "\n";
		}

		cout << "\n\n";
	}
	cout << "----------------------------------- DATA ------------------------------------------\n\n\n\n";
}




static inline int evaluation( Board& b ) {

	int eval = 0;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			if (!b.board[x][y]) {
				continue;
			}

			else if (b.board[x][y] > 0) {
				eval += b.board[x][y] + position_matrix[x][y];
			}

			else {
				eval += b.board[x][y] - position_matrix[x][y];
			}
		}
	}

	return eval;
}

static inline int minimax( Board& b, int depth, int alpha, int beta, bool color ) {

	//nodes += 1;

	if (depth == 0) return evaluation( b );


	Board b_copy;
	int evaluation;

	Move moves[100];
	moves[99] = Move( 0, 0, 0, 0, 0 );
	generateMoves( b, moves, color, false );



	if (color) {

		int maxEval = -999999;

		for (int i = 0; i < moves[99].from_x; ++i) {

			b_copy = b;
			makeMove( b_copy, moves[i] );

			evaluation = minimax( b_copy, depth - 1, alpha, beta, false );


			if (evaluation > maxEval) maxEval = evaluation;

			/* Alpha beta pruning */
			alpha = max( alpha, evaluation );
			if (beta <= alpha) break;
		}

		return maxEval;
	}


	else {

		int minEval = 999999;

		for (int i = 0; i < moves[99].from_x; ++i) {

			b_copy = b;
			makeMove( b_copy, moves[i] );

			evaluation = minimax( b_copy, depth - 1, alpha, beta, true );



			if (evaluation < minEval) minEval = evaluation;

			/* Alpha beta pruning */
			beta = min( beta, evaluation );
			if (beta <= alpha) break;
		}

		return minEval;
	}
}