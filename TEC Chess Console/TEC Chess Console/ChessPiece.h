/*/-------------------------------------------------------------------------------------//
	Filename:           ChessPiece.h
	Contributor:        Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:

//-------------------------------------------------------------------------------------/*/

	/**	Stores the current col and row position in the two arguments
		@pre inCol and inRow are variable integers (can be passed by reference)
		@post inCol and inRow arguments now contain the values of
			calling objext's col and row members
		@return void
		
	void getPosition(int& inCol, int& inRow) const;  */


	/**	Returns the piece type
		@pre An instantiated ChessPiece object
		@post No change to the object
		@return the piece_type: bishop, king, queen, etc.
			(an enumerated type belong to the ChessPiece Class) 

	piece_type getPieceType() const;	*/


	/**	Returns the team type
		@pre An instantiated ChessPiece object
		@post No change to the object
		@return the team_type: black or white
			(an enumerated type belong to the ChessPiece Class) 
	
	char getTeamType() const = 0;	*/


	/**	Mutator. Changes the position coordinates members, col and row
		@pre An instantiated ChessPiece object
		@post The new position (inCol, inRow) will be set to the members
			if the move complies with the rules of movement defined for the piece
			(but excluding conditions involving relativity to other pieces,
			and the boundaries of the board)
		@return Pointer to int array of size MAX_PATH.
			The int array contains the set of spaces that the piece has
			to traverse to reach the destination
	
	virtual int* setPosition(int inCol, int inRow) = 0;	*/


#ifndef CHESSPIECE_H
#define CHESSPIECE_H


namespace chess {


	class ChessPiece {

		public:

			enum class team_type : unsigned char
			{
				none = '0', white = 'w', black = 'b'
			};

			enum class piece_type : unsigned char
			{
				none = '0', pawn = 'P', rook = 'R', knight = 'N', bishop = 'B', queen = 'Q', king = 'K'
			};


			const static int MAX_PATH = 6;
			class PieceMoveError {};

			ChessPiece(int inCol = 0, int inRow = 0, team_type color = team_type::white);
			void getPosition(int& inCol, int& inRow) const;
			piece_type getPieceType() const;
			team_type getTeamType() const;
			virtual int* setPosition(int inCol, int inRow);

		protected:

			int col;
			int row;
			team_type team;
			piece_type piece;
			virtual int* getPath(int inCol, int inRow);
			// int[] with 6 possible coordinates, and -1 signals end of coordinates

			/*	path[2 * BOAD_SIZE] = {c1, r1, c2, r2, c3, r3...c6, r6}
				path[n * 2]			= {c1, c2, c3,...cn,}
				path[n * 2 + 1]		= {r1, r2, r3,...rn,}	*/

	};

} // closes namespace

#endif

/*	Note:	Some member functions would be better as pure virtual functions;
			however, it is not desirable to make this an abstract class
			because we would like to manage a collection of ChessPieces via
			arra of pointers, or another data structures that can only manage
			a collection of objects of the same types.We will use the
			base class ChessPiece to make such declarations, and this
			cannot be done with an abstract class, which cannot be instantiated.
			Hence, ChessPiece as an abstract class is not compatible with
			design goals, despite that it srves more as an abstract class.		*/