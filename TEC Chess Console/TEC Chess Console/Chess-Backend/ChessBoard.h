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
		team_type getTurnTeam();
		char getTurnTeamUnlyingType();
		team_type getWinner();
		char getWinnerUnlyingType();
		void reset();

		// static const int BOARD_SIZE = 8;
		

	private:

		// Grid grid;
		team_type winner;
		History history;
		ChessTeam turnMachine;
		bool draw;

		// For convenient access to Grid Elements
		bool isPiece(int pos1, int pos2) const;
		team_type getTeamType(int pos1, int pos2) const;
		piece_type getPieceType(int pos1, int pos2) const;
		
	};



} // closes namespace

#endif


// (*) https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzarg/inline_member.htm