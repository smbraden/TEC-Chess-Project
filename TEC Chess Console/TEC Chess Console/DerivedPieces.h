/*/-------------------------------------------------------------------------------------//
	Filename:           DerivedPieces.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/

#ifndef DERIVEDPIECES_H
#define DERIVEDPIECES_H

#include "ChessPiece.h"




namespace chess {

	class Pawn : public ChessPiece {

	public:

		Pawn(int inCol = 0, int inRow = 1, team_type color = white);	// defaults to the left-most white pawn
		class PawnMoveError {};
		int* setPosition(int inCol, int inRow);

	private:

		int* getPath(int inCol, int inRow);

	};






	class Castle : public ChessPiece {

	public:

		Castle(int inCol = 0, int inRow = 0, team_type color = white);  // defaults to left-most white castle
		class CastleMoveError {};
		int* setPosition(int inCol, int inRow);
		friend class Queen;			// for Queen access to getPath()

	private:

		int* getPath(int inCol, int inRow);

	};






	class Knight : public ChessPiece {

	public:

		Knight(int inCol = 1, int inRow = 0, team_type color = white);  // defaults to left-most white knight
		class KnightMoveError {};
		int* setPosition(int inCol, int inRow);

	private:

		int* getPath(int inCol, int inRow);

	};






	class Rook : public ChessPiece {

	public:

		Rook(int inCol = 2, int inRow = 0, team_type color = white); // defaults to left-most white rook
		class RookMoveError {};
		int* setPosition(int inCol, int inRow);
		friend class Queen;		// for Queen access to getPath()

	private:

		int* getPath(int inCol, int inRow);

	};






	class Queen : public ChessPiece {

	public:

		Queen(int inCol = 3, int inRow = 0, team_type color = white);  // defaults to white queen
		class QueenMoveError {};
		int* setPosition(int inCol, int inRow);

	private:

		//int* getPath(int inCol, int inRow);

	};






	class King : public ChessPiece {

	public:

		King(int inCol = 4, int inRow = 0, team_type color = white);	// defaults to white king
		class KingMoveError {};
		int* setPosition(int inCol, int inRow);

	private:

		int* getPath(int inCol, int inRow);

	};

} // closes namespace

#endif