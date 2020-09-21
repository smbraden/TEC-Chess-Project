/*/-------------------------------------------------------------------------------------//
	Filename:           BlackSet.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:		
//-------------------------------------------------------------------------------------/*/

#ifndef BLACKSET_H
#define BLACKSET_H

#include "ChessPiece.h"

namespace chess {

	class Pawn : public ChessPiece {

	public:

		Pawn(char inCol = 'b', int inRow = 1);
		class PawnMoveError {};
		void setPosition(char inCol, int inRow, team_type team);

	};





	class Rook : public ChessPiece {

	public:

		Rook(char inCol = 'a', int inRow = 1);
		class RookMoveError {};
		void setPosition(char inCol, int inRow);

	};






	class Knight : public ChessPiece {

	public:

		Knight(char inCol = 'a', int inRow = 1);
		class KnightMoveError {};
		void setPosition(char inCol, int inRow);

	};






	class Castle : public ChessPiece {

	public:

		Castle(char inCol = 'b', int inRow = 1);
		class CastleMoveError {};
		void setPosition(char inCol, int inRow);

	};





	class Queen : public ChessPiece {

	public:

		Queen(char inCol = 'b', int inRow = 1);
		class QueenMoveError {};
		void setPosition(char inCol, int inRow);

	};





	class King : public ChessPiece {

	public:

		King(char inCol = 'b', int inRow = 1);
		class KingMoveError {};
		void setPosition(char inCol, int inRow);

	};

} // closes namespace

#endif