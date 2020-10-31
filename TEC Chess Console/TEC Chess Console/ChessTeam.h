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
#include "Grid.h"
#include <cassert>


namespace chess {

	class ChessTeam
	{
	public:

		// Constructors
		ChessTeam();
		ChessTeam(ChessPiece::team_type t, Grid g, bool m);
				
		// Accessors
		Grid getGrid() const;
		int getKCol() const;
		int getKRow() const;
		bool getCheckmateStatus() const;
		ChessPiece::team_type getTeam() const;
		
		// Mutators
		void setGrid(const Grid& arg);
		void setKing(int move1, int move2);
		void setCheckmateStatus(bool arg);
		void setTeam(ChessPiece::team_type t);
		
		// Other
		void move(int pos1, int pos2, int move1, int move2);
		bool isCheckmate();
		bool isStalemate();

		static const int MAX_PATH = 7; // 6 spaces for max path, and 1 more for an extra delimiter
		static const int BOARD_SIZE = 8;

	protected:

		// primary data members
		Grid grid;
		int kCol;						// column of team's king
		int kRow;						// row of team's king
		ChessPiece::team_type team;		// team's type, white or black
		bool checkmateStatus;

		// inline helpers to replace macros
		bool inBounds2(const int a, const int b) const;
		bool inBounds4(const int a, const int b, const int c, const int d) const;

		// Grid element accessors
		ChessPiece* getElement(int col, int row) const;
		ChessPiece::team_type getTeam(int pos1, int pos2) const;
		ChessPiece::piece_type getPiece(int pos1, int pos2) const;

		// Grid element mutators
		void setPiece(int pos1, int pos2, int move1, int move2);
		void setElement(int col, int row, ChessPiece* ptr);

		// Other helpers 
		ChessTeam isValidMove(int pos1, int pos2, int move1, int move2) const;
		void remove(int x, int y);
		bool isPiece(int inCol, int inRow) const;
		void evaluatePath(int* path) const;
		
		//-------------------Pawn-related functions------------------//
		
		int* validPawnMove(int pos1, int pos2, int move1, int move2) const;
		bool simpleAdvance(int pos1, int pos2, int move1, int move2) const;
		void resetEnPassant(int pos1, int pos2);

		// Symmetry-dependent //
		virtual bool isCapture(int pos1, int pos2, int move1, int move2) const;
		virtual bool isEnPassant(int pos1, int pos2, int move1, int move2) const;
		virtual void pawnPromote(int pos1, int pos2, int move1, int move2);

		//------------------King-related functions-------------------//
		
		bool validCastlePath(int k1, int k2, int r1, int r2);

		// Symmetry-dependent //
		virtual bool Castle(int pos1, int pos2, int move1, int move2);

		//-----------------Check & Checkmate functions----------------//
		
		bool isCheck() const;						// for assessing Game State
		bool isCheck(int pos1, int pos2) const;		// for evaluating specific squares

		bool checkLaterals(int kCol, int kRow) const;
		bool singleLateral(int kCol, int kRow, int colSign, int rowSign) const;
		bool checkDiagonals(int kCol, int kRow) const;
		bool singleDiagonal(int kCol, int kRow, int colSign, int rowSign) const;
		bool checkKnight(int kCol, int kRow) const;
		bool singleKnight(int kCol, int kRow, int colSign, int rowSign) const;

		// Symmetry-dependent//
		virtual bool checkCorners(int kCol, int kRow) const;
		
		//---------------StaleMate & Checkmate functions--------------//

		bool isTrapped(int pos1, int pos2) const;	// if a piece has any legal moves available
		
	};

}	// closes namespace


#endif

// (*) https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzarg/inline_member.htm
