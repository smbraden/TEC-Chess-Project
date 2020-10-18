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
#include "ChessTeam.h"
#include "Grid.h"

namespace chess {

	class ChessBoard {

	public:

		// Big-3
		ChessBoard();
		ChessBoard(const ChessBoard&);
		~ChessBoard();
		ChessBoard operator=(const ChessBoard&);

		void moveWhite(int pos1, int pos2, int move1, int move2); // indices 0-7 
		void moveBlack(int pos1, int pos2, int move1, int move2); // (col ,row)
		void printBoard() const;

		class TurnMoveError {};		// when a player attempts to move the opponent's piece
		// class EmptySquareError {};	// Attempt to move an empty square
		
		static const int BOARD_SIZE = 8;
		
	private:

		// main data members
		ChessPiece** grid;
		ChessPiece::team_type Winner;
		ChessTeam whiteT;
		ChessTeam blackT;

		// 3-Big helper functions
		void remove(int x, int y);
		void clear();
		void copy(const ChessBoard&);
		void initPieces();

		// Private Grid Element Accessors/Mutators
		ChessPiece* getElement(int col, int row) const;
		ChessPiece* setElement(int col, int row, ChessPiece* ptr);
		ChessPiece::team_type getTeam(int pos1, int pos2) const;
		ChessPiece::piece_type getPiece(int pos1, int pos2) const;
		bool isPiece(int inCol, int inRow) const;	// verifies coordinates in bounds and correspond to an object

		// Check status Accessors and Mutators
		ChessPiece::team_type getWinner();
		void setWinner(ChessPiece::team_type arg);

	};



} // closes namespace

#endif