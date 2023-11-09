#include "search.h"

using namespace std;
using namespace std::chrono;



//int nodes = 0;
void PlayBot() {

	int depth;
	scanf("%i", &depth);

	int n_position[3];
	scanf("%i", &n_position[0]);
	scanf("%i", &n_position[1]);
	scanf("%i", &n_position[2]);

	char fen[3][kNMaxFen][80];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < kNMaxFen; ++j) {
			for (int k = 0; k < 80; ++k) {
				fen[i][j][k] = 0;
			}
		}
	}

	while (getchar() != '\n');

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < n_position[i]; ++j) {
			fgets(fen[i][j], 80, stdin);
		}
	}


	Board b;
	double average_times[3][kNMaxFen];
	double standard_deviations[3][kNMaxFen];

	for (int board_type = 0; board_type < 3; ++board_type) {
		for (int board_index = 0; board_index < n_position[board_type]; ++board_index) {

			b.Initialize(fen[board_type][board_index]);


			int evaluation;
			double time_total = 0;
			duration<double> time;
			time_point<high_resolution_clock> time_start;
			double times[101];

			printf("FEN: %s", fen[board_type][board_index]);
			printf("        [0]         [1]         [2]         [3]         [4]         [5]         [6]         [7]         [8]         [9]");


			for (int i = 0; i < 100; ++i) {

				if (i % 10 == 0) printf("\n[%i] ", i / 10);

				//nodes = 0;

				time_start = high_resolution_clock::now();

				evaluation = Minimax(b, depth, GET_UTILITY_SIDE(b.bb[0]));

				time = high_resolution_clock::now() - time_start;
				time_total += time.count();
				times[i] = time.count();

				printf("%.9f ", times[i]);
			}


			// Average time
			average_times[board_type][board_index] = time_total / kNTests;

			// Standard deviation
			double sum_deviation = 0;
			for (int i = 0; i < 100; ++i) { sum_deviation += (times[i] - average_times[board_type][board_index]) * (times[i] - average_times[board_type][board_index]); }
			standard_deviations[board_type][board_index] = sqrt(sum_deviation / 100);

			printf("\n[AVERAGE] %.9f s\n", average_times[board_type][board_index]);
			printf("[STANDARD DEVIATION] %.9f s\n\n", standard_deviations[board_type][board_index]);

			// printf("FEN: %s", fen[board_type][board_index]);
			// printf("nodes: %i\n\n", nodes);
		}
	}



	printf("----------------------------------- AVERAGES ------------------------------------------\n\n");

	for (int i = 0; i < 3; ++i) {

		if (i == 0 && n_position[i]) printf("\n---------- REGULAR POSITIONS ----------\n\n");
		else if (i == 1 && n_position[i]) printf("\n---------- TACTICAL POSITINOS ----------\n\n");
		else if (n_position[i]) printf("\n---------- SMALL POSITIONS ----------\n\n");

		printf("    [AVERAGE (s)]    [STANDARD DEVIATION (s)]\n");

		for (int j = 0; j < n_position[i]; ++j) {
			if (j < 10) printf(" ");
			printf("[%i] %.9f          %.9f\n", j, average_times[i][j], standard_deviations[i][j]);
		}
	}
	printf("\n\n----------------------------------- AVERAGES ------------------------------------------\n\n");

	printf("\n\n\n\n---------- SUMMARY ----------\n\n");

	printf("[bb undo move] AVERAGE AVERAGE TIMES (s)\n");

	// Average average times
	double final_averages[3];
	for (int type = 0; type < 3; ++type) {

		double sum_averages = 0;
		for (int i = 0; i < n_position[type]; ++i) { sum_averages += average_times[type][i]; }
		final_averages[type] = sum_averages / n_position[type];
		
		printf("%.9f\n", final_averages[type]);
	}

	printf("\n");
	printf("[bb undo move] AVERAGE STANDARD DEVIATIONS (s)\n");	

	// Average standard deviations
	double average_standard_deviations[3];
	for (int type = 0; type < 3; ++type) {

		double final_sum_deviation = 0;
		for (int i = 0; i < n_position[type]; ++i) { final_sum_deviation += standard_deviations[type][i] * standard_deviations[type][i]; }
		average_standard_deviations[type] = sqrt(final_sum_deviation / n_position[type]);

		printf("%.9f\n", average_standard_deviations[type]);
	}
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

inline void GetMoveCaptures(Board& b, U64 moves[100], const bool kSide) {

	if (kSide) {
		for (int i = 0; i < moves[99]; ++i) {
			if (!GET_MOVE_CAPTURE(moves[i])) continue;

			for (int j = 7; j < 13; ++j) {
				if (b.bb[j] & (1ULL << GET_MOVE_TARGET(moves[i]))) {
					moves[i] &= kCaptureMask;
					SET_MOVE_CAPTURE(moves[i], j);
					break;
				}
			}
		}
	}

	else {
		for (int i = 0; i < moves[99]; ++i) {
			if (!GET_MOVE_CAPTURE(moves[i])) continue;

			for (int j = 1; j < 7; ++j) {
				if (b.bb[j] & (1ULL << GET_MOVE_TARGET(moves[i]))) {
					moves[i] &= kCaptureMask;
					SET_MOVE_CAPTURE(moves[i], j);
					break;
				}
			}
		}
	}

	return;
}

// Search Function
inline int Minimax(Board& b, const int kDepth, const bool kSide) {

	//nodes += 1;

	if (!kDepth) return Evaluate(b.bb);

	int evaluation;

	U64 moves[100];
	moves[99] = 0;
	GenerateMoves(b.bb, moves, kSide);

	// Necessary for if king capture !
	GetMoveCaptures(b, moves, kSide);

	const U64 kUtil = b.bb[0];



	if (kSide) {

		int max_eval = -999999;

		for (int i = 0; i < moves[99]; ++i) {

			if (1ULL << GET_MOVE_TARGET(moves[i]) & b.bb[12]) return (kMaterialScore[6] + kDepth);

			MakeMove(b.bb, moves[i], kSide);

			evaluation = Minimax(b, kDepth - 1, false);

			UndoMove(b.bb, moves[i], kSide, kUtil);


			if (evaluation > max_eval) max_eval = evaluation;
		}

		return max_eval;
	}


	else {

		int min_eval = 999999;

		for (int i = 0; i < moves[99]; ++i) {

			if (1ULL << GET_MOVE_TARGET(moves[i]) & b.bb[6]) return (kMaterialScore[12] - kDepth);

			MakeMove(b.bb, moves[i], kSide);

			evaluation = Minimax(b, kDepth - 1, true);

			UndoMove(b.bb, moves[i], kSide, kUtil);


			if (evaluation < min_eval) min_eval = evaluation;
		}

		return min_eval;
	}
}