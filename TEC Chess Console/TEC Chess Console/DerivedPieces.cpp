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

	Pawn::Pawn(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = pawn;
		team = color;
	}

	void Pawn::setPosition(int inCol, int inRow)
	{
		
		if (team == black) {

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 5 && inRow == 3 && col == inCol) || (inRow == (row - 1) && col == inCol)) {
				col = inCol;
				row = inRow;
			}
			else {
				throw PieceMoveError();
			}
		}
		else if (team == white) {

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 1 && inRow == 3 && col == inCol) || (inRow == row + 1 && col == inCol)) {
				col = inCol;
				row = inRow;
			}
			else {
				throw PieceMoveError();
			}
		}
	}







	
	Castle::Castle(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = castle;
		team = color;
	}

	void Castle::setPosition(int inCol, int inRow)
	{

		// if moving only along columns or rows
		if ((row == inRow) || (col == inCol)) {
			col = inCol;
			row = inRow;
		}
		else {
			throw PieceMoveError();
		}
	}






	Knight::Knight(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = knight;
		team = color;
	}

	void Knight::setPosition(int inCol, int inRow)
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

	}







	Rook::Rook(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = rook;
		team = color;
	}

	void Rook::setPosition(int inCol, int inRow)
	{


		if ((col - inCol) == (row - inRow) || (col - inCol) == -(row - inRow)) {
			col = inCol;
			row = inRow;
		}
		else {
			throw PieceMoveError();
		}

	}






	Queen::Queen(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = queen;
		team = color;
	}

	void Queen::setPosition(int inCol, int inRow)
	{

		bool castleMove = ((row == inRow) || (col == inCol));
		bool rookMove = ((col - inCol) == (row - inRow) || (col - inCol) == -(row - inRow));
		if (castleMove || rookMove) {
			col = inCol;
			row = inRow;
		}
		else {
			throw PieceMoveError();
		}
	}






	King::King(int inCol, int inRow, team_type color)
	{
		col = inCol;
		row = inRow;
		piece = king;
		team = color;
	}

	void King::setPosition(int inCol, int inRow)
	{

		if ((inRow <= row + 1) && (inRow >= row - 1) && (inCol <= col + 1) && (inCol >= col - 1)) {
			col = inCol;
			row = inRow;
		}
		else {
			throw PieceMoveError();
		}
	}
}
