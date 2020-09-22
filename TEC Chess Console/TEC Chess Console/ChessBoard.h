/*/-------------------------------------------------------------------------------------//
	Filename:           ChessBoard.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:        
//-------------------------------------------------------------------------------------/*/


#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include  "ChessPiece.h"
#include  "ChessTeam.h"

namespace chess {

	class ChessBoard {

	public:

		ChessBoard();
		class MoveError{};
		int moveWhite(int position1, int position2, int move1, int move2); // a5 to b3 for example
		int moveBlack(int position1, int position2, int move1, int move2);
		void printBoard();

	private:

		ChessTeam White;
		ChessTeam Black;
		int remove(int position1, int position2);

	};



} // closes namespace

#endif