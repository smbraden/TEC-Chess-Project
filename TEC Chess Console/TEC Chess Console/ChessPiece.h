/*/-------------------------------------------------------------------------------------//
	Filename:           ChessPiece.h
	Contributor:        Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/


#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <cassert>				// for assert()
#include <stdlib.h>				// for abs()
#include "ChessExceptions.h"

// using namespace chess_except;

namespace chess {


	class ChessPiece {

		public:
			
			enum class team_type : unsigned char
			{ white = 'w', black = 'b', nullType = 't'};	// nullType for init ChessBoard 'Winner' member
			

			enum class piece_type : unsigned char
			{ none = '0', pawn = 'P', rook = 'R', knight = 'N', bishop = 'B', queen = 'Q', king = 'K', nullType = 't'};

			const static int BOARD_SIZE = 8;
			// const static int MAX_PATH = 7;
			const static int MAX_PATH_LEN = 14;		// 6 spaces for max path, and 1 more for an extra delimiter
			const static int ARRAY_END = -8;	// signals the end of a trapSet and path arrays

			ChessPiece();											// Default constructor
			ChessPiece(int inCol , int inRow , team_type color);	// Parameterized constructor
			
			// Acessors
			team_type getTeamType() const;
			piece_type getPieceType() const;
			void getPosition(int& inCol, int& inRow) const;
			int getCol() const;
			int getRow() const;
			
			// Mutators
			void setPosition(int inCol, int inRow);

			// Piece-specific evaluation
			virtual int* validMove(int inCol, int inRow) const;
			virtual int* getTrapSet() const;

		protected:

			int col;
			int row;
			team_type team;
			piece_type piece;
			
			virtual int* getPath(int inCol, int inRow);	// (*)
			
	};

} // closes namespace

#endif


/*

	(*)		virtual int* getPath(int inCol, int inRow);
			
			The returned int pointer, int* path, is such that:

			path[2 * BOAD_SIZE] = {c1, r1, c2, r2, c3, r3...c6, r6}
			path[n * 2]			= {c1, c2, c3,...cn,}
			path[n * 2 + 1]		= {r1, r2, r3,...rn,}


	Note:	According to our CS instructor, in "real" production code 
			one would never use the "protected" keyword. 
			This branch does so in all cases of inheritence anyways.
			Doing so simplifies the code, and all base and derived classes 
			never interface with a client; they are all modules 
			contributing to the ultimate client-facing class, ChessBoard,
			which has only private members.

	Note:	Some member functions would be better as pure virtual functions;
			however, it is not desirable to make this an abstract class
			because we would like to manage a collection of ChessPieces via
			array of pointers, or another data structures that can only manage
			a collection of objects of the same types, in this case, 
			the base class, ChessPiece. We cannot instaniate/declare an abstract class
			for such purposes.
			Hence, ChessPiece as a true abstract class is not compatible with
			design goals, despite that it serves quite like an abstract class.		*/