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


bool testMove(ChessBoard& argBoard, int x1, int y1, int x2, int y2, bool& flag);
void play(ChessBoard& argBoard, char& option, char& x1, int& y1, char& x2, int& y2);
inline int char2col(char ch);
inline int int2row(int arg);



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
	cout << "To enter moves, use the format 'ColRow': a7, b3, etc" << endl;
	cout << "Don't hit 'enter' without any input. This is a quick n dirty test that will break." << endl;
	cout << "Enter 'q' to exit at the continue/quit prompt after each round" << endl;
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







bool testMove(ChessBoard& argBoard, int x1, int y1, int x2, int y2, bool& flag)
{
	try {

		argBoard.move(x1, y1, x2, y2);
		cout << endl;
		argBoard.printBoard();
		cout << endl;
		return true;
	}
	catch (const chess_except::InvalidMoveExcep& e) {
		cout << e.getMsg() << endl << endl;
	}
	catch (const chess_except::DrawSignal& e) {
		cout << e.getMsg() << endl << endl;
		flag = true;
		return true;
	}
	catch (const chess_except::WinSignal& e) {
		cout << e.getMsg() << endl << endl;
		flag = true;
		return true;
	}

	return false;
}







void play(ChessBoard& argBoard, char& option, char& x1, int& y1, char& x2, int& y2)
{
	bool endFlag = false;

	do {

		do {
			
			string team = (argBoard.getTurnTeam() == team_type::white) ? "White" : "Black";

			cout << team << " move. Current position:	";
			cin >> x1 >> y1;
			cout << team << " move. New position:	";
			cin >> x2 >> y2;
			cout << endl;
			
		} while (!testMove(argBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2), endFlag));

		if (endFlag)
			break;

		// Continue prompt
		cout << "quit or continue (q/c):	";
		cin >> option;
		cout << endl;
		if (option == 'q')
			break;

	} while (tolower(option) != 'q' && !endFlag);

	argBoard.printBoard();	// the final print will not execute (win or draw signaled by exception)
}






inline int char2col(char ch)
{
	return (tolower(ch) - 97);
}






inline int int2row(int arg)
{
	return (arg - 1);
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



/*
bool testMove(ChessBoard& argBoard, int x1, int y1, int x2, int y2, bool& flag)
{
	try {

		argBoard.move(x1, y1, x2, y2);
		cout << endl;
		argBoard.printBoard();
		cout << endl;
		return true;
	}
	catch (ChessTeam::BoundsError e) {
		cout << "Cannot move to or from a position off the board..." << endl << endl;
	}
	catch (ChessTeam::EmptySquareError e) {
		cout << "Cannot move an empty square..." << endl << endl;
	}
	catch (ChessTeam::TurnMoveError e) {
		cout << "Not your turn, or you're moving the other player's piece..." << endl << endl;
	}
	catch (ChessTeam::NoTurnPassError e) {
		cout << "No moving to the same square, no passing turns..." << endl << endl;
	}
	catch (ChessTeam::SelfCapturError e) {
		cout << "You cannot 'capture' your own pieces..." << endl << endl;
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid move for that piece..." << endl << endl;
	}
	catch (ChessTeam::IndirectPathError e) {
		cout << "Indirect path. Only Knights can jump over other pieces..." << endl << endl;
	}
	catch (ChessTeam::CheckError e) {
		cout << "This move does not remove your King from check. You might be pwned..." << endl << endl;
	}
	catch (ChessBoard::DrawSignal e) {
		cout << "The game is a draw. The cause is 3-fold repetition of the game state..." << endl << endl;
		flag = true;
		return true;
	}
	catch (ChessBoard::WinSignal e) {
		string winner = (argBoard.getWinner() == ChessPiece::team_type::white) ? "white" : "black";
		cout << "The winner is " << winner << "!" << endl << endl;
		flag = true;
		return true;
	}

	return false;
}
*/
