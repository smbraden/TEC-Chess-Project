/*/-------------------------------------------------------------------------------------//
	Filename:           DerivedPieces.cpp
	Contributors:        Sonja Braden
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
			}
		}

		return path;
	}



	int* Pawn::getPath(int inCol, int inRow)
	{
		int* path = nullptr;
		
		if (row == 5 || row == 1) {
			
			path = new int[2 * MAX_PATH];
			path[0] = inCol;

			if (team == black)
				path[1] = inRow - 1;	// minus 1 row for black pawn moves
			else  
				path[1] = inRow + 1;	// plus 1 row for white pawn moves
		}

		return path;
	}






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



	int* Castle::getPath(int inCol, int inRow)
	{
		int* path = new int[2 * MAX_PATH];

		// path[n * 2]  = {c1, r1, c2, r2, c3, r3...cn, rn} 
		
		// get the path
		
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
		int* path = new int[2 * MAX_PATH];

		// path[n * 2]  = {c1, r1, c2, r2, c3, r3...cn, rn} 

		// get the path

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
