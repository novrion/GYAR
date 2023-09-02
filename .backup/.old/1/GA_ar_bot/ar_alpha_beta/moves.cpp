#include "beta.h"

using namespace std;



void generateMoves(Board& b, Move moves[100], bool player, bool onlyCapture) {

	if (player) {

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {

				if (b.board[x][y] == 0) continue;

				else if (b.board[x][y] == 1000) generatePawnMoves(b, moves, x, y);

				else if (b.board[x][y] == 3000) generateHorseMoves(b, moves, x, y);

				else if (b.board[x][y] == 3100) generateBishopMoves(b, moves, x, y);

				else if (b.board[x][y] == 5000) generateRookMoves(b, moves, x, y);

				else if (b.board[x][y] == 9000) generateQueenMoves(b, moves, x, y);

				else if (b.board[x][y] == 100000) generateKingMoves(b, moves, x, y);
			}
		}
	}

	else {

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {

				if (b.board[x][y] == 0) continue;

				else if (b.board[x][y] == -1000) generatePawnMoves(b, moves, x, y);

				else if (b.board[x][y] == -3000) generateHorseMoves(b, moves, x, y);

				else if (b.board[x][y] == -3100) generateBishopMoves(b, moves, x, y);

				else if (b.board[x][y] == -5000) generateRookMoves(b, moves, x, y);

				else if (b.board[x][y] == -9000) generateQueenMoves(b, moves, x, y);

				else if (b.board[x][y] == -100000) generateKingMoves(b, moves, x, y);
			}
		}
	}
}



static inline void addMove(Move moves[100], Move move) {
	moves[moves[99].from_x++] = move;
}



static inline void generatePawnMoves(Board& b, Move moves[100], int pos_x, int pos_y) {

	if (b.board[pos_x][pos_y] == 1000) {

		// Captures
		if (pos_x + 1 < 8 && pos_y + 1 < 8 && b.board[pos_x + 1][pos_y + 1] < 0) addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y + 1, b.board[pos_x + 1][pos_y + 1]));

		if (pos_x - 1 > -1 && pos_y + 1 < 8 && b.board[pos_x - 1][pos_y + 1] < 0) addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y + 1, b.board[pos_x - 1][pos_y + 1]));


		if (pos_y + 1 < 8 && !b.board[pos_x][pos_y + 1]) {

			addMove(moves, Move(pos_x, pos_y, pos_x, pos_y + 1, 0));


			if (pos_y == 1 && !b.board[pos_x][pos_y + 2]) {
				addMove(moves, Move(pos_x, pos_y, pos_x, pos_y + 2, 0));
			}
		}
	}

	else {

		// Captures
		if (pos_x + 1 < 8 && pos_y - 1 > -1 && b.board[pos_x + 1][pos_y - 1] > 0) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y - 1, b.board[pos_x + 1][pos_y - 1]));
		}

		if (pos_x - 1 > -1 && pos_y - 1 > -1 && b.board[pos_x - 1][pos_y - 1] > 0) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y - 1, b.board[pos_x - 1][pos_y - 1]));
		}


		if (pos_y - 1 > -1 && !b.board[pos_x][pos_y - 1]) {
			addMove(moves, Move(pos_x, pos_y, pos_x, pos_y - 1, 0));



			if (pos_y == 6 && !b.board[pos_x][pos_y - 2]) {
				addMove(moves, Move(pos_x, pos_y, pos_x, pos_y - 2, 0));
			}
		}
	}
}

static inline void generateHorseMoves(Board& b, Move moves[100], int pos_x, int pos_y) {

	if (b.board[pos_x][pos_y] == 3000) {

		if (pos_x + 1 < 8 && pos_y + 2 < 8 && b.board[pos_x + 1][pos_y + 2] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y + 2, b.board[pos_x + 1][pos_y + 2]));
		}

		if (pos_x - 1 > -1 && pos_y + 2 < 8 && b.board[pos_x - 1][pos_y + 2] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y + 2, b.board[pos_x - 1][pos_y + 2]));
		}

		if (pos_x + 2 < 8 && pos_y + 1 < 8 && b.board[pos_x + 2][pos_y + 1] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 2, pos_y + 1, b.board[pos_x + 2][pos_y + 1]));
		}

		if (pos_x - 2 > -1 && pos_y + 1 < 8 && b.board[pos_x - 2][pos_y + 1] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 2, pos_y + 1, b.board[pos_x - 2][pos_y + 1]));
		}

		if (pos_x + 2 < 8 && pos_y - 1 > -1 && b.board[pos_x + 2][pos_y - 1] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 2, pos_y - 1, b.board[pos_x + 2][pos_y - 1]));
		}

		if (pos_x - 2 > -1 && pos_y - 1 > -1 && b.board[pos_x - 2][pos_y - 1] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 2, pos_y - 1, b.board[pos_x - 2][pos_y - 1]));
		}

		if (pos_x + 1 < 8 && pos_y - 2 > -1 && b.board[pos_x + 1][pos_y - 2] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y - 2, b.board[pos_x + 1][pos_y - 2]));
		}

		if (pos_x - 1 > -1 && pos_y - 2 > -1 && b.board[pos_x - 1][pos_y - 2] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y - 2, b.board[pos_x - 1][pos_y - 2]));
		}
	}

	else {

		if (pos_x + 1 < 8 && pos_y + 2 < 8 && b.board[pos_x + 1][pos_y + 2] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y + 2, b.board[pos_x + 1][pos_y + 2]));
		}

		if (pos_x - 1 > -1 && pos_y + 2 < 8 && b.board[pos_x - 1][pos_y + 2] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y + 2, b.board[pos_x - 1][pos_y + 2]));
		}

		if (pos_x + 2 < 8 && pos_y + 1 < 8 && b.board[pos_x + 2][pos_y + 1] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 2, pos_y + 1, b.board[pos_x + 2][pos_y + 1]));
		}

		if (pos_x - 2 > -1 && pos_y + 1 < 8 && b.board[pos_x - 2][pos_y + 1] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 2, pos_y + 1, b.board[pos_x - 2][pos_y + 1]));
		}

		if (pos_x + 2 < 8 && pos_y - 1 > -1 && b.board[pos_x + 2][pos_y - 1] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 2, pos_y - 1, b.board[pos_x + 2][pos_y - 1]));
		}

		if (pos_x - 2 > -1 && pos_y - 1 > -1 && b.board[pos_x - 2][pos_y - 1] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 2, pos_y - 1, b.board[pos_x - 2][pos_y - 1]));
		}

		if (pos_x + 1 < 8 && pos_y - 2 > -1 && b.board[pos_x + 1][pos_y - 2] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y - 2, b.board[pos_x + 1][pos_y - 2]));
		}

		if (pos_x - 1 > -1 && pos_y - 2 > -1 && b.board[pos_x - 1][pos_y - 2] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y - 2, b.board[pos_x - 1][pos_y - 2]));
		}
	}
}

static inline void generateBishopMoves(Board& b, Move moves[100], int pos_x, int pos_y) {

	if (b.board[pos_x][pos_y] == 3100) {

		// Up Right
		for (int x = pos_x + 1, y = pos_y + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = pos_x - 1, y = pos_y + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = pos_x + 1, y = pos_y - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = pos_x - 1, y = pos_y - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}
	}

	else {

		// Up Right
		for (int x = pos_x + 1, y = pos_y + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = pos_x - 1, y = pos_y + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = pos_x + 1, y = pos_y - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = pos_x - 1, y = pos_y - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}
	}
}

static inline void generateRookMoves(Board& b, Move moves[100], int pos_x, int pos_y) {

	if (b.board[pos_x][pos_y] == 5000) {

		// Up
		for (int y = pos_y + 1; y < 8; y++) {

			if (b.board[pos_x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, 0));
			}

			else if (b.board[pos_x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, b.board[pos_x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = pos_y - 1; y > -1; y--) {

			if (b.board[pos_x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, 0));
			}

			else if (b.board[pos_x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, b.board[pos_x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = pos_x + 1; x < 8; x++) {

			if (b.board[x][pos_y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, 0));
			}

			else if (b.board[x][pos_y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, b.board[x][pos_y]));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = pos_x - 1; x > -1; x--) {

			if (b.board[x][pos_y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, 0));
			}

			else if (b.board[x][pos_y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, b.board[x][pos_y]));
				break;
			}

			else {
				break;
			}
		}
	}

	else {

		// Up
		for (int y = pos_y + 1; y < 8; y++) {

			if (b.board[pos_x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, 0));
			}

			else if (b.board[pos_x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, b.board[pos_x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = pos_y - 1; y > -1; y--) {

			if (b.board[pos_x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, 0));
			}

			else if (b.board[pos_x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, b.board[pos_x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = pos_x + 1; x < 8; x++) {

			if (b.board[x][pos_y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, 0));
			}

			else if (b.board[x][pos_y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, b.board[x][pos_y]));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = pos_x - 1; x > -1; x--) {

			if (b.board[x][pos_y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, 0));
			}

			else if (b.board[x][pos_y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, b.board[x][pos_y]));
				break;
			}

			else {
				break;
			}
		}
	}
}

static inline void generateQueenMoves(Board& b, Move moves[100], int pos_x, int pos_y) {

	if (b.board[pos_x][pos_y] == 9000) {

		// Up Right
		for (int x = pos_x + 1, y = pos_y + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = pos_x - 1, y = pos_y + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = pos_x + 1, y = pos_y - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = pos_x - 1, y = pos_y - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up
		for (int y = pos_y + 1; y < 8; y++) {

			if (b.board[pos_x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, 0));
			}

			else if (b.board[pos_x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, b.board[pos_x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = pos_y - 1; y > -1; y--) {

			if (b.board[pos_x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, 0));
			}

			else if (b.board[pos_x][y] < 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, b.board[pos_x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = pos_x + 1; x < 8; x++) {

			if (b.board[x][pos_y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, 0));
			}

			else if (b.board[x][pos_y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, b.board[x][pos_y]));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = pos_x - 1; x > -1; x--) {

			if (b.board[x][pos_y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, 0));
			}

			else if (b.board[x][pos_y] < 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, b.board[x][pos_y]));
				break;
			}

			else {
				break;
			}
		}
	}

	else {

		// Up Right
		for (int x = pos_x + 1, y = pos_y + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = pos_x - 1, y = pos_y + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = pos_x + 1, y = pos_y - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = pos_x - 1, y = pos_y - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up
		for (int y = pos_y + 1; y < 8; y++) {

			if (b.board[pos_x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, 0));
			}

			else if (b.board[pos_x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, b.board[pos_x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = pos_y - 1; y > -1; y--) {

			if (b.board[pos_x][y] == 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, 0));
			}

			else if (b.board[pos_x][y] > 0) {
				addMove(moves, Move(pos_x, pos_y, pos_x, y, b.board[pos_x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = pos_x + 1; x < 8; x++) {

			if (b.board[x][pos_y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, 0));
			}

			else if (b.board[x][pos_y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, b.board[x][pos_y]));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = pos_x - 1; x > -1; x--) {

			if (b.board[x][pos_y] == 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, 0));
			}

			else if (b.board[x][pos_y] > 0) {
				addMove(moves, Move(pos_x, pos_y, x, pos_y, b.board[x][pos_y]));
				break;
			}

			else {
				break;
			}
		}
	}
}

static inline void generateKingMoves(Board& b, Move moves[100], int pos_x, int pos_y) {

	if (b.board[pos_x][pos_y] == 100000) {

		// Up
		if (pos_y + 1 < 8 && b.board[pos_x][pos_y + 1] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x, pos_y + 1, b.board[pos_x][pos_y + 1]));
		}

		// Up Right
		if (pos_x + 1 < 8 && pos_y + 1 < 8 && b.board[pos_x + 1][pos_y + 1] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y + 1, b.board[pos_x + 1][pos_y + 1]));
		}

		// Up Left
		if (pos_x - 1 > -1 && pos_y + 1 < 8 && b.board[pos_x - 1][pos_y + 1] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y + 1, b.board[pos_x - 1][pos_y + 1]));
		}

		// Right
		if (pos_x + 1 < 8 && b.board[pos_x + 1][pos_y] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y, b.board[pos_x + 1][pos_y]));
		}

		// Left
		if (pos_x - 1 > -1 && b.board[pos_x - 1][pos_y] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y, b.board[pos_x - 1][pos_y]));
		}

		// Down
		if (pos_y - 1 > -1 && b.board[pos_x][pos_y - 1] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x, pos_y - 1, b.board[pos_x][pos_y - 1]));
		}

		// Down Right
		if (pos_x + 1 < 8 && pos_y - 1 > -1 && b.board[pos_x + 1][pos_y - 1] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y - 1, b.board[pos_x + 1][pos_y - 1]));
		}

		// Down Left
		if (pos_x - 1 > -1 && pos_y - 1 > -1 && b.board[pos_x - 1][pos_y - 1] < 1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y - 1, b.board[pos_x - 1][pos_y - 1]));
		}
	}

	else {

		// Up
		if (pos_y + 1 < 8 && b.board[pos_x][pos_y + 1] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x, pos_y + 1, b.board[pos_x][pos_y + 1]));
		}

		// Up Right
		if (pos_x + 1 < 8 && pos_y + 1 < 8 && b.board[pos_x + 1][pos_y + 1] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y + 1, b.board[pos_x + 1][pos_y + 1]));
		}

		// Up Left
		if (pos_x - 1 > -1 && pos_y + 1 < 8 && b.board[pos_x - 1][pos_y + 1] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y + 1, b.board[pos_x - 1][pos_y + 1]));
		}

		// Right
		if (pos_x + 1 < 8 && b.board[pos_x + 1][pos_y] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y, b.board[pos_x + 1][pos_y]));
		}

		// Left
		if (pos_x - 1 > -1 && b.board[pos_x - 1][pos_y] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y, b.board[pos_x - 1][pos_y]));
		}

		// Down
		if (pos_y - 1 > -1 && b.board[pos_x][pos_y - 1] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x, pos_y - 1, b.board[pos_x][pos_y - 1]));
		}

		// Down Right
		if (pos_x + 1 < 8 && pos_y - 1 > -1 && b.board[pos_x + 1][pos_y - 1] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x + 1, pos_y - 1, b.board[pos_x + 1][pos_y - 1]));
		}

		// Down Left
		if (pos_x - 1 > -1 && pos_y - 1 > -1 && b.board[pos_x - 1][pos_y - 1] > -1) {
			addMove(moves, Move(pos_x, pos_y, pos_x - 1, pos_y - 1, b.board[pos_x - 1][pos_y - 1]));
		}
	}
}