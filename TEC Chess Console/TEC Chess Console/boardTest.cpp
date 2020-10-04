/*/-------------------------------------------------------------------------------------//
	Filename:           boardTest.cpp
	Contributor:        Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:		A client for testing the chess board class. The class requires 
						extensive testing
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include "ChessBoard.h"

using namespace std;
using namespace chess;

int main() {

	bool result = true;
	ChessBoard testBoard;
	testBoard.printBoard();
	try {
		testBoard.moveWhite(0, 1, 0, 2);
	}
	catch (ChessBoard::BoundsError e) {
		cout << "Cannot move to or from a position off the board" << endl;
	}
	catch (ChessBoard::EmptySquareError e) {
		cout << "Cannot move an empty square." << endl;
	}
	catch (ChessBoard::TurnMoveError e) {
		cout << "Either it is not your turn, or you're moving the other player's piece." << endl;
	}
	catch (ChessBoard::NoTurnPassError e) {
		cout << "No moving to the same square, no passing turns." << endl;
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid move for that piece." << endl;
	}
	catch (ChessBoard::IlegalMoveError e) {
		cout << "Illegal move. Cannot jump over other pieces." << endl;
	}
	testBoard.printBoard();

}
