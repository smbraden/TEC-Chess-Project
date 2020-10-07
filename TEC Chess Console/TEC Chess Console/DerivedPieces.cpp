/*/-------------------------------------------------------------------------------------//
	Filename:           DerivedPieces.cpp
	Contributors:       Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/


#include "DerivedPieces.h"



namespace chess {


	//------------------------------Pawn-----------------------------------//

	Pawn::Pawn(int inCol, int inRow, team_type color)
	{
		assert((inCol < BOARD_SIZE) && (inRow < BOARD_SIZE) && (inCol >= 0) && (inRow >= 0));
		col = inCol;
		row = inRow;
		piece = piece_type::pawn;
		team = color;
	}


	// Precondition:	the potential validity of the move with respect to 
	//					other pieces on the board has been evaluated and confirmed.
	//					(ie pieces blocking the pawn vs pieces captured by the pawn)
	int* Pawn::validMove(int inCol, int inRow) const
	{
		int* path = nullptr;

		if (team == team_type::black) {

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 6 && inRow == 4 && col == inCol) || (inRow == (row - 1) && col == inCol)) {
				if (row == 6 && inRow == 4 && col == inCol)
					path = getPath(inCol, inRow);	// only need path if moved two spaces
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
				if (row == 1 && inRow == 3 && col == inCol)
					path = getPath(inCol, inRow);	// only need path if moved two spaces
			}
			else if (inRow == row + 1 && abs(col - inCol) == 1) {	// diagonal capture, no path

			}
			else {
				throw PieceMoveError();
			} // (*)
		}

		return path; // could be condensed, but with lengthy, less-readable condition statements
	}









	// Precondition:	the move was a 2-space advance from the initial row
	int* Pawn::getPath(int inCol, int inRow) const
	{
		int* path = nullptr;
		
		if (abs(inRow - row) == 2) {

			path = new int[2 * MAX_PATH]{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
			path[0] = inCol;
			path[1] = (team == team_type::black ? inRow + 1 : row + 1);
			
		}
		return path;	// path is nullptr if no spaces between position and destination
	}
	
	/*
	
	if (team == team_type::black)
		path[1] = inRow + 1;
	else
		path[1] = row + 1;
	
	*/


	
	/* 
		(*) NOTE:  We can use -1 as the "null termiator" without potentially niche 
					negative cooridates complications. We use only adding, and not subtraction, 
					relative to either current position, or destination, as necessary.
					However, the execption hierarchy in ChessBoard::move() should also prevent 
					these conditions by disallowing out of bounds moves. 
	*/






	//------------------------------Rook-----------------------------------//
	
	Rook::Rook(int inCol, int inRow, team_type color)
	{
		assert((inCol < BOARD_SIZE) && (inRow < BOARD_SIZE) && (inCol >= 0) && (inRow >= 0));
		col = inCol;
		row = inRow;
		piece = piece_type::rook;
		team = color;
	}



	int* Rook::validMove(int inCol, int inRow) const
	{
		int* path = nullptr;

		// if moving only along columns or rows
		if ((row == inRow) || (col == inCol)) {
			
			path = getPath(inCol, inRow);

		}
		else {
			throw PieceMoveError();
		}

		return path;
	}



	int* Rook::getPath(int inCol, int inRow) const
	{
		int* path = nullptr; 

		if (abs(inCol - col) > 0 || abs(inRow - row) > 0) {	// if squares traversed

			path = new int[2 * MAX_PATH]{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
			int j = 0;
			
			if (col == inCol) {

				int nextRow = 0;

				if (row > inRow) {

					nextRow = inRow + 1;
					while (nextRow != row) {

						path[2 * j] = col;
						path[2 * j + 1] = nextRow;
						nextRow++;					
						j++;
					}
				}
				else {	// if row < inRow

					nextRow = row + 1;
					while (nextRow != inRow) {

						path[2 * j] = col;
						path[2 * j + 1] = nextRow;
						nextRow++;					
						j++;
					}
				}
			}
			else if (row == inRow) {

				int nextCol = 0;

				if (col > inCol) {

					nextCol = inCol + 1;
					while (nextCol != col) {

						path[2 * j] = col;
						path[2 * j + 1] = nextCol;
						nextCol++;					
						j++;
					}
				}
				else {	// if col < inCol

					nextCol = col + 1;
					while (nextCol != inCol) {

						path[2 * j] = col;
						path[2 * j + 1] = nextCol;
						nextCol++;					
						j++;
					}
				}
			}
		}
		
		return path;
	}






	//------------------------------Knight-----------------------------------//

	Knight::Knight(int inCol, int inRow, team_type color)
	{
		assert((inCol < BOARD_SIZE) && (inRow < BOARD_SIZE) && (inCol >= 0) && (inRow >= 0));
		col = inCol;
		row = inRow;
		piece = piece_type::knight;
		team = color;
	}



	// Although the return "path" for Knights is irrelevant,
	// the rules of inheitance dictate that the return type is the 
	// same as that of the base class for overriden virtual functions.
	// Thus, we will simply return nullptr for all Kight moves, correct or incorrect
	int* Knight::validMove(int inCol, int inRow) const
	{
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

	Bishop::Bishop(int inCol, int inRow, team_type color)
	{
		assert((inCol < BOARD_SIZE) && (inRow < BOARD_SIZE) && (inCol >= 0) && (inRow >= 0));
		col = inCol;
		row = inRow;
		piece = piece_type::bishop;
		team = color;
	}



	int* Bishop::validMove(int inCol, int inRow) const
	{
		int* path = nullptr;

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






	//------------------------------Queen-----------------------------------//

	Queen::Queen(int inCol, int inRow, team_type color)
	{
		assert((inCol < BOARD_SIZE) && (inRow < BOARD_SIZE) && (inCol >= 0) && (inRow >= 0));
		col = inCol;
		row = inRow;
		piece = piece_type::queen;
		team = color;
	}



	int* Queen::validMove(int inCol, int inRow) const
	{
		static int* path = nullptr;

		bool rookMove = ((row == inRow) || (col == inCol));
		bool bishopMove = ((col - inCol) == (row - inRow) || (col - inCol) == -(row - inRow));
		
		if (rookMove) {
			
			Rook tempRook(col, row, team);			// a funky non-ideal work-around;
			path = tempRook.getPath(inCol, inRow);	// rather have friend functions to call
		}											// Rook and Bishop getPath()'s from Queen.
		else if (bishopMove) {

			Bishop tempBishop(col, row, team);
			path = tempBishop.getPath(inCol, inRow);

		}
		else {
			throw PieceMoveError();
		}

		return path;
	}






	//------------------------------King-----------------------------------//

	King::King(int inCol, int inRow, team_type color)
	{
		assert((inCol < BOARD_SIZE) && (inRow < BOARD_SIZE) && (inCol >= 0) && (inRow >= 0));
		col = inCol;
		row = inRow;
		piece = piece_type::king;
		team = color;
	}


	// Like the Knight, the "path" for King is irrelevant,
	// as he only moves space by space. Path only concern space between the position 
	// and destination. Nullptr will be returned by default

	int* King::validMove(int inCol, int inRow) const
	{
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




