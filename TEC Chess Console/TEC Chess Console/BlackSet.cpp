/*/-------------------------------------------------------------------------------------//
	Filename:           BlackSet.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:		
//-------------------------------------------------------------------------------------/*/


#include "BlackSet.h"

namespace chess {

	Pawn::Pawn(char inCol, int inRow)
	{
		ChessPiece();
	}

	void Pawn::setPosition(char inCol, int inRow, team_type team)
	{
		if (team == black) {

			// if starting row and move two rows forward, or move one row forward 
			if ((row == 5 && inRow == 7 && col == inCol) || (inRow == row - 1 && col == inCol)) {
				col = inCol;
				row = inRow;
			}
			else {
				throw PawnMoveError();
			}
		}
		else if (team == white) {

			// if starting row and move two rows forward, or move one row forward 
			if ((row == 2 && inRow == 4 && col == inCol) || (inRow == row + 1 && col == inCol)) {
				col = inCol;
				row = inRow;
			}
			else {
				throw PawnMoveError();
			}
		}
	}







	Rook::Rook(char inCol, int inRow)
	{
		ChessPiece();
	}

	void Rook::setPosition(char inCol, int inRow)
	{

		/*
		if (valid Rook move) {
			col = inCol;
			row = inRow;
		}
		else {
			throw RookMoveError();
		}
		*/
	}






	Knight::Knight(char inCol, int inRow)
	{
		ChessPiece();
	}

	void Knight::setPosition(char inCol, int inRow)
	{

		/*
		if (valid Knight move) {
			col = inCol;
			row = inRow;
		}
		else {
			throw KnightMoveError();
		}
		*/
	}






	Castle::Castle(char inCol, int inRow)
	{
		ChessPiece();
	}

	void Castle::setPosition(char inCol, int inRow)
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






	Queen::Queen(char inCol, int inRow)
	{
		ChessPiece();
	}

	void Queen::setPosition(char inCol, int inRow)
	{

		/*
		if (invalid Queen move) {
			col = inCol;
			row = inRow;
		}
		else {
			throw QueenMoveError();
		}
		*/
	}






	King::King(char inCol, int inRow)
	{
		ChessPiece();
	}

	void King::setPosition(char inCol, int inRow)
	{

		/*
		if (valid Knight move) {
			col = inCol;
			row = inRow;
		}
		else {
			throw KingMoveError();
		}
		*/
	}
}
