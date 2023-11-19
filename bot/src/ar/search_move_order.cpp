#include "search_alpha_beta.h"

using namespace std;
using namespace std::chrono;


int MVVLVA[2001][2001];



inline void InitializeMVVLVA(int hash[2001][2001]) {
	hash[1010][1010] = 105; hash[1010][1030] = 205; hash[1010][1031] = 305; hash[1010][1050] = 405; hash[1010][1090] = 505; hash[1010][2000] = 605; hash[1010][990] = 105; hash[1010][970] = 205; hash[1010][969] = 305; hash[1010][950] = 405; hash[1010][910] = 505; hash[1010][0] = 605; 
	hash[1030][1010] = 104; hash[1030][1030] = 204; hash[1030][1031] = 304; hash[1030][1050] = 404; hash[1030][1090] = 504; hash[1030][2000] = 604; hash[1030][990] = 104; hash[1030][970] = 204; hash[1030][969] = 304; hash[1030][950] = 404; hash[1030][910] = 504; hash[1030][0] = 604; 
	hash[1031][1010] = 103; hash[1031][1030] = 203; hash[1031][1031] = 303; hash[1031][1050] = 403; hash[1031][1090] = 503; hash[1031][2000] = 603; hash[1031][990] = 103; hash[1031][970] = 203; hash[1031][969] = 303; hash[1031][950] = 403; hash[1031][910] = 503; hash[1031][0] = 603; 
	hash[1050][1010] = 102; hash[1050][1030] = 202; hash[1050][1031] = 302; hash[1050][1050] = 402; hash[1050][1090] = 502; hash[1050][2000] = 602; hash[1050][990] = 102; hash[1050][970] = 202; hash[1050][969] = 302; hash[1050][950] = 402; hash[1050][910] = 502; hash[1050][0] = 602; 
	hash[1090][1010] = 101; hash[1090][1030] = 201; hash[1090][1031] = 301; hash[1090][1050] = 401; hash[1090][1090] = 501; hash[1090][2000] = 601; hash[1090][990] = 101; hash[1090][970] = 201; hash[1090][969] = 301; hash[1090][950] = 401; hash[1090][910] = 501; hash[1090][0] = 601; 
	hash[2000][1010] = 100; hash[2000][1030] = 200; hash[2000][1031] = 300; hash[2000][1050] = 400; hash[2000][1090] = 500; hash[2000][2000] = 600; hash[2000][990] = 100; hash[2000][970] = 200; hash[2000][969] = 300; hash[2000][950] = 400; hash[2000][910] = 500; hash[2000][0] = 600; 
	hash[990][1010] = 105; hash[990][1030] = 205; hash[990][1031] = 305; hash[990][1050] = 405; hash[990][1090] = 505; hash[990][2000] = 605; hash[990][990] = 105; hash[990][970] = 205; hash[990][969] = 305; hash[990][950] = 405; hash[990][910] = 505; hash[990][0] = 605; 
	hash[970][1010] = 104; hash[970][1030] = 204; hash[970][1031] = 304; hash[970][1050] = 404; hash[970][1090] = 504; hash[970][2000] = 604; hash[970][990] = 104; hash[970][970] = 204; hash[970][969] = 304; hash[970][950] = 404; hash[970][910] = 504; hash[970][0] = 604; 
	hash[969][1010] = 103; hash[969][1030] = 203; hash[969][1031] = 303; hash[969][1050] = 403; hash[969][1090] = 503; hash[969][2000] = 603; hash[969][990] = 103; hash[969][970] = 203; hash[969][969] = 303; hash[969][950] = 403; hash[969][910] = 503; hash[969][0] = 603; 
	hash[950][1010] = 102; hash[950][1030] = 202; hash[950][1031] = 302; hash[950][1050] = 402; hash[950][1090] = 502; hash[950][2000] = 602; hash[950][990] = 102; hash[950][970] = 202; hash[950][969] = 302; hash[950][950] = 402; hash[950][910] = 502; hash[950][0] = 602; 
	hash[910][1010] = 101; hash[910][1030] = 201; hash[910][1031] = 301; hash[910][1050] = 401; hash[910][1090] = 501; hash[910][2000] = 601; hash[910][990] = 101; hash[910][970] = 201; hash[910][969] = 301; hash[910][950] = 401; hash[910][910] = 501; hash[910][0] = 601; 
	hash[0][1010] = 100; hash[0][1030] = 200; hash[0][1031] = 300; hash[0][1050] = 400; hash[0][1090] = 500; hash[0][2000] = 600; hash[0][990] = 100; hash[0][970] = 200; hash[0][969] = 300; hash[0][950] = 400; hash[0][910] = 500; hash[0][0] = 600; 
}



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
	InitializeMVVLVA(MVVLVA);
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

				evaluation = Minimax(b, depth, -999999, 999999, b.side);

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

	// Average times
	for (int type = 0; type < 3; ++type) {
		for (int i = 0; i < n_position[type]; ++i) {
			printf("%.9f ", average_times[type][i]);
		}

		printf("\n");
	}
}



// Evaluation
inline int Evaluate(const Board& b) {

  int eval = 0;

  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {

      if (!b.board[x][y]) {
        continue;
      }

      else if (b.board[x][y] > 0) {
        eval += b.board[x][y] + kPositionScore[x][y];
      }

      else {
        eval += b.board[x][y] - kPositionScore[x][y];
      }
    }
  }

  return eval;
}



// Search Function
inline int Minimax(Board& b, const int kDepth, int alpha, int beta, const bool kSide) {

 // nodes += 1;

  if (!kDepth) return Evaluate(b);

  Board b_copy;
  int evaluation;

  Move moves[100];
  moves[99] = Move(0, 0, 0, 0, 0);
  GenerateMoves(b, moves, kSide);

  // Move Order
  sort(moves, moves + moves[99].from_x, [b](Move& c, Move& d) {return MVVLVA[1000 + b.board[c.from_x][c.from_y] / 10][1000 + c.capture / 10] > MVVLVA[1000 + b.board[d.from_x][d.from_y] / 10][1000 + d.capture / 10]; });



  if (kSide) {

    int max_eval = -999999;

    for (int i = 0; i < moves[99].from_x; ++i) {

      if (moves[i].capture == -10000) return (10000 + kDepth);

      b_copy = b;
      MakeMove(b_copy, moves[i]);

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

    for (int i = 0; i < moves[99].from_x; ++i) {

      if (moves[i].capture == 10000) return (-10000 - kDepth);

      b_copy = b;
      MakeMove(b_copy, moves[i]);

      evaluation = Minimax(b_copy, kDepth - 1, alpha, beta, true);


      if (evaluation < min_eval) min_eval = evaluation;

      // Alpha Beta Pruning
      if (evaluation < beta) beta = evaluation;
      if (beta <= alpha) break;
    }

    return min_eval;
  }
}