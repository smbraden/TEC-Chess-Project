/*/-------------------------------------------------------------------------------------//
	Filename:           ChessPiece.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:		Implementation  of the ChessPiece class. This is the base
						class from which unique types of pieces are derived 
						(queen, king, etc.) Unique types have different error checking 
						for valid movement.
//-------------------------------------------------------------------------------------/*/


#include "ChessPiece.h"

//using namespace std;

namespace chess {
	
	
	ChessPiece::ChessPiece(int inCol, int inRow,team_type color)
	{
		row = inRow;
		col = inCol;
		piece = none;
		team = color;
	}






	void ChessPiece::getPosition(int& inCol, int& inRow) const
	{
		inRow = row;
		inCol = col;

	}






	char ChessPiece::getPieceType() const
	{
		return piece;
	}






	char ChessPiece::getTeamType() const
	{
		return team;
	}






	void ChessPiece::setPosition(int inCol, int inRow)
	{
		/*	Pseudocode:
		
		if (inRow invalid move || inCol invalid move) {
			throw PieceMoveError();
		}
		else {
			col = inCol;
			row = inRow;
		}
		*/
	}

}  // closes namespace

