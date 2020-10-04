#include <iostream>
#include "ChessBoard.h"
//#include "DerivedPieces.h"

using namespace std;
using namespace chess;

int main() {

	bool result = true;
	ChessBoard testBoard;
	testBoard.printBoard();
	try {
		result = testBoard.moveWhite(0, 1, 0, 3);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid move for that piece." << endl;
	}
	catch (ChessBoard::IlegalMoveError e) {
		cout << "Illegal move. Cannot jump over other pieces." << endl;
	}
	testBoard.printBoard();

}
