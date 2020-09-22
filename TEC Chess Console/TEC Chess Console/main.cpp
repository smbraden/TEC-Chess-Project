/*/-------------------------------------------------------------------------------------//
	Filename:           main.cpp
	Contributors:       Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/


#include <iostream>
//#include "ChessBoard.h"
#include "DerivedPieces.h"

using namespace std;
using namespace chess;


const int SIZE = 8;

// Test
int main() {

	ChessPiece a;
	Pawn pW(0, 1);
	Pawn pB(4, 5, 'b');
	Castle cB(6, 6, 'b');
	//Knight n;
	Rook r;
	Queen Q;
	King K;

	ChessPiece Arr[SIZE] = { a, pW, pB, cB, r, Q, K };

	for (int i = 0; i < SIZE; i++) {
			
		cout << Arr[i].getPieceType() << "  " << Arr[i].getTeamType() << endl;
	}
	cout << endl << endl;


	int row;
	int col;
	




	cout << "Testing white Pawn move exceptions..." << endl;

	pW.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;

	try {
		pW.setPosition(0, 3);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Forward 2 on first move. This move should NOT throw an exception." << endl;
	}

	try {
		pW.setPosition(0, 4);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		pW.setPosition(1, 4);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	try {
		pW.setPosition(0, 3);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	try {
		pW.setPosition(0, 5);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Invalid Pawn move. This move should NOT throw an exception." << endl;
	}

	pW.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;






	cout << endl;
	cout << "Testing black Pawn move exceptions..." << endl;

	pB.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;

	try {
		pB.setPosition(4, 3);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Forward 2 on first move. This move should NOT throw an exception." << endl;
	}

	try {
		pB.setPosition(4, 2);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		pB.setPosition(5, 2);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	try {
		pB.setPosition(4, 1);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		pB.setPosition(4, 2);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	pB.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;





	cout << endl;
	cout << "Testing Castle move exceptions..." << endl;

	cB.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;

	try {
		cB.setPosition(5, 2);
	}
	catch (Castle::CastleMoveError e) {
		cout << "Invalid Castle move. This move SHOULD throw an exception." << endl;
	}

	try {
		cB.setPosition(6, 2);
	}
	catch (Castle::CastleMoveError e) {
		cout << "Move along a column. This move should NOT throw an exception." << endl;
	}

	try {
		cB.setPosition(4, 6);
	}
	catch (Castle::CastleMoveError e) {
		cout << "Move along a row. This move should NOT throw an exception." << endl;
	}

	cB.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;


	return 0;
}


/*

0  w
P  w
P  b
C  b
R  w
Q  w
K  w
0  w


Testing white Pawn move exceptions...
Initial position: ( 0, 0 )
Forward 2 on first move. This move should NOT throw an exception.
This move should NOT throw an exception.
Invalid Pawn move. This move SHOULD throw an exception.
Invalid Pawn move. This move SHOULD throw an exception.
Invalid Pawn move. This move should NOT throw an exception.
Final position: ( 0, 0 )

Testing black Pawn move exceptions...
Initial position: ( 0, 0 )
Forward 2 on first move. This move should NOT throw an exception.
This move should NOT throw an exception.
Invalid Pawn move. This move SHOULD throw an exception.
This move should NOT throw an exception.
Invalid Pawn move. This move SHOULD throw an exception.
Final position: ( 0, 0 )

Testing Castle move exceptions...
Initial position: ( 0, 0 )
Invalid Castle move. This move SHOULD throw an exception.
Move along a column. This move should NOT throw an exception.
Move along a row. This move should NOT throw an exception.
Final position: ( 0, 0 )

*/