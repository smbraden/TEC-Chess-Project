/*/-------------------------------------------------------------------------------------//
	Filename:           WhiteSet.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:		
//-------------------------------------------------------------------------------------/*/


#include "WhiteSet.h"

namespace chess {

	Pawn::Pawn(char inCol, int inRow)
	{
		ChessPiece();
	}

	void Pawn::setPosition(char& inCol, int& inRow)
	{
		
		if ((row == 2 && inRow == 4 && col == inCol) || (inRow == row + 1 && col == inCol)) {
			col = inCol;
			row = inRow;
		}
		else
			throw PawnMoveError();
	}

	Rook::Rook(char inCol, int inRow)
	{
		ChessPiece();
	}

	Knight::Knight(char inCol, int inRow)
	{
		ChessPiece();
	}

	Castle::Castle(char inCol, int inRow)
	{
		ChessPiece();
	}

	Queen::Queen(char inCol, int inRow)
	{
		ChessPiece();
	}

	King::King(char inCol, int inRow)
	{
		ChessPiece();
	}

}
