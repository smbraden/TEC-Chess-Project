/*/-------------------------------------------------------------------------------------//
	Filename:           DerivedPieces.cpp
	Contributors:       Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/


#include "DerivedPieces.h"
#include <stdlib.h>			// for abs()


namespace chess {


	//------------------------------Pawn-----------------------------------//

	Pawn::Pawn(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = pawn;
		team = color;
	}


	// In progress: How to handle captures by Pawns?
	// Only piece whose range of motion depends on capture vs non-capture moves

	// for now, this only accounts for forward moves by Pawns, not diagonal attackes
	int* Pawn::setPosition(int inCol, int inRow)
	{
		int* path = nullptr;

		if (team == black) {

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 5 && inRow == 3 && col == inCol) || (inRow == (row - 1) && col == inCol)) {
				
				path = getPath(inCol, inRow);
				
				col = inCol;
				row = inRow;
			}
			else {
				throw PieceMoveError();
			}
		}
		else { //  if (team == white)

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 1 && inRow == 3 && col == inCol) || (inRow == row + 1 && col == inCol)) {
				
				path = getPath(inCol, inRow);
				
				col = inCol;
				row = inRow;
			}
			else {
				throw PieceMoveError();
			} // (*)
		}

		return path;
	}



	// for now, this only accounts for forward moves by Pawns, not diagonal attacks
	int* Pawn::getPath(int inCol, int inRow)
	{
		int* path = nullptr;
		int j = 0;
		
		if (abs(inRow - row) == 1) {

			path = new int[MAX_PATH * 2];		// room for 6 coordinates 
												// path[n * 2]  = {c1, r1, c2, r2, c3, r3...cn, rn} 
			if (team == black) {

				path[0] = inCol;
				path[1] = inRow + 1;			// (*) add 1 to the destination row for black pawns 
			}
			else { //  if (team == white)

				path[0] = inCol;
				path[1] = row + 1;			// (*) add 1 to the current row for white pawns 
				
			}

			for (int i = 2; i < (2 * MAX_PATH); i++) {
				path[i] = -1;				// using -1 to signal end of path information
			}								// analogous to null ternimator on a cstring
		}
		
		return path;	// path is nullptr if no spaces between position and destination
	}
	
	
	/* 
		(*) NOTE:  We can use -1 as the "null termiator" without potentially niche 
					negative cooridates complications. We use only adding, and not subtraction, 
					relative to either current position, or destination, as necessary.
					However, the execption hierarchy in ChessBoard::move() should also prevent 
					these conditions by disallowing out of bounds moves. 
	*/






	//------------------------------Castle-----------------------------------//
	
	Castle::Castle(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = castle;
		team = color;
	}



	int* Castle::setPosition(int inCol, int inRow)
	{
		int* path = nullptr;

		// if moving only along columns or rows
		if ((row == inRow) || (col == inCol)) {
			
			path = getPath(inCol, inRow);

			col = inCol;
			row = inRow;
		}
		else {
			throw PieceMoveError();
		}

		return path;
	}


	// **** Refactoring NOTE: This can be condensed with a helper function
	int* Castle::getPath(int inCol, int inRow)
	{
		int* path = nullptr; 

		// path[n * 2]  = {c1, r1, c2, r2, c3, r3...cn, rn} 
		if (abs(inCol - col) > 0 || abs(inRow - row) > 0) {	// if squares traversed

			path = new int[2 * MAX_PATH];
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

			// fill the rest of the spaces with -1, "null terminator"
			do {

				j++;
				path[2 * j] = -1;
				path[2 * j + 1] = -1;

			} while (j < MAX_PATH);


		}
		
		return path;
	}






	//------------------------------Knight-----------------------------------//

	Knight::Knight(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = knight;
		team = color;
	}



	// Although the return "path" for Knights is irrelevant,
	// the rules of inheitance dictate that the return type is the 
	// same as that of the base class for overriden virtual functions.
	// Thus, we will simply return nullptr for all Kight moves, correct or incorrect
	int* Knight::setPosition(int inCol, int inRow)
	{
		bool cond1 = abs(col - inCol) == 2 && abs(row - inRow) == 1; // (1, 0) ---> (0, 2)
		bool cond2 = abs(row - inRow) == 2 && abs(col - inCol) == 1;

		if (cond1 || cond2) {
			
			col = inCol;
			row = inRow;
		}
		else {
			throw PieceMoveError();
		}
		
		col = inCol;
		row = inRow;

		return nullptr;
	}



	int* Knight::getPath(int inCol, int inRow)
	{
		return nullptr;	// no path for knights, they can leap
	}






	//------------------------------Rook-----------------------------------//

	Rook::Rook(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = rook;
		team = color;
	}



	int* Rook::setPosition(int inCol, int inRow)
	{
		int* path = nullptr;

		if ((col - inCol) == (row - inRow) || (col - inCol) == -(row - inRow)) {
			
			path = getPath(inCol, inRow);
			
			col = inCol;
			row = inRow;
		}
		else {
			throw PieceMoveError();
		}

		return path;
	}



	int* Rook::getPath(int inCol, int inRow)
	{
		int* path = nullptr;
		


		return path;
	}






	//------------------------------Queen-----------------------------------//

	Queen::Queen(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = queen;
		team = color;
	}



	int* Queen::setPosition(int inCol, int inRow)
	{
		int* path = nullptr;

		bool castleMove = ((row == inRow) || (col == inCol));
		bool rookMove = ((col - inCol) == (row - inRow) || (col - inCol) == -(row - inRow));
		
		if (castleMove || rookMove) {
			
			path = getPath(inCol, inRow);
			
			col = inCol;
			row = inRow;
		}
		else {
			throw PieceMoveError();
		}

		return path;
	}



	int* Queen::getPath(int inCol, int inRow)
	{
		int* path = new int[2 * MAX_PATH];

		// path[n * 2]  = {c1, r1, c2, r2, c3, r3...cn, rn} 

		// get the path

		return path;
	}






	//------------------------------King-----------------------------------//

	King::King(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = king;
		team = color;
	}


	// Like the Knight, the "path" for King is irrelevant,
	// as he only moves space by space. Path only concern space between the position 
	// and destination. Nullptr will be returned by default

	int* King::setPosition(int inCol, int inRow)
	{
		if ((inRow <= row + 1) && (inRow >= row - 1) && (inCol <= col + 1) && (inCol >= col - 1)) {
			
			col = inCol;
			row = inRow;
		}
		else {
			throw PieceMoveError();
		}

		return  nullptr;
	}



	int* King::getPath(int inCol, int inRow)
	{
		return nullptr;	// no path for Kings, they only move by 1 space at a time
	}

}	// closes namespace




	/*

			int* path = nullptr;
		int j = 0;

		if (team == black) {

			int nextRow = row - 1;			// subtract 1 for black pawns

			while (nextRow != inRow) {

				path[2 * j] = col;
				path[2 * j + 1] = nextRow;
				nextRow--;					// subtract 1 for black pawns

				j++;
			}
		}
		else { //  if (team == white)

			int nextRow = row + 1;			// add 1 for white pawns

			while (nextRow != inRow) {

				path[2 * j] = col;
				path[2 * j + 1] = nextRow;
				nextRow++;					// add 1 for white pawns

				j++;
			}
		}

		do {

			j++;
			path[2 * j] = -1;				// using -1 to signal end of
			path[2 * j + 1] = -1;			// path could be problematic
											// since an incorrect "out of bounds"
		} while (j < MAX_PATH);				// move from black could result in -1,
											// and bounds are checked by ChessBoard,
											// not ChessPiece at this time

		return path;


	*/