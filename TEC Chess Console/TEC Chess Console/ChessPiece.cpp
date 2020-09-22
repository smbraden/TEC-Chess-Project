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
	
	/*
	ChessPiece::ChessPiece()
	{
		row = 0;
		col = 0;
		piece_type = 'P';
		team_type = 'w';
	}
	*/
	ChessPiece::ChessPiece(int inCol, int inRow,char color)
	{
		row = inRow;
		col = inCol;
		piece_type = '0';
		team_type = color;
	}






	void ChessPiece::getPosition(int& inCol, int& inRow) const
	{
		inRow = row;
		inCol = col;

	}






	char ChessPiece::getPieceType() const
	{
		return piece_type;
	}






	char ChessPiece::getTeamType() const
	{
		return team_type;
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

