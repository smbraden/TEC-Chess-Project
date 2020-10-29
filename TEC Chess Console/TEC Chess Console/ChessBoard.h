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

		void move(int pos1, int pos2, int move1, int move2);
		void printBoard() const;
		ChessPiece::team_type getTurn();
		ChessPiece::team_type getWinner();

		static const int BOARD_SIZE = 8;
		


	private:

		// main data members
		Grid grid;
		ChessPiece::team_type turn;
		ChessPiece::team_type winner;
		History history;
		
		WhiteTeam whiteT;
		BlackTeam blackT;

		// constructor helpers
		void copy(const ChessBoard&);
		void initPieces();

		// For convenient access to Grid Elements
		ChessPiece* getElement(int col, int row) const;
		void setElement(int col, int row, ChessPiece* ptr);
		ChessPiece::team_type getTeam(int pos1, int pos2) const;
		ChessPiece::piece_type getPiece(int pos1, int pos2) const;
		
		// inline helpers to replace macros (*)
		bool inBounds2(const int a, const int b) const;
		bool inBounds4(const int a, const int b, const int c, const int d) const;
	};



} // closes namespace

#endif


// (*) https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzarg/inline_member.htm