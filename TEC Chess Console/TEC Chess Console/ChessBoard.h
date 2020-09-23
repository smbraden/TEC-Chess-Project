/*/-------------------------------------------------------------------------------------//
	Filename:           ChessBoard.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:        
//-------------------------------------------------------------------------------------/*/


#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include  "DerivedPieces.h"

namespace chess {

	class ChessBoard {

	public:

		ChessBoard();
		class SelfCapturError {};	// moving a piece to a position already occupied by that team
		class TurnMoveError {};		// when a player attempts to move the opponent's piece
		class BoundsError {};		// for moves that go out of board bounds
		class IlegalMoveError {};	// any other illegal moves

		int moveWhite(int pos1, int pos2, int move1, int move2); // indices 0-7 to rep
		int moveBlack(int pos1, int pos2, int move1, int move2); // rows a-h, cols 1-8
		void printBoard();

		static const int BOARD_SIZE = 8;
		static const int SPACES = 64;

	private:

		ChessPiece* grid[BOARD_SIZE][BOARD_SIZE];
		void initPieces();
		int remove(int pos1, int pos2);

	};



} // closes namespace

#endif