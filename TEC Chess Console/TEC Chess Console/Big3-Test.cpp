/*/-------------------------------------------------------------------------------------//
	Filename:           Big3-Test.cpp
	Contributor:        Sonja Braden
	Date:               10/14/2020
	Reference:
	Description:		A client for testing the Big-3 of the ChessBoard class
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include "ChessBoard.h"

using namespace std;
using namespace chess;



int main() {

	ChessBoard base;

	cout << "Beginning assignment operator test..." << endl;

	ChessBoard b1;
	cout << endl << "Board 1: " << endl << endl;
	b1.printBoard();

	ChessBoard b2;
	cout << endl << "Board 2: " << endl << endl;
	b2.printBoard();

	b1.moveWhite(0, 1, 0, 3);
	cout << endl << "Moving a piece on Board 1: " << endl << endl;
	b1.printBoard();

	b2 = b1;
	cout << endl << "Setting Board 2 equal to Board 1: " << endl << endl;
	b2.printBoard();
	
	ChessBoard b3(b2);
	cout << endl << "Creating Board 3 via coy constructor: " << endl << endl;
	b3.printBoard();
	
	return 0;

}


/*

Beginning assignment operator test...

Board 1:

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

Board 2:

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

Moving a piece on Board 1:

  a  b  c  d  e  f  g  h
8 bR bN bB bQ bK bB bN bR 8
7 bP bP bP bP bP bP bP bP 7
6 __ __ __ __ __ __ __ __ 6
5 __ __ __ __ __ __ __ __ 5
4 wP __ __ __ __ __ __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 __ wP wP wP wP wP wP wP 2
1 wR wN wB wQ wK wB wN wR 1
  a  b  c  d  e  f  g  h

Setting Board 2 equal to Board 1:

  a  b  c  d  e  f  g  h
8 bR bN bB bQ bK bB bN bR 8
7 bP bP bP bP bP bP bP bP 7
6 __ __ __ __ __ __ __ __ 6
5 __ __ __ __ __ __ __ __ 5
4 wP __ __ __ __ __ __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 __ wP wP wP wP wP wP wP 2
1 wR wN wB wQ wK wB wN wR 1
  a  b  c  d  e  f  g  h

Creating Board 3 via coy constructor:

  a  b  c  d  e  f  g  h
8 bR bN bB bQ bK bB bN bR 8
7 bP bP bP bP bP bP bP bP 7
6 __ __ __ __ __ __ __ __ 6
5 __ __ __ __ __ __ __ __ 5
4 wP __ __ __ __ __ __ __ 4
3 __ __ __ __ __ __ __ __ 3
2 __ wP wP wP wP wP wP wP 2
1 wR wN wB wQ wK wB wN wR 1
  a  b  c  d  e  f  g  h

*/