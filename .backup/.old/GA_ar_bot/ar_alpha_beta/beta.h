#pragma once

#include <algorithm>
#include <iostream>
#include <chrono>
#include <map>


const int kNPositions = 10;
const int kNTests = 100;



struct Move {

	Move() {

		from_x = -1;
		from_y = 0;
		to_x = 0;
		to_y = 0;

		capture = 0;
	}

	Move(int f_x, int f_y, int t_x, int t_y, int _capture) {

		from_x = f_x;
		from_y = f_y;
		to_x = t_x;
		to_y = t_y;

		capture = _capture;
	}

	int from_x, from_y, to_x, to_y;
	int capture;
};

struct Board {

	int board[8][8];

	void initialize(int board_type, int board_index);
};


static inline int minimax(Board& b, int depth, int alpha, int beta, bool color);


void makeMove(Board& b, Move& move);


void generateMoves(Board& b, Move moves[100], bool player, bool onlyCapture);

static inline void generatePawnMoves(Board& b, Move moves[100], int pos_x, int pos_y);
static inline void generateHorseMoves(Board& b, Move moves[100], int pos_x, int pos_y);
static inline void generateBishopMoves(Board& b, Move moves[100], int pos_x, int pos_y);
static inline void generateRookMoves(Board& b, Move moves[100], int pos_x, int pos_y);
static inline void generateQueenMoves(Board& b, Move moves[100], int pos_x, int pos_y);
static inline void generateKingMoves(Board& b, Move moves[100], int pos_x, int pos_y);


void playBot();