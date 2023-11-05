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

      printf("FEN: %s", fen[board_type][board_index]);
      printf("        [0]         [1]         [2]         [3]         [4]         [5]         [6]         [7]         [8]         [9]");

      for (int i = 0; i < 100; ++i) {

        if (i % 10 == 0) printf("\n[%i] ", i / 10);

        //nodes = 0;

        time_start = high_resolution_clock::now();

        evaluation = Minimax(b, depth, -999999, 999999, b.side);

        time = high_resolution_clock::now() - time_start;
        time_total += time.count();

        printf("%.9f ", time.count());
      }

      average_times[board_type][board_index] = time_total / kNTests;
      printf("\n[AVERAGE] %.9f s\n\n", average_times[board_type][board_index]);

      // printf("FEN: %s", fen[board_type][board_index]);
      // printf("nodes: %i\n\n", nodes);
    }
  }



  printf("----------------------------------- AVERAGES ------------------------------------------\n\n");

  for (int i = 0; i < 3; ++i) {

    if (i == 0 && n_position[i]) printf("\n---------- REGULAR POSITIONS ----------\n\n");
    else if (i == 1 && n_position[i]) printf("\n---------- TACTICAL POSITINOS ----------\n\n");
    else if (n_position[i]) printf("\n---------- SMALL POSITIONS ----------\n\n");

    for (int j = 0; j < n_position[i]; ++j) {
      if (j < 10) printf(" ");
      printf("[%i] %.9f\n", j, average_times[i][j]);
    }
  }
  printf("\n\n----------------------------------- AVERAGES ------------------------------------------\n\n");

  printf("\n\n\n\n\n---------- COPY PASTE ----------\n\n");

  printf("TIME (s)\n");
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < n_position[i]; ++j) {
      printf("%.9f\n", average_times[i][j]);
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

  //nodes += 1;

  if (!kDepth) return Evaluate(b);

  int evaluation;

  Move moves[100];
  moves[99] = Move(0, 0, 0, 0, 0);
  GenerateMoves(b, moves, kSide);

  const int en_passant_x = b.en_passant_x;
  const int en_passant_y = b.en_passant_y;
  const bool w_l_castle = b.w_l_castle;
  const bool w_r_castle = b.w_r_castle;
  const bool b_l_castle = b.b_l_castle;
  const bool b_r_castle = b.b_r_castle;



  if (kSide) {

    int max_eval = -999999;

    for (int i = 0; i < moves[99].from_x; ++i) {

      if (moves[i].capture == -100000) return (100000 + kDepth);


      MakeMove(b, moves[i]);
      evaluation = Minimax(b, kDepth - 1, alpha, beta, false);
      UndoMove(b, moves[i], en_passant_x, en_passant_y, w_l_castle, w_r_castle, b_l_castle, b_r_castle);


      if (evaluation > max_eval) max_eval = evaluation;
    }

    return max_eval;
  }


  else {

    int min_eval = 999999;

    for (int i = 0; i < moves[99].from_x; ++i) {

      if (moves[i].capture == 100000) return (-100000 - kDepth);


      MakeMove(b, moves[i]);
      evaluation = Minimax(b, kDepth - 1, alpha, beta, true);
      UndoMove(b, moves[i], en_passant_x, en_passant_y, w_l_castle, w_r_castle, b_l_castle, b_r_castle);


      if (evaluation < min_eval) min_eval = evaluation;
    }

    return min_eval;
  }
}