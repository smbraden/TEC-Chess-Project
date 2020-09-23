/*/-------------------------------------------------------------------------------------//
	Filename:           ChessPiece.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:		Implementation  of the ChessPiece class. This is the base
						class from which unique types of pieces are derived 
						(queen, king, etc.) Unique types have different error checking 
						for valid movement.
//-------------------------------------------------------------------------------------/*/


#include "ChessPiece.h"

//using namespace std;

namespace chess {
	
	
	ChessPiece::ChessPiece(int inCol, int inRow,team_type color)
	{
		row = inRow;
		col = inCol;
		piece = none;
		team = color;
	}






	void ChessPiece::getPosition(int& inCol, int& inRow) const
	{
		inRow = row;
		inCol = col;

	}






	char ChessPiece::getPieceType() const
	{
		return piece;
	}






	char ChessPiece::getTeamType() const
	{
		return team;
	}





	// Returns the "path" the new space if the move is valid
	// validity of piece moves does not consider board bounds, nor
	// "jumps" over other pieces. The "path" returned will represent 
	// the spaces between current position and move. 
	// compliance with non-"jump" moves will be evaluated by 
	// the ChessBoard client, which manages info of all piece positions

	int* ChessPiece::setPosition(int inCol, int inRow)
	{
		/*
		if ( Valid move ) {

			col = inCol;
			row = inRow;
			
			int* path = getPath();
		}
		else {
			
			throw PieceMoveError();
		}

		return path;
		*/
	}






	//	always returns pointer to array of length (2 * MAX_PATH)
	int* ChessPiece::getPath(int inCol, int inRow)
	{
		/*
		int numSpaces = (calc num spaces);
		int *path = new int[2 * MAX_PATH];
		
		for ( r = 0; r < numSpaces; 2 * (r++)) {
			path[r] =		pathCol_r;
			path[r + 1] =	pathRow_r;
		}

		return path;
		*/
	}

}  // closes namespace

