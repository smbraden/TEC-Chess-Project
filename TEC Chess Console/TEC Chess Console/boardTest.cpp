 /*/-------------------------------------------------------------------------------------//
	Filename:           boardTest.cpp
	Contributor:        Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:		A client for testing the chess board class. The class requires 
						extensive testing
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include <ctype.h>		// for tolower()
#include "ChessBoard.h"

using namespace std;
using namespace chess;



#define char2col(ch) tolower(ch) - 97
#define int2row(in) in - 1



bool testMoveW(ChessBoard& argBoard, int x1, int y1, int x2, int y2);
bool testMoveB(ChessBoard& argBoard, int x1, int y1, int x2, int y2);
void play(ChessBoard& argBoard, char& option, char& x1, int& y1, char& x2, int& y2);






int main() {

	char x1 = 'a';
	int y1 = 1;
	char x2 = 'a';
	int y2 = 1; 
	char option = 'c';

	ChessBoard testBoard;
	testBoard.printBoard();
	cout << endl << endl;

	cout << "Welcome to the TEC Chess Test Console!" << endl;
	cout << "To enter moves, use the format 'ColRow': a7, b3, etc"<< endl;
	cout << "Enter 'q' to exit at the continue/quit promt after each round" << endl;
	cout << "Play? Hit quit/continue now (q/c): ";
	cin >> option;
	cout << endl;

	if (option == 'q')
		return 0;
	else {
		play(testBoard, option, x1, y1, x2, y2);
	}

	return 0;
}







void play(ChessBoard& argBoard, char& option, char& x1, int& y1, char& x2, int& y2)
{

	do {

		do {

			cout << "White move. Current position:	";
			cin >> x1 >> y1;
			cout << "White move. New position:	";
			cin >> x2 >> y2;
			cout << endl;

		} while (!testMoveW(argBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2)));

		do {

			cout << "Black move. Current position:	";
			cin >> x1 >> y1;
			cout << "Black move. New position:	";
			cin >> x2 >> y2;
			cout << endl;

		} while (!testMoveB(argBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2)));


		// Continue prompt
		cout << "quit or continue (q/c):	";
		cin >> option;
		cout << endl;
		if (option == 'q')
			break;

	} while (tolower(option) != 'q');
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
		cout << "Cannot move to or from a position off the board" << endl << endl;
	}
	catch (ChessBoard::EmptySquareError e) {
		cout << "Cannot move an empty square" << endl << endl;
	}
	catch (ChessBoard::TurnMoveError e) {
		cout << "Not your turn, or you're moving the other player's piece" << endl << endl;
	}
	catch (ChessBoard::NoTurnPassError e) {
		cout << "No moving to the same square, no passing turns" << endl << endl;
	}
	catch (ChessBoard::SelfCapturError e) {
		cout << "You cannot 'capture' your own pieces" << endl << endl;
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid move for that piece" << endl << endl;
	}
	catch (ChessBoard::IndirectPathError e) {
		cout << "Indirect path. Only Knights can jump over other pieces" << endl << endl;
	}
	catch (ChessBoard::IlegalMoveError e) {
		cout << "Ilegal move" << endl << endl;
	}

	return false;
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
		cout << "Cannot move to or from a position off the board" << endl << endl;
	}
	catch (ChessBoard::EmptySquareError e) {
		cout << "Cannot move an empty square" << endl << endl;
	}
	catch (ChessBoard::TurnMoveError e) {
		cout << "Not your turn, or you're moving the other player's piece" << endl << endl;
	}
	catch (ChessBoard::NoTurnPassError e) {
		cout << "No moving to the same square, no passing turns" << endl << endl;
	}
	catch (ChessBoard::SelfCapturError e) {
		cout << "You cannot 'capture' your own pieces" << endl << endl;
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid move for that piece" << endl << endl;
	}
	catch (ChessBoard::IndirectPathError e) {
		cout << "Indirect path. Only Knights can jump over other pieces" << endl << endl;
	}
	catch (ChessBoard::IlegalMoveError e) {
		cout << "Ilegal move" << endl << endl;
	}

	return false;
}




/*

Sample output...

  a  b  c  d  e  f  g  h
8 bR bN bB bQ bK bB bN bR 8
7 bP bP bP bP bP bP bP bP 7
6 __ __ __ __ __ __ __ __ 6
5 __ __ __ __ __ __ __ __ 5
4 __ __ __ __ __ __ __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 wP wP wP wP wP wP wP wP 2
1 wR wN wB wQ wK wB wN wR 1
  a  b  c  d  e  f  g  h


Welcome to the TEC Chess Test Console!
To enter moves, use the format 'ColRow': a7, b3, etc
Enter 'q' to exit at the continue/quit promt after each round
Play? Hit quit/continue now (q/c): c

White move. Current position:   f2
White move. New position:       f4


  a  b  c  d  e  f  g  h
8 bR bN bB bQ bK bB bN bR 8
7 bP bP bP bP bP bP bP bP 7
6 __ __ __ __ __ __ __ __ 6
5 __ __ __ __ __ __ __ __ 5
4 __ __ __ __ __ wP __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 wP wP wP wP wP __ wP wP 2
1 wR wN wB wQ wK wB wN wR 1
  a  b  c  d  e  f  g  h

Black move. Current position:   e2
Black move. New position:       f2

Not your turn, or you're moving the other player's piece

Black move. Current position:   b8
Black move. New position:       c6


  a  b  c  d  e  f  g  h
8 bR __ bB bQ bK bB bN bR 8
7 bP bP bP bP bP bP bP bP 7
6 __ __ bN __ __ __ __ __ 6
5 __ __ __ __ __ __ __ __ 5
4 __ __ __ __ __ wP __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 wP wP wP wP wP __ wP wP 2
1 wR wN wB wQ wK wB wN wR 1
  a  b  c  d  e  f  g  h

quit or continue (q/c): c

White move. Current position:   e1
White move. New position:       g3

Invalid move for that piece

White move. Current position:   e1
White move. New position:       f2


  a  b  c  d  e  f  g  h
8 bR __ bB bQ bK bB bN bR 8
7 bP bP bP bP bP bP bP bP 7
6 __ __ bN __ __ __ __ __ 6
5 __ __ __ __ __ __ __ __ 5
4 __ __ __ __ __ wP __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 wP wP wP wP wP wK wP wP 2
1 wR wN wB wQ __ wB wN wR 1
  a  b  c  d  e  f  g  h

Black move. Current position:   d7
Black move. New position:       d5


  a  b  c  d  e  f  g  h
8 bR __ bB bQ bK bB bN bR 8
7 bP bP bP __ bP bP bP bP 7
6 __ __ bN __ __ __ __ __ 6
5 __ __ __ bP __ __ __ __ 5
4 __ __ __ __ __ wP __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 wP wP wP wP wP wK wP wP 2
1 wR wN wB wQ __ wB wN wR 1
  a  b  c  d  e  f  g  h

quit or continue (q/c): c

White move. Current position:   g1
White move. New position:       f3


  a  b  c  d  e  f  g  h
8 bR __ bB bQ bK bB bN bR 8
7 bP bP bP __ bP bP bP bP 7
6 __ __ bN __ __ __ __ __ 6
5 __ __ __ bP __ __ __ __ 5
4 __ __ __ __ __ wP __ __ 4
3 __ __ __ __ __ wN __ __ 3
2 wP wP wP wP wP wK wP wP 2
1 wR wN wB wQ __ wB __ wR 1
  a  b  c  d  e  f  g  h

Black move. Current position:   d8
Black move. New position:       d6


  a  b  c  d  e  f  g  h
8 bR __ bB __ bK bB bN bR 8
7 bP bP bP __ bP bP bP bP 7
6 __ __ bN bQ __ __ __ __ 6
5 __ __ __ bP __ __ __ __ 5
4 __ __ __ __ __ wP __ __ 4
3 __ __ __ __ __ wN __ __ 3
2 wP wP wP wP wP wK wP wP 2
1 wR wN wB wQ __ wB __ wR 1
  a  b  c  d  e  f  g  h

quit or continue (q/c): c

White move. Current position:   f3
White move. New position:       d4


  a  b  c  d  e  f  g  h
8 bR __ bB __ bK bB bN bR 8
7 bP bP bP __ bP bP bP bP 7
6 __ __ bN bQ __ __ __ __ 6
5 __ __ __ bP __ __ __ __ 5
4 __ __ __ wN __ wP __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 wP wP wP wP wP wK wP wP 2
1 wR wN wB wQ __ wB __ wR 1
  a  b  c  d  e  f  g  h

Black move. Current position:   c8
Black move. New position:       h3

Indirect path. Only Knights can jump over other pieces

Black move. Current position:   d6
Black move. New position:       b8

Indirect path. Only Knights can jump over other pieces

Black move. Current position:   c8
Black move. New position:       a6

Indirect path. Only Knights can jump over other pieces

Black move. Current position:   a8
Black move. New position:       b8


  a  b  c  d  e  f  g  h
8 __ bR bB __ bK bB bN bR 8
7 bP bP bP __ bP bP bP bP 7
6 __ __ bN bQ __ __ __ __ 6
5 __ __ __ bP __ __ __ __ 5
4 __ __ __ wN __ wP __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 wP wP wP wP wP wK wP wP 2
1 wR wN wB wQ __ wB __ wR 1
  a  b  c  d  e  f  g  h

quit or continue (q/c): c

White move. Current position:   d4
White move. New position:       c6


  a  b  c  d  e  f  g  h
8 __ bR bB __ bK bB bN bR 8
7 bP bP bP __ bP bP bP bP 7
6 __ __ wN bQ __ __ __ __ 6
5 __ __ __ bP __ __ __ __ 5
4 __ __ __ __ __ wP __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 wP wP wP wP wP wK wP wP 2
1 wR wN wB wQ __ wB __ wR 1
  a  b  c  d  e  f  g  h

Black move. Current position:   c8
Black move. New position:       g4

Indirect path. Only Knights can jump over other pieces

Black move. Current position:   c8
Black move. New position:       f5

Indirect path. Only Knights can jump over other pieces

Black move. Current position:   c8
Black move. New position:       e6


  a  b  c  d  e  f  g  h
8 __ bR __ __ bK bB bN bR 8
7 bP bP bP __ bP bP bP bP 7
6 __ __ wN bQ bB __ __ __ 6
5 __ __ __ bP __ __ __ __ 5
4 __ __ __ __ __ wP __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 wP wP wP wP wP wK wP wP 2
1 wR wN wB wQ __ wB __ wR 1
  a  b  c  d  e  f  g  h

quit or continue (q/c):



*/





/*

// Prototype
bool testMove(ChessBoard& argBoard, int x1, int y1, int x2, int y2, ChessPiece::team_type inTeam);


// Definition
bool testMove(ChessBoard& argBoard, int x1, int y1, int x2, int y2, ChessPiece::team_type inTeam)
{
	try {
		if (inTeam == ChessPiece::team_type::black)
			argBoard.moveBlack(x1, y1, x2, y2);
		else
			argBoard.moveWhite(x1, y1, x2, y2);
		cout << endl;
		argBoard.printBoard();
		cout << endl;
		return true;
	}
	catch (ChessBoard::BoundsError e) {
		cout << "Cannot move to or from a position off the board" << endl << endl;
	}
	catch (ChessBoard::EmptySquareError e) {
		cout << "Cannot move an empty square" << endl << endl;
	}
	catch (ChessBoard::TurnMoveError e) {
		cout << "Not your turn, or you're moving the other player's piece" << endl << endl;
	}
	catch (ChessBoard::NoTurnPassError e) {
		cout << "No moving to the same square, no passing turns" << endl << endl;
	}
	catch (ChessBoard::SelfCapturError e) {
		cout << "You cannot 'capture' your own pieces" << endl << endl;
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid move for that piece" << endl << endl;
	}
	catch (ChessBoard::IlegalMoveError e) {
		cout << "Only Knights can jump over other pieces" << endl << endl;
	}

	return false;
}



// while (!testMove(testBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2), ChessPiece::team_type::black));
// while (!testMove(testBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2), ChessPiece::team_type::white));

*/