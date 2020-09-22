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
		class IlegalMoveError {};// moving a piece to a position already occupied by that team
		class BoundsError {};	// for moves that go out of board bounds
		int moveWhite(int position1, int position2, int move1, int move2); // indices 0-7 to rep
		int moveBlack(int position1, int position2, int move1, int move2); // rows a-h, cols 1-8
		void printBoard();

	private:

		ChessTeam White;
		ChessTeam Black;
		int remove(int position1, int position2);

	};



} // closes namespace

#endif