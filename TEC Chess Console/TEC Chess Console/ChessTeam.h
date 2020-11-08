/*/-------------------------------------------------------------------------------------//
	Filename:           ChessTeam.h
	Contributor:        Sonja Braden
	Date:               10/16/2020
	Reference:			https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzarg/inline_member.htm
	Description:
//-------------------------------------------------------------------------------------/*/

#ifndef CHESSTEAM_H
#define CHESSTEAM_H

#include "DerivedPieces.h"
#include "ChessExceptions.h"
#include "Grid.h"
#include <cassert>



namespace chess {

	class ChessTeam
	{
	public:

		struct team_ID { 

			int kCol;
			int kRow;
			ChessPiece::team_type team; 
			
			team_ID(int c = 4, int r = 0, ChessPiece::team_type t = ChessPiece::team_type::white) :
				kCol(c), kRow(r), team(t) {}

			team_ID operator=(const team_ID& right) {
				kCol = right.kCol;	
				kRow = right.kRow;
				team = right.team;
				return *this;
			}			
		};

		// Constructors
		ChessTeam();
		ChessTeam(Grid g, team_ID w, team_ID b, team_ID t);
				
		// Accessors
		Grid getGrid() const;
		bool isPiece(int inCol, int inRow) const;
		ChessPiece::team_type getTurnTeam() const;
		ChessPiece::team_type getTeamType(int pos1, int pos2) const;
		ChessPiece::piece_type getPieceType(int pos1, int pos2) const;
		
		// Other
		void move(int pos1, int pos2, int move1, int move2);
		bool isCheckmate();
		bool isStalemate();

		static const int MAX_PATH = 7; // 6 spaces for max path, and 1 more for an extra delimiter
		static const int BOARD_SIZE = 8;

	protected:

		// primary data members
		Grid grid;
		team_ID white;
		team_ID black;
		team_ID turn;
		
		// inline helpers to replace macros
		bool inBounds2(const int a, const int b) const;
		bool inBounds4(const int a, const int b, const int c, const int d) const;

		// Grid element accessors
		ChessPiece* getElement(int col, int row) const;

		// Grid element mutators
		void setPiece(int pos1, int pos2, int move1, int move2);
		void setElement(int col, int row, ChessPiece* ptr);

		// Other helpers 
		// void isValidMove(int pos1, int pos2, int move1, int move2);
		ChessTeam isValidMove(int pos1, int pos2, int move1, int move2) const;
		void remove(int x, int y);
		
		void evaluatePath(int* path) const;
		void setTurnKing(int move1, int move2);


		//-------------------Pawn-related functions------------------//
		
		int* validPawnMove(int pos1, int pos2, int move1, int move2) const;
		bool simpleAdvance(int pos1, int pos2, int move1, int move2) const;
		void resetEnPassant(int pos1, int pos2);
		bool isCapture(int pos1, int pos2, int move1, int move2) const;
		bool isEnPassant(int pos1, int pos2, int move1, int move2) const;
		void pawnPromote(int pos1, int pos2, int move1, int move2);

		//------------------King-related functions-------------------//
		
		bool validCastlePath(int k1, int k2, int r1, int r2);
		bool Castle(int pos1, int pos2, int move1, int move2);

		//-----------------Check & Checkmate functions---------------//
		
		bool isCheck(int pos1, int pos2) const;		// for evaluating specific squares

		bool KingIsTrapped();
		bool findBlockCapture(int attack1, int attack2);
		bool findBlock(int attack1, int attack2);
		bool findCapture(int attack1, int attack2);

		bool checkLaterals(int kCol, int kRow, int& attack1, int& attack2) const;
		bool singleLateral(int kCol, int kRow, int colSign, int rowSign, int& attack1, int& attack2) const;
		bool checkDiagonals(int kCol, int kRow, int& attack1, int& attack2) const;
		bool singleDiagonal(int kCol, int kRow, int colSign, int rowSign, int& attack1, int& attack2) const;
		bool checkKnight(int kCol, int kRow, int& attack1, int& attack2) const;
		bool singleKnight(int kCol, int kRow, int colSign, int rowSign, int& attack1, int& attack2) const;
		bool checkCorners(int kCol, int kRow, int& attack1, int& attack2) const;

		//-------------------Stalemate helper function------------------//

		bool isTrapped(int pos1, int pos2) const;	// if a piece has any legal moves available

	};

}	// closes namespace


#endif

// (*) https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzarg/inline_member.htm
