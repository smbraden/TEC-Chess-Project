/*/-------------------------------------------------------------------------------------//
	Filename:           ChessBoard.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:        Annoyingly, I have index the Board coordinates as [Column][Row],
						as this is how a chess board is labeled 
						(eg, a1, a2, b5, etc. where letters are columns ).
//-------------------------------------------------------------------------------------/*/


#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include  "DerivedPieces.h"

namespace chess {

	class ChessBoard {

	public:

		ChessBoard();
		ChessBoard(const ChessBoard&);
		~ChessBoard();
		ChessBoard operator=(const ChessBoard);
		
		class SelfCapturError {};	// moving a piece to a position already occupied by that team
		class NoTurnPassError {};	// Passing is not allowed in the classic rules of chess.
									// This is the same as moving a piece to it's current position
		class TurnMoveError {};		// when a player attempts to move the opponent's piece
		class BoundsError {};		// for moves that go out of board bounds
		class EmptySquareError {};	
		class IlegalMoveError {};	// any other illegal moves

		int moveWhite(int pos1, int pos2, int move1, int move2); // indices 0-7 
		int moveBlack(int pos1, int pos2, int move1, int move2); // (col ,row)
		//ChessPiece::team_type getTeam(int pos1, int pos2);
		//ChessPiece::piece_type getPiece(int pos1, int pos2);
		void printBoard();

		const int MAX_PATH = 6;
		static const int BOARD_SIZE = 8;
		const int SPACES = 64;

	private:

		ChessPiece* grid[BOARD_SIZE][BOARD_SIZE];
		void initPieces();
		void evaluatePath(int* path);
		void move(int pos1, int pos2, int move1, int move2, ChessPiece::team_type); //
		void remove(int pos1, int pos2);
		void clear();
		void copy(const ChessBoard);
		bool isPiece(int inCol, int inRow);
	};



} // closes namespace

#endif