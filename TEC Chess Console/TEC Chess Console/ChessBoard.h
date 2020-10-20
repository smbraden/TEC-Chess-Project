/*/-------------------------------------------------------------------------------------//
	Filename:           ChessBoard.h
	Contributor:        Sonja Braden
	Date:               10/16/2020
	Reference:
	Description:        
//-------------------------------------------------------------------------------------/*/


#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "DerivedTeams.h"

namespace chess {

	class ChessBoard {

	public:

		ChessBoard();
		ChessBoard(const ChessBoard&);

		void moveWhite(int pos1, int pos2, int move1, int move2); // indices 0-7 
		void moveBlack(int pos1, int pos2, int move1, int move2); // (col ,row)
		void printBoard() const;
						
		static const int BOARD_SIZE = 8;
		
	private:

		// main data members
		Grid grid;
		ChessPiece::team_type Winner;
		History history;

		WhiteTeam whiteT;
		BlackTeam blackT;

		void copy(const ChessBoard&);
		void initPieces();

		// Private Grid Element Accessors/Mutators
		ChessPiece* getElement(int col, int row) const;
		void setElement(int col, int row, ChessPiece* ptr);
		ChessPiece::team_type getTeam(int pos1, int pos2) const;
		ChessPiece::piece_type getPiece(int pos1, int pos2) const;
		
		// Check status Accessors and Mutators
		ChessPiece::team_type getWinner();
		void setWinner(ChessPiece::team_type arg);

	};



} // closes namespace

#endif