/*/-------------------------------------------------------------------------------------//
	Filename:           ChessPieceInterface.h
	Contributor:        Sonja Braden
	Date:               9/23/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/

#ifndef CHESSPIECE_H
#define CHESSPIECE_H


class ChessPiece {

public:

	enum team_type { white = 'w', black = 'b' };
	enum piece_type { base = 'B', pawn = 'P', castle = 'C', 
					knight = 'N', rook = 'R', queen = 'Q', king = 'K'};

	/**	Stores the current col and row position in the two arguments
	@pre inCol and inRow are variable integers (can be passed by reference)
	@post inCol and inRow arguments now contain the values of 
	calling objext's col and row members 
	@return void */
	virtual void getPosition(int& inCol, int& inRow) const = 0;

	/**	Returns the piece type
	@pre An instantiated ChessPiece object
	@post No change to the object
	@return the piece_type: rook, king, queen, etc.
			(an enumerated type belong to the ChessPiece Class) */
	virtual piece_type getPieceType() const = 0;
		
	/**	Returns the team type
	@pre An instantiated ChessPiece object
	@post No change to the object
	@return the team_type: black or white
			(an enumerated type belong to the ChessPiece Class) */
	virtual char getTeamType() const = 0;

	/**	Mutator. Changes the position coordinates members, col and row
	@pre An instantiated ChessPiece object
	@post The new position (inCol, inRow) will be set to the members
	if the move complies with the rules of movement defined for the piece
	(but excluding conditions involving relativity to other pieces, 
	and the boundaries of the board) 
	@return Pointer to int array of size MAX_PATH. 
			The int array contains the set of spaces that the piece has 
			to traverse to reach the destination*/
	virtual int* setPosition(int inCol, int inRow) = 0;

};


#endif