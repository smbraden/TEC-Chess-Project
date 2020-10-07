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
		
		Pawn();
		Pawn(int inCol, int inRow, team_type color);
		class PawnMoveError {};
		int* validMove(int inCol, int inRow) const;
		friend bool getPassantState();
		friend void setPassantState(bool);

	private:

		bool enPassant;
		int* getPath(int inCol, int inRow) const;
		
	};






	class Rook : public ChessPiece {

	public:

		Rook();
		Rook(int inCol, int inRow, team_type color);
		class RookMoveError {};
		int* validMove(int inCol, int inRow) const;
		
		friend class Queen;			// for Queen access to getPath()

	private:

		int* getPath(int inCol, int inRow) const;
		
	};






	class Knight : public ChessPiece {

	public:

		Knight();
		Knight(int inCol, int inRow, team_type color);
		class KnightMoveError {};
		int* validMove(int inCol, int inRow) const;
		
	private:

		int* getPath(int inCol, int inRow) const;
		
	};






	class Bishop : public ChessPiece {

	public:
		Bishop();
		Bishop(int inCol, int inRow, team_type color);
		class BishopMoveError {};
		int* validMove(int inCol, int inRow) const;
		friend class Queen;		// for Queen access to getPath()
		
	private:

		int* getPath(int inCol, int inRow) const;
		//int* buildPath(signed int colSign, signed int rowSign, int inCol, int inRow);

	};






	class Queen : public ChessPiece {

	public:

		Queen();
		Queen(int inCol, int inRow, team_type color);
		class QueenMoveError {};
		int* validMove(int inCol, int inRow) const;
		
	private:

		//int* getPath(int inCol, int inRow) const;
		
	};






	class King : public ChessPiece {

	public:

		King();
		King(int inCol, int inRow, team_type color);
		class KingMoveError {};
		int* validMove(int inCol, int inRow) const;
		
	private:

		int* getPath(int inCol, int inRow) const;
		
	};

} // closes namespace

#endif