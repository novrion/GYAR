#include "search.h"

using namespace std;
using namespace std::chrono;



//int nodes = 0;
void PlayBot() {

  int depth;
	cin >> depth;

	int n_position[3];
	cin >> n_position[0] >> n_position[1] >> n_position[2];

	string fen[3][kNMaxFen];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < n_position[i]; ++j) {
			cin >> fen[i][j];
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
      time_point<high_resolution_clock> start_time;


      for (int i = 0; i < kNTests; ++i) {

        //nodes = 0;

        start_time = high_resolution_clock::now();

        evaluation = Minimax(b, depth, -999999, 999999, b.side);

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

    for (int j = 0; j < n_position[i]; ++j) {
      cout << "[" << j + 1 << "] " << average_times[i][j] << "\n";
    }

    cout << "\n\n";
  }
  cout << "----------------------------------- DATA ------------------------------------------\n\n\n\n";
}



// Evaluation
inline int Evaluate(Board& b) {

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



// Minimax
inline int Minimax(Board& b, const int kDepth, int alpha, int beta, const bool kSide) {

  //nodes += 1;

  if (!kDepth) return Evaluate(b);

  Board b_copy;
  int evaluation;

  Move moves[100];
  moves[99] = Move(0, 0, 0, 0, 0);
  GenerateMoves(b, moves, kSide);



  if (kSide) {

    int max_eval = -999999;

    for (int i = 0; i < moves[99].from_x; ++i) {

      b_copy = b;
      MakeMove(b_copy, moves[i]);

      evaluation = Minimax(b_copy, kDepth - 1, alpha, beta, false);


      if (evaluation > max_eval) max_eval = evaluation;
    }

    return max_eval;
  }


  else {

    int min_eval = 999999;

    for (int i = 0; i < moves[99].from_x; ++i) {

      b_copy = b;
      MakeMove(b_copy, moves[i]);

      evaluation = Minimax(b_copy, kDepth - 1, alpha, beta, true);


      if (evaluation < min_eval) min_eval = evaluation;
    }

    return min_eval;
  }
}