/*/-------------------------------------------------------------------------------------//
	Filename:           piecesTest.cpp
	Contributors:       Sonja Braden
	Date:               9/22/2020
	Reference:
	Description:		Testing the derived chess piece classes
//-------------------------------------------------------------------------------------/*/


#include <iostream>
//#include "ChessBoard.h"
#include "DerivedPieces.h"

using namespace std;
using namespace chess;


const int SIZE = 8;


void WpawnTest(ChessPiece& pawn);
void BpawnTest(ChessPiece& pawn);
void castleTest(ChessPiece& castle);
//void knightTest(ChessPiece& knight);
void rookTest(ChessPiece& rook);
void queenTest(ChessPiece& queen);
void kingTest(ChessPiece& king);


// Test
int main() {

	ChessPiece a;
	Pawn pW(0, 1);
	Pawn pB(4, 5, ChessPiece::black);
	Castle cB(6, 6, ChessPiece::black);
	//Knight n;
	Rook r;
	Queen Q;
	King K;

	ChessPiece Arr[SIZE] = { a, pW, pB, cB, r, Q, K };

	for (int i = 0; i < SIZE; i++) {
			
		cout << Arr[i].getPieceType() << "  " << Arr[i].getTeamType() << endl;
	}
	cout << endl << endl;


	WpawnTest(pW);
	BpawnTest(pB);
	castleTest(cB);
	rookTest(r);
	queenTest(Q);
	kingTest(K);

	return 0;
}



void WpawnTest(ChessPiece& pawn)
{

	int row;
	int col;

	cout << "Testing white Pawn move exceptions: expecting 2 exceptions..." << endl;

	pawn.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;

	try {
		pawn.setPosition(0, 3);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Forward 2 on first move. This move should NOT throw an exception." << endl;
	}

	try {
		pawn.setPosition(0, 4);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		pawn.setPosition(1, 4);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	try {
		pawn.setPosition(0, 3);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	try {
		pawn.setPosition(0, 5);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Invalid Pawn move. This move should NOT throw an exception." << endl;
	}

	pawn.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;

}






void BpawnTest(ChessPiece& pawn)
{
	int col;
	int row;
	
	cout << endl;
	cout << "Testing black Pawn move exceptions: expecting 2 exceptions..." << endl;

	pawn.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;

	try {
		pawn.setPosition(4, 3);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Forward 2 on first move. This move should NOT throw an exception." << endl;
	}

	try {
		pawn.setPosition(4, 2);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		pawn.setPosition(5, 2);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	try {
		pawn.setPosition(4, 1);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		pawn.setPosition(4, 2);
	}
	catch (Pawn::PawnMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	pawn.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;


}

void castleTest(ChessPiece& castle)
{

	int col;
	int row;

	cout << endl;
	cout << "Testing Castle move exceptions: expecting 1 exceptions..." << endl;

	castle.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;	// (2, 0)

	try {
		castle.setPosition(5, 2);
	}
	catch (Castle::CastleMoveError e) {
		cout << "Invalid Castle move. This move SHOULD throw an exception." << endl;
	}

	try {
		castle.setPosition(6, 2);
	}
	catch (Castle::CastleMoveError e) {
		cout << "Move along a column. This move should NOT throw an exception." << endl;
	}

	try {
		castle.setPosition(6, 4);
	}
	catch (Castle::CastleMoveError e) {
		cout << "Move along a row. This move should NOT throw an exception." << endl;
	}

	castle.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;

}







void knightTest(ChessPiece& knight)
{


}






void rookTest(ChessPiece& rook)
{
	int col;
	int row;

	cout << endl;
	cout << "Testing Rook move exceptions: expecting 2 exceptions..." << endl;

	rook.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;	// (2, 0)

	try {
		rook.setPosition(2, 2);
	}
	catch (Rook::RookMoveError e) {
		cout << "Invalid Rook move. This move SHOULD throw an exception." << endl;
	}

	try {
		rook.setPosition(4, 2);
	}
	catch (Rook::RookMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		rook.setPosition(1, 3);
	}
	catch (Rook::RookMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		rook.setPosition(6, 4);
	}
	catch (Rook::RookMoveError e) {
		cout << "Invalid Rook move. This move SHOULD throw an exception." << endl;
	}

	rook.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;


}







void queenTest(ChessPiece& queen)
{
	int col;
	int row;

	cout << endl;
	cout << "Testing Queen move exceptions: expecting 1 exceptions..." << endl;

	queen.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;	// (3 , 0)

	try {
		queen.setPosition(6, 2);
	}
	catch (Queen::QueenMoveError e) {
		cout << "Invalid Queen move. This move SHOULD throw an exception." << endl;
	}

	try {
		queen.setPosition(5, 2);
	}
	catch (Queen::QueenMoveError e) {
		cout << "Move on a diagonal. This move should NOT throw an exception." << endl;
	}

	try {
		queen.setPosition(0, 2);
	}
	catch (Queen::QueenMoveError e) {
		cout << "Move along a row. This move should NOT throw an exception." << endl;
	}

	try {
		queen.setPosition(0, 1);
	}
	catch (Queen::QueenMoveError e) {
		cout << "Move along a col. This move should NOT throw an exception." << endl;
	}

	queen.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;

}






void kingTest(ChessPiece& king)
{
	int col;
	int row;

	cout << endl;
	cout << "Testing King move exceptions: expecting 1 exceptions..." << endl;

	king.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl; // (4, 0)

	try {
		king.setPosition(6, 0);
	}
	catch (King::KingMoveError e) {
		cout << "Invalid King move. This move SHOULD throw an exception." << endl;
	}

	try {
		king.setPosition(5, 1);
	}
	catch (King::KingMoveError e) {
		cout << "Move on diagonal. This move should NOT throw an exception." << endl;
	}

	try {
		king.setPosition(4, 1);
	}
	catch (King::KingMoveError e) {
		cout << "Move along a row. This move should NOT throw an exception." << endl;
	}

	try {
		king.setPosition(3, 1);
	}
	catch (King::KingMoveError e) {
		cout << "Move along a col. This move should NOT throw an exception." << endl;
	}

	king.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;


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


Testing white Pawn move exceptions: expecting 2 exceptions...
Initial position: ( 0, 1 )
Invalid Pawn move. This move SHOULD throw an exception.
Invalid Pawn move. This move SHOULD throw an exception.
Final position: ( 0, 5 )

Testing black Pawn move exceptions: expecting 2 exceptions...
Initial position: ( 4, 5 )
Invalid Pawn move. This move SHOULD throw an exception.
Invalid Pawn move. This move SHOULD throw an exception.
Final position: ( 4, 1 )

Testing Castle move exceptions: expecting 1 exceptions...
Initial position: ( 6, 6 )
Invalid Castle move. This move SHOULD throw an exception.
Final position: ( 6, 4 )

Testing Rook move exceptions: expecting 2 exceptions...
Initial position: ( 2, 0 )
Invalid Rook move. This move SHOULD throw an exception.
This move should NOT throw an exception.
Final position: ( 6, 4 )

Testing Queen move exceptions: expecting 1 exceptions...
Initial position: ( 3, 0 )
Invalid Queen move. This move SHOULD throw an exception.
Final position: ( 0, 1 )

Testing King move exceptions: expecting 1 exceptions...
Initial position: ( 4, 0 )
Invalid King move. This move SHOULD throw an exception.
Final position: ( 3, 1 )


*/