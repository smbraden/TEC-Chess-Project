/*/-------------------------------------------------------------------------------------//
	Filename:           ChessPiece.h
	Contributor:        Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:

//-------------------------------------------------------------------------------------/*/

#ifndef CHESSPIECE_H
#define CHESSPIECE_H


namespace chess {


	class ChessPiece {

		public:

			enum class team_type : unsigned char
			{ white = 'w', black = 'b', nullType = 'n' };

			enum class piece_type : unsigned char
			{ none = '0', pawn = 'P', rook = 'R', knight = 'N', bishop = 'B', queen = 'Q', king = 'K' };

			const static int BOARD_SIZE = 8;
			const static int MAX_PATH = 7;	 // 6 spaces for max path, and 1 more for an extra delimiter
			class PieceMoveError {};

			ChessPiece();											// Default constructor
			ChessPiece(int inCol , int inRow , team_type color);	// Parameterized constructor
			
			// Accessors
			team_type getTeamType() const;
			piece_type getPieceType() const;
			void getPosition(int& inCol, int& inRow) const;
			int getCol() const;
			int getRow() const;
			
			// Mutators
			void setPosition(int inCol, int inRow);
			void setTeamType(team_type);
			void setPieceType(piece_type);
			virtual int* validMove(int inCol, int inRow) const;

		private:

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


	Note:	According to Dave Harden, in "real" production code 
			one would never use the "protected" keyword. 
			Instead, one would provide accessors and mutators to allow 
			derived classes to access or mutate the private data members.

			The code was recently refactored to avoid using a 
			protected Base Class Access Specification.
			Derived classes now access base memebers only via accessors/mutators

	Note:	Some member functions would be better as pure virtual functions;
			however, it is not desirable to make this an abstract class
			because we would like to manage a collection of ChessPieces via
			array of pointers, or another data structures that can only manage
			a collection of objects of the same types, in this case, 
			the base class, ChessPiece. We cannot instaniate/declare an abstract class
			for such purposes.
			Hence, ChessPiece as a true abstract class is not compatible with
			design goals, despite that it serves quite like an abstract class.		*/