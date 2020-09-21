/*/-------------------------------------------------------------------------------------//
	Filename:           ChessBoard.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:        
//-------------------------------------------------------------------------------------/*/


#ifndef CHESSBOARD_H
#define CHESSBOARD_H


#include  "WhiteSet.h"
#include  "BlackSet.h"

namespace chess {

	class ChessBoard {

	public:

		class MoveError{};
		int moveWhite(char position1, int position2, char move1, int move2); // a5 to b3 for example
		int moveBlack(char position1, int position2, char move1, int move2);
		void printBoard();

	private:

		WhiteSet white;
		BlackSet black;
		int remove(char position1, int position2);

	};



} // closes namespace

#endif