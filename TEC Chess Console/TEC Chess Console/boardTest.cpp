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

#define char2col(ch) ch - 65
#define int2row(in) in - 1

bool testMoveW(ChessBoard& argBoard, int x1, int y1, int x2, int y2);
bool testMoveB(ChessBoard& argBoard, int x1, int y1, int x2, int y2);

int main() {

	char x1 = 'a';
	int y1 = 1;
	char x2 = 'a';
	int y2 = 1;
	bool status = false;

	ChessBoard testBoard;
	testBoard.printBoard();
	testMoveW(testBoard, 0, 1, 0, 2);
	testMoveB(testBoard, 5, 6, 5, 4);

	cout << "Welcome to the TEC Chess Console!" << endl;
	cout << "To enter moves, use the format 'ColRow': a7, b3, etc"<< endl;
	cout << "Enter 'q' to exit at any time." << endl;
	cout << endl;

	do {

		status = (tolower(x1) != 'q' && tolower(y1) != 'q' && tolower(x2) != 'q' && tolower(y2) != 'q');

		do {

			cout << "White move. Current position:	";
			cin >> x1 >> y1;
			cout << endl;
			cout << "White move. New position:	";
			cin >> x2 >> y2;
			cout << endl;

			status = (tolower(x1) != 'q' && tolower(y1) != 'q' && tolower(x2) != 'q' && tolower(y2) != 'q');

		} while (status && !testMoveW(testBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2)));

		do {

			cout << "Black move. Current position:	";
			cin >> x1 >> y1;
			cout << endl;
			cout << "Black move. New position:	";
			cin >> x2 >> y2;
			cout << endl;

			status = (tolower(x1) != 'q' && tolower(y1) != 'q' && tolower(x2) != 'q' && tolower(y2) != 'q');

		} while (status && !testMoveB(testBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2)));
		
	} while (status);

	return 0;
}








bool testMoveW(ChessBoard& argBoard, int x1, int y1, int x2, int y2)
{
	try {
		argBoard.moveWhite(x1, y1, x2, y2);
		cout << endl;
		argBoard.printBoard();
		cout << endl;
		return true;
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

	return false;
}






bool testMoveB(ChessBoard& argBoard, int x1, int y1, int x2, int y2)
{
	try {
		argBoard.moveBlack(x1, y1, x2, y2);
		cout << endl;
		argBoard.printBoard();
		cout << endl;
		return true;
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

	return false;
}


/*

Sample output...

wC wN wR wQ wK wR wN wC
wP wP wP wP wP wP wP wP
__ __ __ __ __ __ __ __
__ __ __ __ __ __ __ __
__ __ __ __ __ __ __ __
__ __ __ __ __ __ __ __
bP bP bP bP bP bP bP bP
bC bN bR bQ bK bR bN bC

wC wN wR wQ wK wR wN wC
__ wP wP wP wP wP wP wP
wP __ __ __ __ __ __ __
__ __ __ __ __ __ __ __
__ __ __ __ __ __ __ __
__ __ __ __ __ __ __ __
bP bP bP bP bP bP bP bP
bC bN bR bQ bK bR bN bC


wC wN wR wQ wK wR wN wC
__ wP wP wP wP wP wP wP
wP __ __ __ __ __ __ __
__ __ __ __ __ __ __ __
__ __ __ __ __ bP __ __
__ __ __ __ __ __ __ __
bP bP bP bP bP __ bP bP
bC bN bR bQ bK bR bN bC


Or, with extra spaces...

wC  wN  wR  wQ  wK  wR  wN  wC

wP  wP  wP  wP  wP  wP  wP  wP

__  __  __  __  __  __  __  __

__  __  __  __  __  __  __  __

__  __  __  __  __  __  __  __

__  __  __  __  __  __  __  __

bP  bP  bP  bP  bP  bP  bP  bP

bC  bN  bR  bQ  bK  bR  bN  bC



wC  wN  wR  wQ  wK  wR  wN  wC

__  wP  wP  wP  wP  wP  wP  wP

wP  __  __  __  __  __  __  __

__  __  __  __  __  __  __  __

__  __  __  __  __  __  __  __

__  __  __  __  __  __  __  __

bP  bP  bP  bP  bP  bP  bP  bP

bC  bN  bR  bQ  bK  bR  bN  bC



wC  wN  wR  wQ  wK  wR  wN  wC

__  wP  wP  wP  wP  wP  wP  wP

wP  __  __  __  __  __  __  __

__  __  __  __  __  __  __  __

__  __  __  __  __  bP  __  __

__  __  __  __  __  __  __  __

bP  bP  bP  bP  bP  __  bP  bP

bC  bN  bR  bQ  bK  bR  bN  bC



*/