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

  for (int board_type = 0; board_type < 3; ++board_type) {
    for (int board_index = 0; board_index < n_position[board_type]; ++board_index) {

			b.Initialize(fen[board_type][board_index]);

      int evaluation;
      double time_total = 0;
      duration<double> time;
      time_point<high_resolution_clock> time_start;

      for (int i = 0; i < kNTests; ++i) {

        //nodes = 0;

        time_start = high_resolution_clock::now();

        evaluation = Minimax(b, depth, -999999, 999999, GET_UTILITY_SIDE(b.bb[0]));

        time = high_resolution_clock::now() - time_start;
        time_total += time.count();

        printf("[%i] %.9f\n", i+1, time.count());
      }

      average_times[board_type][board_index] = time_total / kNTests;
      printf("[AVERAGE] %.9f s\n\n", average_times[board_type][board_index]);

      //printf("nodes: %i\n\n\n\n", nodes);
    }
  }





  printf("----------------------------------- AVERAGES ------------------------------------------\n\n");
  for (int i = 0; i < 3; ++i) {

    if (i == 0 && n_position[i]) printf("---------- REGULAR POSITIONS ----------\n\n");
    else if (i == 1 && n_position[i]) printf("---------- TACTICAL POSITINOS ----------\n\n");
    else if (n_position[i]) printf("---------- SMALL POSITIONS ----------\n\n");

    for (int j = 0; j < n_position[i]; ++j) {
      printf("[%i] %.9f\n", j + 1, average_times[i][j]);
    }
  }
  printf("\n----------------------------------- AVERAGES ------------------------------------------\n\n\n\n");
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

	//nodes += 1;

	if (!kDepth) return Evaluate(b.bb);

	Board b_copy;
	int evaluation;

	U64 moves[100];
	moves[99] = 0;
	GenerateMoves(b.bb, moves, kSide);



	if (kSide) {

		int max_eval = -999999;

		for (int i = 0; i < moves[99]; ++i) {

			b_copy = b;
			MakeMove(b_copy.bb, moves[i], kSide);

			evaluation = Minimax(b_copy, kDepth - 1, alpha, beta, false);


			if (evaluation > max_eval) max_eval = evaluation;


			// Alpha Beta Pruning
			if (evaluation > alpha) alpha = evaluation;
			if (beta <= alpha) break;
		}

		return max_eval;
	}


	else {

		int min_eval = 999999;

		for (int i = 0; i < moves[99]; ++i) {

			b_copy = b;
			MakeMove(b_copy.bb, moves[i], kSide);

			evaluation = Minimax(b_copy, kDepth - 1, alpha, beta, true);


			if (evaluation < min_eval) min_eval = evaluation;


			// Alpha Beta Pruning
			if (evaluation < beta) beta = evaluation;
			if (beta <= alpha) break;
		}

		return min_eval;
	}
}