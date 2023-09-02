#include "beta.h"

using namespace std;



void generateMoves( Board& b, Move moves[100], bool player, bool onlyCapture ) {

	if (player) {

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {

				if (b.board[x][y] == 0) continue;

				else if (b.board[x][y] == 1000) generatePawnMoves( b, moves, x, y );

				else if (b.board[x][y] == 3000) generateHorseMoves( b, moves, x, y );

				else if (b.board[x][y] == 3100) generateBishopMoves( b, moves, x, y );

				else if (b.board[x][y] == 5000) generateRookMoves( b, moves, x, y );

				else if (b.board[x][y] == 9000) generateQueenMoves( b, moves, x, y );

				else if (b.board[x][y] == 100000) generateKingMoves( b, moves, x, y );
			}
		}
	}

	else {

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {

				if (b.board[x][y] == 0) continue;

				else if (b.board[x][y] == -1000) generatePawnMoves( b, moves, x, y );

				else if (b.board[x][y] == -3000) generateHorseMoves( b, moves, x, y );

				else if (b.board[x][y] == -3100) generateBishopMoves( b, moves, x, y );

				else if (b.board[x][y] == -5000) generateRookMoves( b, moves, x, y );

				else if (b.board[x][y] == -9000) generateQueenMoves( b, moves, x, y );

				else if (b.board[x][y] == -100000) generateKingMoves( b, moves, x, y );
			}
		}
	}
}



static inline void addMove( Move moves[100], Move move ) {
	moves[moves[99].from_x++] = move;
}



static inline void generatePawnMoves( Board& b, Move moves[100], int posX, int posY ) {

	if (b.board[posX][posY] == 1000) {

		// Captures
		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] < 0) addMove( moves, Move( posX, posY, posX + 1, posY + 1, b.board[posX + 1][posY + 1] ) );

		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] < 0) addMove( moves, Move( posX, posY, posX - 1, posY + 1, b.board[posX - 1][posY + 1] ) );


		if (posY + 1 < 8 && !b.board[posX][posY + 1]) {

			addMove( moves, Move( posX, posY, posX, posY + 1, 0 ) );


			if (posY == 1 && !b.board[posX][posY + 2]) {
				addMove( moves, Move( posX, posY, posX, posY + 2, 0 ) );
			}
		}
	}

	else {

		// Captures
		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] > 0) {
			addMove( moves, Move( posX, posY, posX + 1, posY - 1, b.board[posX + 1][posY - 1] ) );
		}

		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] > 0) {
			addMove( moves, Move( posX, posY, posX - 1, posY - 1, b.board[posX - 1][posY - 1] ) );
		}


		if (posY - 1 > -1 && !b.board[posX][posY - 1]) {
			addMove( moves, Move( posX, posY, posX, posY - 1, 0 ) );



			if (posY == 6 && !b.board[posX][posY - 2]) {
				addMove( moves, Move( posX, posY, posX, posY - 2, 0 ) );
			}
		}
	}
}

static inline void generateHorseMoves( Board& b, Move moves[100], int posX, int posY ) {

	if (b.board[posX][posY] == 3000) {

		if (posX + 1 < 8 && posY + 2 < 8 && b.board[posX + 1][posY + 2] < 1) {
			addMove( moves, Move( posX, posY, posX + 1, posY + 2, b.board[posX + 1][posY + 2] ) );
		}

		if (posX - 1 > -1 && posY + 2 < 8 && b.board[posX - 1][posY + 2] < 1) {
			addMove( moves, Move( posX, posY, posX - 1, posY + 2, b.board[posX - 1][posY + 2] ) );
		}

		if (posX + 2 < 8 && posY + 1 < 8 && b.board[posX + 2][posY + 1] < 1) {
			addMove( moves, Move( posX, posY, posX + 2, posY + 1, b.board[posX + 2][posY + 1] ) );
		}

		if (posX - 2 > -1 && posY + 1 < 8 && b.board[posX - 2][posY + 1] < 1) {
			addMove( moves, Move( posX, posY, posX - 2, posY + 1, b.board[posX - 2][posY + 1] ) );
		}

		if (posX + 2 < 8 && posY - 1 > -1 && b.board[posX + 2][posY - 1] < 1) {
			addMove( moves, Move( posX, posY, posX + 2, posY - 1, b.board[posX + 2][posY - 1] ) );
		}

		if (posX - 2 > -1 && posY - 1 > -1 && b.board[posX - 2][posY - 1] < 1) {
			addMove( moves, Move( posX, posY, posX - 2, posY - 1, b.board[posX - 2][posY - 1] ) );
		}

		if (posX + 1 < 8 && posY - 2 > -1 && b.board[posX + 1][posY - 2] < 1) {
			addMove( moves, Move( posX, posY, posX + 1, posY - 2, b.board[posX + 1][posY - 2] ) );
		}

		if (posX - 1 > -1 && posY - 2 > -1 && b.board[posX - 1][posY - 2] < 1) {
			addMove( moves, Move( posX, posY, posX - 1, posY - 2, b.board[posX - 1][posY - 2] ) );
		}
	}

	else {

		if (posX + 1 < 8 && posY + 2 < 8 && b.board[posX + 1][posY + 2] > -1) {
			addMove( moves, Move( posX, posY, posX + 1, posY + 2, b.board[posX + 1][posY + 2] ) );
		}

		if (posX - 1 > -1 && posY + 2 < 8 && b.board[posX - 1][posY + 2] > -1) {
			addMove( moves, Move( posX, posY, posX - 1, posY + 2, b.board[posX - 1][posY + 2] ) );
		}

		if (posX + 2 < 8 && posY + 1 < 8 && b.board[posX + 2][posY + 1] > -1) {
			addMove( moves, Move( posX, posY, posX + 2, posY + 1, b.board[posX + 2][posY + 1] ) );
		}

		if (posX - 2 > -1 && posY + 1 < 8 && b.board[posX - 2][posY + 1] > -1) {
			addMove( moves, Move( posX, posY, posX - 2, posY + 1, b.board[posX - 2][posY + 1] ) );
		}

		if (posX + 2 < 8 && posY - 1 > -1 && b.board[posX + 2][posY - 1] > -1) {
			addMove( moves, Move( posX, posY, posX + 2, posY - 1, b.board[posX + 2][posY - 1] ) );
		}

		if (posX - 2 > -1 && posY - 1 > -1 && b.board[posX - 2][posY - 1] > -1) {
			addMove( moves, Move( posX, posY, posX - 2, posY - 1, b.board[posX - 2][posY - 1] ) );
		}

		if (posX + 1 < 8 && posY - 2 > -1 && b.board[posX + 1][posY - 2] > -1) {
			addMove( moves, Move( posX, posY, posX + 1, posY - 2, b.board[posX + 1][posY - 2] ) );
		}

		if (posX - 1 > -1 && posY - 2 > -1 && b.board[posX - 1][posY - 2] > -1) {
			addMove( moves, Move( posX, posY, posX - 1, posY - 2, b.board[posX - 1][posY - 2] ) );
		}
	}
}

static inline void generateBishopMoves( Board& b, Move moves[100], int posX, int posY ) {

	if (b.board[posX][posY] == 3100) {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] < 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] < 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] < 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] < 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}
	}

	else {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] > 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] > 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] > 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] > 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}
	}
}

static inline void generateRookMoves( Board& b, Move moves[100], int posX, int posY ) {

	if (b.board[posX][posY] == 5000) {

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				addMove( moves, Move( posX, posY, posX, y, 0 ) );
			}

			else if (b.board[posX][y] < 0) {
				addMove( moves, Move( posX, posY, posX, y, b.board[posX][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				addMove( moves, Move( posX, posY, posX, y, 0 ) );
			}

			else if (b.board[posX][y] < 0) {
				addMove( moves, Move( posX, posY, posX, y, b.board[posX][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				addMove( moves, Move( posX, posY, x, posY, 0 ) );
			}

			else if (b.board[x][posY] < 0) {
				addMove( moves, Move( posX, posY, x, posY, b.board[x][posY] ) );
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				addMove( moves, Move( posX, posY, x, posY, 0 ) );
			}

			else if (b.board[x][posY] < 0) {
				addMove( moves, Move( posX, posY, x, posY, b.board[x][posY] ) );
				break;
			}

			else {
				break;
			}
		}
	}

	else {

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				addMove( moves, Move( posX, posY, posX, y, 0 ) );
			}

			else if (b.board[posX][y] > 0) {
				addMove( moves, Move( posX, posY, posX, y, b.board[posX][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				addMove( moves, Move( posX, posY, posX, y, 0 ) );
			}

			else if (b.board[posX][y] > 0) {
				addMove( moves, Move( posX, posY, posX, y, b.board[posX][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				addMove( moves, Move( posX, posY, x, posY, 0 ) );
			}

			else if (b.board[x][posY] > 0) {
				addMove( moves, Move( posX, posY, x, posY, b.board[x][posY] ) );
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				addMove( moves, Move( posX, posY, x, posY, 0 ) );
			}

			else if (b.board[x][posY] > 0) {
				addMove( moves, Move( posX, posY, x, posY, b.board[x][posY] ) );
				break;
			}

			else {
				break;
			}
		}
	}
}

static inline void generateQueenMoves( Board& b, Move moves[100], int posX, int posY ) {

	if (b.board[posX][posY] == 9000) {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] < 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] < 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] < 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] < 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				addMove( moves, Move( posX, posY, posX, y, 0 ) );
			}

			else if (b.board[posX][y] < 0) {
				addMove( moves, Move( posX, posY, posX, y, b.board[posX][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				addMove( moves, Move( posX, posY, posX, y, 0 ) );
			}

			else if (b.board[posX][y] < 0) {
				addMove( moves, Move( posX, posY, posX, y, b.board[posX][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				addMove( moves, Move( posX, posY, x, posY, 0 ) );
			}

			else if (b.board[x][posY] < 0) {
				addMove( moves, Move( posX, posY, x, posY, b.board[x][posY] ) );
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				addMove( moves, Move( posX, posY, x, posY, 0 ) );
			}

			else if (b.board[x][posY] < 0) {
				addMove( moves, Move( posX, posY, x, posY, b.board[x][posY] ) );
				break;
			}

			else {
				break;
			}
		}
	}

	else {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] > 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] > 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] > 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				addMove( moves, Move( posX, posY, x, y, 0 ) );
			}

			else if (b.board[x][y] > 0) {
				addMove( moves, Move( posX, posY, x, y, b.board[x][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				addMove( moves, Move( posX, posY, posX, y, 0 ) );
			}

			else if (b.board[posX][y] > 0) {
				addMove( moves, Move( posX, posY, posX, y, b.board[posX][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				addMove( moves, Move( posX, posY, posX, y, 0 ) );
			}

			else if (b.board[posX][y] > 0) {
				addMove( moves, Move( posX, posY, posX, y, b.board[posX][y] ) );
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				addMove( moves, Move( posX, posY, x, posY, 0 ) );
			}

			else if (b.board[x][posY] > 0) {
				addMove( moves, Move( posX, posY, x, posY, b.board[x][posY] ) );
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				addMove( moves, Move( posX, posY, x, posY, 0 ) );
			}

			else if (b.board[x][posY] > 0) {
				addMove( moves, Move( posX, posY, x, posY, b.board[x][posY] ) );
				break;
			}

			else {
				break;
			}
		}
	}
}

static inline void generateKingMoves( Board& b, Move moves[100], int posX, int posY ) {

	if (b.board[posX][posY] == 100000) {

		// Up
		if (posY + 1 < 8 && b.board[posX][posY + 1] < 1) {
			addMove( moves, Move( posX, posY, posX, posY + 1, b.board[posX][posY + 1] ) );
		}

		// Up Right
		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] < 1) {
			addMove( moves, Move( posX, posY, posX + 1, posY + 1, b.board[posX + 1][posY + 1] ) );
		}

		// Up Left
		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] < 1) {
			addMove( moves, Move( posX, posY, posX - 1, posY + 1, b.board[posX - 1][posY + 1] ) );
		}

		// Right
		if (posX + 1 < 8 && b.board[posX + 1][posY] < 1) {
			addMove( moves, Move( posX, posY, posX + 1, posY, b.board[posX + 1][posY] ) );
		}

		// Left
		if (posX - 1 > -1 && b.board[posX - 1][posY] < 1) {
			addMove( moves, Move( posX, posY, posX - 1, posY, b.board[posX - 1][posY] ) );
		}

		// Down
		if (posY - 1 > -1 && b.board[posX][posY - 1] < 1) {
			addMove( moves, Move( posX, posY, posX, posY - 1, b.board[posX][posY - 1] ) );
		}

		// Down Right
		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] < 1) {
			addMove( moves, Move( posX, posY, posX + 1, posY - 1, b.board[posX + 1][posY - 1] ) );
		}

		// Down Left
		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] < 1) {
			addMove( moves, Move( posX, posY, posX - 1, posY - 1, b.board[posX - 1][posY - 1] ) );
		}
	}

	else {

		// Up
		if (posY + 1 < 8 && b.board[posX][posY + 1] > -1) {
			addMove( moves, Move( posX, posY, posX, posY + 1, b.board[posX][posY + 1] ) );
		}

		// Up Right
		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] > -1) {
			addMove( moves, Move( posX, posY, posX + 1, posY + 1, b.board[posX + 1][posY + 1] ) );
		}

		// Up Left
		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] > -1) {
			addMove( moves, Move( posX, posY, posX - 1, posY + 1, b.board[posX - 1][posY + 1] ) );
		}

		// Right
		if (posX + 1 < 8 && b.board[posX + 1][posY] > -1) {
			addMove( moves, Move( posX, posY, posX + 1, posY, b.board[posX + 1][posY] ) );
		}

		// Left
		if (posX - 1 > -1 && b.board[posX - 1][posY] > -1) {
			addMove( moves, Move( posX, posY, posX - 1, posY, b.board[posX - 1][posY] ) );
		}

		// Down
		if (posY - 1 > -1 && b.board[posX][posY - 1] > -1) {
			addMove( moves, Move( posX, posY, posX, posY - 1, b.board[posX][posY - 1] ) );
		}

		// Down Right
		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] > -1) {
			addMove( moves, Move( posX, posY, posX + 1, posY - 1, b.board[posX + 1][posY - 1] ) );
		}

		// Down Left
		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] > -1) {
			addMove( moves, Move( posX, posY, posX - 1, posY - 1, b.board[posX - 1][posY - 1] ) );
		}
	}
}