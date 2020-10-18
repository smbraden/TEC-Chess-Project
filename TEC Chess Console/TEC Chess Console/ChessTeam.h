/*/-------------------------------------------------------------------------------------//
	Filename:           ChessTeam.h
	Contributor:        Sonja Braden
	Date:               10/16/2020
	Reference:
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
		ChessTeam(ChessPiece::team_type t, Grid* g, bool m);

		// Accessors
		int getKCol() const;
		int getKRow() const;
		bool getCheckmateStatus() const;
		ChessPiece::team_type getTeam() const;
		Grid* getGridPtr();


		// Mutator
		void setKing(int move1, int move2);
		void setCheckmateStatus(bool arg);
		void setTeam(ChessPiece::team_type t);
		void setGridPtr(Grid* arg);

		// Other
		void move(int pos1, int pos2, int move1, int move2);

		// Error handling
		class SelfCapturError {};	// moving a piece to a position already occupied by that team
		class NoTurnPassError {};	// Equivalent to moving a piece to it's current position
		class TurnMoveError {};		// when a player attempts to move the opponent's piece
		class BoundsError {};		// for moves that go out of board bounds
		class EmptySquareError {};	// Attempt to move an empty square
		class IndirectPathError {};	// For attempts to jump over other pieces if not knight 
		class CheckError {};		// if King in Check, must escape the check

		const int MAX_PATH = 7; // 6 spaces for max path, and 1 more for an extra delimiter
		static const int BOARD_SIZE = 8;

	protected:	// I'm being lazy for the moment

		// primary members
		Grid* gridPtr;					
		int kCol;						// column of team's king
		int kRow;						// row of team's king
		ChessPiece::team_type team;		// team's type, white or black
		bool checkmateStatus;

		// helper functions
		void remove(int x, int y);

		// private accessors
		ChessPiece* getElement(int col, int row) const;
		void setElement(int col, int row, ChessPiece* ptr);

		// Grid element accessors
		ChessPiece::team_type getTeam(int pos1, int pos2) const;
		ChessPiece::piece_type getPiece(int pos1, int pos2) const;

		// Mutators
		void setPiece(int pos1, int pos2, int move1, int move2);

		// Other helpers 
		bool isPiece(int inCol, int inRow) const;	// verifies coordinates in bounds and correspond to an object
		void evaluatePath(int* path) const;
		

		//-------------------Pawn-related functions------------------//
		int* validPawnMove(int pos1, int pos2, int move1, int move2) const;
		bool simpleAdvance(int pos1, int pos2, int move1, int move2) const;
		void resetEnPassant(int pos1, int pos2);

		// Symmetry-dependent//
		virtual bool isCapture(int pos1, int pos2, int move1, int move2) const;
		virtual bool isEnPassant(int pos1, int pos2, int move1, int move2) const;
		virtual void pawnPromote(int pos1, int pos2, int move1, int move2);



		//------------------King-related functions-------------------//
		bool validCastlePath(int k1, int k2, int r1, int r2);

		// Symmetry-dependent//
		virtual bool Castle(int pos1, int pos2, int move1, int move2);



		//-----------------------Check functions---------------------//
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

		
	};

}	// closes namespace


#endif