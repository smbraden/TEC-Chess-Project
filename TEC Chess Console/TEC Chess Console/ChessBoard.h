/*/-------------------------------------------------------------------------------------//
	Filename:           ChessBoard.h
	Contributor:        Sonja Braden
	Date:               10/16/2020
	Reference:			
	Description:        
//-------------------------------------------------------------------------------------/*/


#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessTeam.h"
#include "History.h"

namespace chess {

	class ChessBoard {

	public:

		ChessBoard();

		void move(int pos1, int pos2, int move1, int move2);
		void printBoard() const;
		ChessPiece::team_type getTurnTeam();
		ChessPiece::team_type getWinner();

		static const int BOARD_SIZE = 8;
		

	private:

		// Grid grid;
		ChessPiece::team_type winner;
		History history;
		ChessTeam turnMachine;
		bool draw;

		// For convenient access to Grid Elements
		bool isPiece(int pos1, int pos2) const;
		ChessPiece::team_type getTeamType(int pos1, int pos2) const;
		ChessPiece::piece_type getPieceType(int pos1, int pos2) const;
		
		// inline helpers to replace macros (*)
		bool inBounds2(const int a, const int b) const;
		bool inBounds4(const int a, const int b, const int c, const int d) const;
	};



} // closes namespace

#endif


// (*) https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzarg/inline_member.htm