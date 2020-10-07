/*/-------------------------------------------------------------------------------------//
	Filename:           ChessPiece.h
	Contributor:        Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:		Implementation  of the ChessPiece class. This is the base
						class from which unique types of pieces are derived 
						(queen, king, etc.) Unique types have different error checking 
						for valid movement by the rules of chess.						
//-------------------------------------------------------------------------------------/*/




#include "ChessPiece.h"

namespace chess {
	
	
	ChessPiece::ChessPiece(int inCol, int inRow, team_type color)
	{
		assert((inCol < BOARD_SIZE) && (inRow < BOARD_SIZE) && (inCol >= 0) && (inRow >= 0));
		row = inRow;
		col = inCol;
		team = color;
		piece = piece_type::none;
	}






	void ChessPiece::getPosition(int& inCol, int& inRow) const
	{
		inRow = row;
		inCol = col;
	}






	ChessPiece::piece_type ChessPiece::getPieceType() const
	{
		return piece;
	}






	ChessPiece::team_type ChessPiece::getTeamType() const
	{
		return team;
	}





	// Precondition:	validMove() has been called with no exceptions
	//					AND the path returned has been evualted, and is clear
	void ChessPiece::setPosition(int inCol, int inRow)
	{
		assert(inCol < BOARD_SIZE && inRow < BOARD_SIZE && inCol >= 0 && inRow >= 0);
		col = inCol;
		row = inRow;
	}







	/*	Returns the "path" to the destination if move is otherwise valid.
		Validity of moves in the land of ChessPiece does not consider board bounds, nor
		"jumps" over other pieces. The "path" returned will represent 
		the spaces between current position and destination (not inclusive). 
		compliance with non-jump moves will be evaluated by 
		the ChessBoard client, which manages info on all piece positions	*/

	int* ChessPiece::validMove(int inCol, int inRow) const
	{
		assert(inCol < BOARD_SIZE && inRow < BOARD_SIZE && inCol >= 0 && inRow >= 0);
		int* path = nullptr;
		return path;
	}

	/* Real pieces will take the folloing form 
 		
		int* ChessPiece::setPosition(int inCol, int inRow)
		{
			int* path = nullptr;
		
			if ( Valid move ) {

				path = getPath();

			}
			else {

				throw PieceMoveError();
			}

			return path;
		}
	*/






	int* ChessPiece::getPath(int inCol, int inRow)
	{
		assert(inCol < BOARD_SIZE && inRow < BOARD_SIZE && inCol >= 0 && inRow >= 0);
		int* path = nullptr;
		
		/*	Real pieces will calculate the path:
		
			path = new int[2 * MAX_PATH];
		
			for ( r = 0; r < MAX_PATH; r++) {
				path[2 * r] =		pathCol_r;
				path[2 * r + 1] =	pathRow_r;
			}

		*/

		return path;
	}

}  // closes namespace

