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

void testMoveW(ChessBoard& argBoard, int x1, int y1, int x2, int y2);
void testMoveB(ChessBoard& argBoard, int x1, int y1, int x2, int y2);

int main() {

	ChessBoard testBoard;
	testBoard.printBoard();
	testMoveW(testBoard, 0, 1, 0, 2);
	testMoveB(testBoard, 5, 6, 5, 4);
}








void testMoveW(ChessBoard& argBoard, int x1, int y1, int x2, int y2)
{
	try {
		argBoard.moveWhite(x1, y1, x2, y2);
		cout << endl;
		argBoard.printBoard();
		cout << endl;
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
}






void testMoveB(ChessBoard& argBoard, int x1, int y1, int x2, int y2)
{
	try {
		argBoard.moveBlack(x1, y1, x2, y2);
		cout << endl;
		argBoard.printBoard();
		cout << endl;
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