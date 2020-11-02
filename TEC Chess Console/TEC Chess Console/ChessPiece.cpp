/*/-------------------------------------------------------------------------------------//
	Filename:           ChessPiece.h
	Contributor:        Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:		Implementation  of the ChessPiece class. This is the base
						class from which unique types of pieces are derived 
						(queen, king, etc.) Unique types have different error checking 
						for valid movement by the rules of chess.	

						Mutators for the piece and team members are intentionally absent.
						For the derived ChessPiece's, we want to set these members 
						at construction, and allow them to never change
						(accidentally, or otherwise)
//-------------------------------------------------------------------------------------/*/




#include "ChessPiece.h"

namespace chess {

	// Default constructor
	ChessPiece::ChessPiece()
	{
		col = 0;
		row = 0;
		team = team_type::white;
		piece = piece_type::none;
	}
	
	




	// Parameterized constructor
	ChessPiece::ChessPiece(int inCol, int inRow, team_type color)
	{
		assert((inCol < BOARD_SIZE) && (inRow < BOARD_SIZE) && (inCol >= 0) && (inRow >= 0));
		row = inRow;
		col = inCol;
		team = color;
		piece = piece_type::none;
	}





	// Accessor
	void ChessPiece::getPosition(int& inCol, int& inRow) const
	{
		inRow = row;
		inCol = col;
	}





	// Accessor
	int ChessPiece::getCol() const
	{
		return col;
	}





	// Accessor
	int ChessPiece::getRow() const
	{
		return row;
	}






	// Accessor
	ChessPiece::team_type ChessPiece::getTeamType() const
	{
		return team;
	}





	
	// Accessor
	ChessPiece::piece_type ChessPiece::getPieceType() const
	{
		return piece;
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
		Validity of moves in the ChessPiece class does not consider board bounds, nor
		"jumps" over other pieces, or other relations to board state. The "path" returned 
		represents the spaces between current position and destination (not inclusive). 
		compliance with non-jump moves will be evaluated by 
		the ChessBoard client, which manages info regarding all piece positions	*/

	int* ChessPiece::validMove(int inCol, int inRow) const
	{
		assert(inCol < BOARD_SIZE && inRow < BOARD_SIZE && inCol >= 0 && inRow >= 0);
		int* path = nullptr;
		return path;
	}
	/* Real pieces will take the following form 
 		
		int* ChessPiece::setPosition(int inCol, int inRow)
		{
			int* path = nullptr;
		
			if ( Valid move )
				path = getPath();
			else
				throw PieceMoveError();
			
			return path;
		}
	*/





	int* ChessPiece::getTrapSet() const
	{
		return nullptr;
	}







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

