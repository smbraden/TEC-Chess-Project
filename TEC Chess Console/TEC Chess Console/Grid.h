/*/-------------------------------------------------------------------------------------//
	Filename:           Grid.cpp
	Contributor:        Sonja Braden
	Date:               10/16/2020
	Reference:
	Description:        
//-------------------------------------------------------------------------------------/*/

#ifndef GRID_H
#define GRID_H

#include "DerivedPieces.h"
#include <cassert>



namespace chess {

	class Grid {

	public:

		Grid();
		
		// Big-3
		Grid(const Grid&);
		~Grid();
		Grid operator=(const Grid&);

		ChessPiece* getElement(int col, int row) const;
		ChessPiece::piece_type getPieceType(int col, int row) const;
		ChessPiece::team_type getTeamType(int col, int row) const;
		void setElement(int col, int row, ChessPiece* ptr);
		void remove(int c, int r);
		bool isPiece(int inCol, int inRow) const;	// verifies coordinates in bounds and correspond to an object

		static const int BOARD_SIZE = 8;

	private:

		// ChessPiece* grid[BOARD_SIZE * BOARD_SIZE];	
		ChessPiece* grid[BOARD_SIZE][BOARD_SIZE];

		// Big-3 helpers
		void copy(const Grid& arg);
		void clear();

		// constructor helper
		void initPieces();

		// inline helpers to replace macros (*)
		// int toGrid(const int c, const int r) const;
		bool inBounds2(const int a, const int b) const;
		bool inBounds4(const int a, const int b, const int c, const int d) const;
	};

} // closes namespace

#endif

// (*) https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzarg/inline_member.htm