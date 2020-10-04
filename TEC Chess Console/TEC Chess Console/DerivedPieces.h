/*/-------------------------------------------------------------------------------------//
	Filename:           DerivedPieces.h
	Contributor:        Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/

#ifndef DERIVEDPIECES_H
#define DERIVEDPIECES_H

#include "ChessPiece.h"




namespace chess {

	class Pawn : public ChessPiece {

	public:

		Pawn(int inCol = 0, int inRow = 1, team_type color = team_type::white);	// defaults to the left-most white pawn
		class PawnMoveError {};
		int* setPosition(int inCol, int inRow);

	private:

		int* getPath(int inCol, int inRow) const;
		// 6 possible coordinates, and -1 signals end of coordinates

		/*	path[2 * MAX_PATH] = {c1, r1, c2, r2, c3, r3...c6, r6}
			path[n * 2]			= {c1, c2, c3,...cn,}
			path[n * 2 + 1]		= {r1, r2, r3,...rn,}	*/

	};






	class Rook : public ChessPiece {

	public:

		Rook(int inCol = 0, int inRow = 0, team_type color = team_type::white);  // defaults to left-most white castle
		class RookMoveError {};
		int* setPosition(int inCol, int inRow);
		friend class Queen;			// for Queen access to getPath()

	private:

		int* getPath(int inCol, int inRow) const;

	};






	class Knight : public ChessPiece {

	public:

		Knight(int inCol = 1, int inRow = 0, team_type color = team_type::white);  // defaults to left-most white knight
		class KnightMoveError {};
		int* setPosition(int inCol, int inRow);

	private:

		int* getPath(int inCol, int inRow) const;

	};






	class Bishop : public ChessPiece {

	public:

		Bishop(int inCol = 2, int inRow = 0, team_type color = team_type::white); // defaults to left-most white rook
		class BishopMoveError {};
		int* setPosition(int inCol, int inRow);
		friend class Queen;		// for Queen access to getPath()

	private:

		int* getPath(int inCol, int inRow) const;

	};






	class Queen : public ChessPiece {

	public:

		Queen(int inCol = 3, int inRow = 0, team_type color = team_type::white);  // defaults to white queen
		class QueenMoveError {};
		int* setPosition(int inCol, int inRow);

	private:

		//int* getPath(int inCol, int inRow) const;

	};






	class King : public ChessPiece {

	public:

		King(int inCol = 4, int inRow = 0, team_type color = team_type::white);	// defaults to white king
		class KingMoveError {};
		int* setPosition(int inCol, int inRow);

	private:

		int* getPath(int inCol, int inRow) const;

	};

} // closes namespace

#endif