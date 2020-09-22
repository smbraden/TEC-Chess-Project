/*/-------------------------------------------------------------------------------------//
	Filename:           main.cpp
	Contributors:       Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/


#include <iostream>
#include "ChessBoard.h"


using namespace std;
using namespace chess;


const int SIZE = 3;

// Test
int main() {

	ChessPiece a;
	Pawn b;
	Castle c;

	ChessPiece Arr[SIZE] = { a, b, c };

	for (int i = 0; i < SIZE; i++) {
			
		cout << Arr[i].getType() << endl;
	}

	return 0;
}