/*/-------------------------------------------------------------------------------------//
	Filename:           DerivedPieces.cpp
	Contributors:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/


#include "DerivedPieces.h"

namespace chess {

	Pawn::Pawn(int inCol, int inRow, char color)
	{
		col = inCol;
		row = inRow;
		piece_type = 'P';
		team_type = color;
	}

	void Pawn::setPosition(int inCol, int inRow)
	{
		
		if (team_type == 'b') {

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 5 && inRow == 3 && col == inCol) || (inRow == (row - 1) && col == inCol)) {
				col = inCol;
				row = inRow;
			}
			else {
				throw PawnMoveError();
			}
		}
		else if (team_type == 'w') {

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 1 && inRow == 3 && col == inCol) || (inRow == row + 1 && col == inCol)) {
				col = inCol;
				row = inRow;
			}
			else {
				throw PawnMoveError();
			}
		}
	}







	Rook::Rook(int inCol, int inRow, char color)
	{
		col = inCol;
		row = inRow;
		piece_type = 'R';
		team_type = color;
	}

	void Rook::setPosition(int inCol, int inRow)
	{

		
		if ((col - inCol) == (row - inRow) || (col - inCol) == -(row - inRow)) {
			col = inCol;
			row = inRow;
		}
		else {
			throw RookMoveError();
		}
		
	}






	Knight::Knight(int inCol, int inRow, char color)
	{
		col = inCol;
		row = inRow;
		piece_type = 'N';
		team_type = color;
	}

	void Knight::setPosition(int inCol, int inRow)
	{
		/*
		if (valid knight move) {
			col = inCol;
			row = inRow;
		}
		else {
			throw KnightMoveError();
		}
		*/

		col = inCol;
		row = inRow;

	}






	Castle::Castle(int inCol, int inRow, char color)
	{
		col = inCol;
		row = inRow;
		piece_type = 'C';
		team_type = color;
	}

	void Castle::setPosition(int inCol, int inRow)
	{

		// if moving only along columns or rows
		if ((row == inRow) || (col == inCol)) {
			col = inCol;
			row = inRow;
		}
		else {
			throw CastleMoveError();
		}
	}






	Queen::Queen(int inCol, int inRow, char color)
	{
		col = inCol;
		row = inRow;
		piece_type = 'Q';
		team_type = color;
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
			throw QueenMoveError();
		}
	}






	King::King(int inCol, int inRow, char color)
	{
		col = inCol;
		row = inRow;
		piece_type = 'K';
		team_type = color;
	}

	void King::setPosition(int inCol, int inRow)
	{

		if ((inRow <= row + 1) && (inRow >= row - 1) && (inCol <= col + 1) && (inCol >= col - 1)) {
			col = inCol;
			row = inRow;
		}
		else {
			throw KingMoveError();
		}
	}
}
