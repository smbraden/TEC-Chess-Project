/*/-------------------------------------------------------------------------------------//
	Filename:           WhiteSet.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/

#ifndef WHITESET_H
#define WHITESET_H

#include "ChessPiece.h"

namespace chess {

	class Pawn : public ChessPiece {

	public:

		Pawn(char inCol = 'b', int inRow = 1);
		class PawnMoveError {};
		void setPosition(char& inCol, int& inRow);

	};





	class Rook : public ChessPiece {

	public:

		Rook(char inCol = 'a', int inRow = 1);
		class RookMoveError {};

	};






	class Knight : public ChessPiece {

	public:

		Knight(char inCol = 'a', int inRow = 1);
		class KnightMoveError {};

	};






	class Castle : public ChessPiece {

	public:

		Castle(char inCol = 'b', int inRow = 1);
		class CastleMoveError {};

	};





	class Queen : public ChessPiece {

	public:

		Queen(char inCol = 'b', int inRow = 1);
		class QueenMoveError {};

	};





	class King : public ChessPiece {

	public:

		King(char inCol = 'b', int inRow = 1);
		class KingMoveError {};

	};

} // closes namespace

#endif