#include "search.h"
#include "a.h"

using namespace std;
using namespace std::chrono;

int A::acastle = 0; int A::apromotion = 0; int A::aen_passant = 0; int A::adouble_pawn = 0;


int nodes = 0;
void PlayBot() {

	int depth;
	cout << "depth: ";
	cin >> depth;

	Board b{};
	double average_times[3][kNPositions] = {};

	for (int board_type = 0; board_type < 3; ++board_type) {
		for (int board_index = 0; board_index < kNPositions; ++board_index) {

			b.Initialize(board_type, board_index);

			int evaluation;

			double time_total = 0;

			duration<double> time;
			time_point<high_resolution_clock> start_time;


			for (int i = 0; i < kNTests; ++i) {

				nodes = 0;

				start_time = high_resolution_clock::now();

				A::acastle = 0; A::apromotion = 0; A::aen_passant = 0; A::adouble_pawn = 0;

				evaluation = Minimax(b, depth, -999999, 999999, true);

				time = high_resolution_clock::now() - start_time;
				time_total += time.count();

				cout << "[" << i + 1 << "] " << time.count() << "eval: " << evaluation << " " << "other: " << A::acastle << " " << A::apromotion << " " << A::aen_passant << " " << A::adouble_pawn << "\n";
			}

			average_times[board_type][board_index] = time_total / kNTests;
			cout << "\n\nAverage time: " << time_total / kNTests << " s\n\n";

			cout << "\n\nnodes: " << nodes;
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





// Bit Manipulation
inline int BitCount(U64 x) {

	x -= (x >> 1) & 0x5555555555555555;
	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
	x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;

	return ((x * 0x0101010101010101) >> 56);
}





// Evaluation
inline int MaterialScore(const U64 kBB[13]) {

	int total = 0;

	for (int board = 1; board < 7; ++board) {
		total += kMaterialScore[board] * BitCount(kBB[board]);
		total += kMaterialScore[board + 6] * BitCount(kBB[board + 6]);
	}

	return total;
}

inline int PositionScore(const U64 kBB[13]) {

	int total = 0;
	U64 pieceBitboard;

	for (int i = 1; i < 7; i++) {

		// white pieces
		pieceBitboard = kBB[i];

		while (pieceBitboard) {
			int location = PopLsb(pieceBitboard);
			total += kPositionScore[location];
		}


		// black pieces
		pieceBitboard = kBB[i + 6];

		while (pieceBitboard) {
			int location = PopLsb(pieceBitboard);
			total -= kPositionScore[location];
		}
	}

	return total;
}

inline int Evaluate(const U64 kBB[13]) {

	int evaluation = 0;

	evaluation += MaterialScore(kBB);
	evaluation += PositionScore(kBB);

	return evaluation;
}





// Minimax
inline int Minimax(Board& b, const int kDepth, int alpha, int beta, const bool kSide) {

	nodes += 1;

	if (!kDepth) return Evaluate(b.bb);

	int evaluation;

	U64 moves[100];
	moves[99] = 0;
	GenerateMoves(b.bb, moves, kSide);

	const U64 kUtil = b.bb[0];



	if (kSide) {

		int max_eval = -999999;

		for (int i = 0; i < moves[99]; ++i) {

			MakeMove(b.bb, moves[i], kSide);

			evaluation = Minimax(b, kDepth - 1, alpha, beta, false);

			UndoMove(b.bb, moves[i], true, kUtil);


			if (evaluation > max_eval) max_eval = evaluation;
		}

		return max_eval;
	}


	else {

		int min_eval = 999999;

		for (int i = 0; i < moves[99]; ++i) {

			MakeMove(b.bb, moves[i], kSide);

			evaluation = Minimax(b, kDepth - 1, alpha, beta, true);

			UndoMove(b.bb, moves[i], false, kUtil);


			if (evaluation < min_eval) min_eval = evaluation;
		}

		return min_eval;
	}
}