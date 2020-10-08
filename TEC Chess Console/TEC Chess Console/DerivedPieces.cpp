/*/-------------------------------------------------------------------------------------//
	Filename:           DerivedPieces.cpp
	Contributors:       Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:		Implementation of all the derived ChessPieces
//-------------------------------------------------------------------------------------/*/


#include "DerivedPieces.h"



namespace chess {


	//------------------------------Pawn-----------------------------------//

	Pawn::Pawn() : ChessPiece()
	{
		enPassant = false;
		setPieceType(piece_type::pawn);
	}






	Pawn::Pawn(int inCol, int inRow, team_type color) : ChessPiece(inCol, inRow, color)
	{
		enPassant = false;
		setPieceType(piece_type::pawn);
	}






	/* Precondition:	the potential validity of the move with respect to 
						other pieces on the board has been evaluated and confirmed.
						(ie pieces blocking the pawn vs pieces captured by the pawn)	*/
	int* Pawn::validMove(int inCol, int inRow)
	{
		int* path = nullptr;
		ChessPiece::team_type team = getTeamType();
		int col = getCol();
		int row = getRow();
		
		if (team == team_type::black) {

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 6 && inRow == 4 && col == inCol) || (inRow == (row - 1) && col == inCol)) {
				if (row == 6 && inRow == 4) {			// col == inCol implied
					path = getPath(inCol, inRow);	// only need path if moved two spaces
					setEnPassant(true);
				}
			}
			else if (row == inRow + 1 && abs(col - inCol) == 1) {	// diagonal capture, no path

			}
			else {
				throw PieceMoveError();
			}
		}
		else { //  if (team == white)

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 1 && inRow == 3 && col == inCol) || (inRow == row + 1 && col == inCol)) {
				if (row == 1 && inRow == 3) {		//  col == inCol
					path = getPath(inCol, inRow);	// only need path if moved two spaces
					setEnPassant(true);
				}
			}
			else if (inRow == row + 1 && abs(col - inCol) == 1) {	// diagonal capture, no path

			}
			else {
				throw PieceMoveError();
			} 
		}

		return path; // could be condensed, but with lengthy, less-readable condition statements
	}






	
	bool Pawn::getEnPassant() const
	{
		return enPassant;
	}






	void Pawn::setEnPassant(bool arg)
	{
		enPassant = arg;
	}
	





	// Precondition:	the move was a 2-space advance from the initial row
	int* Pawn::getPath(int inCol, int inRow) const
	{
		int* path = nullptr;
		int row = getRow();
		ChessPiece::team_type team = getTeamType();

		if (abs(inRow - getRow()) == 2) {

			path = new int[2 * MAX_PATH]{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
			path[0] = inCol;
			path[1] = (team == team_type::black ? inRow + 1 : row + 1);
			
		}
		return path;	// path is nullptr if no spaces between position and destination
	}
	
	




	//------------------------------Rook-----------------------------------//
	
	Rook::Rook() : ChessPiece()
	{
		setPieceType(piece_type::rook);
	}






	Rook::Rook(int inCol, int inRow, team_type color) : ChessPiece(inCol, inRow, color)
	{
		setPieceType(piece_type::rook);
	}






	int* Rook::validMove(int inCol, int inRow) const
	{
		int* path = nullptr;
		int col = getCol();
		int row = getRow();


		if ((row == inRow) || (col == inCol)) // if moving only along columns or rows
			path = getPath(inCol, inRow);
		else
			throw PieceMoveError();

		return path;
	}






	int* Rook::getPath(int inCol, int inRow) const
	{
		int* path = nullptr;
		int col = getCol();
		int row = getRow();

		if (abs(inCol - col) > 1 || abs(inRow - row) > 1) {	// if more than 1 squares traversed

			path = new int[2 * MAX_PATH]{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
			int j = 0;
			
			if (col == inCol) {	// same column

				if (row > inRow) {

					int nextRow = inRow + 1;
					while (nextRow != row) {

						path[2 * j] = inCol;
						path[2 * j + 1] = nextRow;
						nextRow++;					
						j++;
					}
				}
				else {	// if row < inRow

					int nextRow = row + 1;
					while (nextRow != inRow) {

						path[2 * j] = inCol;
						path[2 * j + 1] = nextRow;
						nextRow++;					
						j++;
					}
				}
			}
			else if (row == inRow) {	// same column

				if (col > inCol) {

					int nextCol = inCol + 1;
					while (nextCol != col) {

						path[2 * j + 1] = inRow;
						path[2 * j] = nextCol;
						nextCol++;					
						j++;
					}
				}
				else {	// if col < inCol

					int nextCol = col + 1;
					while (nextCol != inCol) {

						path[2 * j + 1] = inRow;
						path[2 * j] = nextCol;
						nextCol++;					
						j++;
					}
				}
			}
		}
		
		return path;
	}






	//------------------------------Knight-----------------------------------//

	Knight::Knight() : ChessPiece()
	{
		setPieceType(piece_type::knight);
	}






	Knight::Knight(int inCol, int inRow, team_type color) : ChessPiece(inCol, inRow, color)
	{
		setPieceType(piece_type::knight);
	}






	// Although the return "path" for Knights is irrelevant,
	// the rules of inheitance dictate that the return type is the 
	// same as that of the base class for overriden virtual functions.
	// Thus, we will simply return nullptr for all Kight moves, correct or incorrect
	int* Knight::validMove(int inCol, int inRow) const
	{
		int col = getCol();
		int row = getRow();

		bool cond1 = abs(col - inCol) == 2 && abs(row - inRow) == 1; // (1, 0) ---> (0, 2)
		bool cond2 = abs(row - inRow) == 2 && abs(col - inCol) == 1;

		if (cond1 || cond2) {

		}
		else {
			throw PieceMoveError();
		}
		
		return nullptr;
	}






	int* Knight::getPath(int inCol, int inRow) const
	{
		return nullptr;	// no path for knights, they can leap
	}






	//------------------------------Bishop-----------------------------------//

	Bishop::Bishop() : ChessPiece()
	{
		setPieceType(piece_type::bishop);
	}






	Bishop::Bishop(int inCol, int inRow, team_type color) : ChessPiece(inCol, inRow, color)
	{
		setPieceType(piece_type::bishop);
	}






	int* Bishop::validMove(int inCol, int inRow) const
	{
		int* path = nullptr;
		int col = getCol();
		int row = getRow();

		if ((col - inCol) == (row - inRow) || (col - inCol) == -(row - inRow)) {
			
			path = getPath(inCol, inRow);

		}
		else {
			throw PieceMoveError();
		}

		return path;
	}





	
	int* Bishop::getPath(int inCol, int inRow) const
	{
		int* path = nullptr;
		int col = getCol();
		int row = getRow();

		if (abs(inCol - col) == 1 && abs(inRow - row) == 1)	// moved by only 1 space
			return nullptr;
		else {
			path = new int[2 * MAX_PATH]{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };	// function for this?
			
			if (row < inRow && col > inCol) {

				/*	__ x2 __ __
					__ __ __ __
					__ __ __ x1
					__ __ __ __		*/

				int nextRow = row + 1;
				int nextCol = col - 1;
				int j = 0;
				while (nextRow != inRow && nextCol != inCol) {
					path[j * 2] = nextCol;
					path[j * 2 + 1] = nextRow;
					j++;
					nextRow++;
					nextCol--;
				}
			}
			else if (row < inRow && col < inCol) {		

				/*	__ __ __ x2
					__ __ __ __
					__ x1 __ __
					__ __ __ __		*/
	
				int nextRow = row + 1;
				int nextCol = col + 1;
				int j = 0;
				while (nextRow != inRow && nextCol != inCol) {
					path[j * 2] = nextCol;
					path[j * 2 + 1] = nextRow;
					j++;
					nextRow++;
					nextCol++;
				}
			}
			else if (row > inRow && col < inCol) {

				/*	__ __ __ __
					__ x1 __ __
					__ __ __ __
					__ __ __ x2		*/

				int nextRow = row - 1;
				int nextCol = col + 1;
				int j = 0;
				while (nextRow != inRow && nextCol != inCol) {
					path[j * 2] = nextCol;
					path[j * 2 + 1] = nextRow;
					j++;
					nextRow--;
					nextCol++;
				}
			}
			else if (row > inRow && col > inCol) {			
								
				/*	__ __ __ x1
					__ __ __ __
					__ x2 __ __
					__ __ __ __		*/

				int nextRow = row - 1;
				int nextCol = col - 1;
				int j = 0;
				while (nextRow != inRow && nextCol != inCol) {
					path[j * 2] = nextCol;
					path[j * 2 + 1] = nextRow;
					j++;
					nextRow--;
					nextCol--;
				}
			}
		}

		return path;
	}
	
	


	//		Alternate to the above getPath(), uses helper function
	/*	
	int* Bishop::buildPath(signed int colSign, signed int rowSign, int inCol, int inRow) {

		int* path = new int[2 * MAX_PATH]{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };	// function for this?

		int nextRow = row + rowSign;
		int nextCol = col + colSign;
		int j = 0;
		while (nextRow != inRow && nextCol != inCol) {
			path[j * 2] = nextCol;
			path[j * 2 + 1] = nextRow;
			j++;
			nextRow = nextRow + rowSign;
			nextCol = nextCol + colSign;
		}

		return path;
	}






	int* Bishop::getPath(int inCol, int inRow) const
	{
		int* path = nullptr;

		if (abs(inCol - col) == 1 && abs(inRow - row) == 1)	// moved by only 1 space
			return path;
		else {
			
			if (col > inCol && row < inRow) {
				path = buildPath(-1, 1, inCol, inRow);
			}
			else if (col < inCol && row < inRow) {
				path = buildPath(1, 1, inCol, inRow);
			}
			else if (col < inCol && row > inRow) {
				path = buildPath(1, -1, inCol, inRow);
			}
			else if (col > inCol && row > inRow) {
				path = buildPath(-1, -1, inCol, inRow);				
			}
		}

		return path;
	}
	*/








	//------------------------------Queen-----------------------------------//

	Queen::Queen() : ChessPiece()
	{
		setPieceType(piece_type::queen);
	}






	Queen::Queen(int inCol, int inRow, team_type color) : ChessPiece(inCol, inRow, color)
	{
		setPieceType(piece_type::queen);
	}






	int* Queen::validMove(int inCol, int inRow) const
	{
		static int* path = nullptr;
		int row = getRow();
		int col = getCol();
		ChessPiece::team_type team = getTeamType();

		bool rookMove = ((row == inRow) || (col == inCol));
		bool bishopMove = ((col - inCol) == (row - inRow) || (col - inCol) == -(row - inRow));
		
		if (rookMove) {
			
			//path = Rook::getPath(inCol, inRow);
			Rook tempRook(col, row, team);			// a funky non-ideal work-around;
			path = tempRook.getPath(inCol, inRow);	// rather have friend functions to call
		}											// Rook and Bishop getPath()'s from Queen.
		else if (bishopMove) {

			//path = Bishop::getPath(inCol, inRow);
			Bishop tempBishop(col, row, team);
			path = tempBishop.getPath(inCol, inRow);

		}
		else {
			throw PieceMoveError();
		}

		return path;
	}






	//------------------------------King-----------------------------------//

	King::King()
	{
		setPieceType(piece_type::king);
	}






	King::King(int inCol, int inRow, team_type color)
	{
		setPieceType(piece_type::king);
	}






	// Like the Knight, the "path" for King is irrelevant,
	// as he only moves space by space. Path only concern space between the position 
	// and destination. Nullptr will be returned by default

	int* King::validMove(int inCol, int inRow) const
	{
		int row = getRow();
		int col = getCol();

		if ((inRow <= row + 1) && (inRow >= row - 1) && (inCol <= col + 1) && (inCol >= col - 1)) {
			
		}
		else {
			throw PieceMoveError();
		}

		return  nullptr;
	}






	int* King::getPath(int inCol, int inRow) const
	{
		return nullptr;	// no path for Kings, they only move by 1 space at a time
	}





}	// closes namespace




