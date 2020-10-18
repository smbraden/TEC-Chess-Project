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

		// Big-3
		Grid();
		Grid(const Grid&);
		~Grid();
		Grid operator=(const Grid&);

		ChessPiece* getElement(int col, int row) const;
		void setElement(int col, int row, ChessPiece* ptr);
		void remove(int c, int r);
		bool isPiece(int inCol, int inRow) const;	// verifies coordinates in bounds and correspond to an object

		static const int BOARD_SIZE = 8;

	private:

		ChessPiece* grid[BOARD_SIZE * BOARD_SIZE];

		// Big-3 helpers
		void copy(const Grid& arg);
		void clear();
		
	};

} // closes namespace

#endif