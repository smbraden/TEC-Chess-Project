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
		Pawn(int inCol, int inRow, team_type color, bool passVal);
		class PawnMoveError {};
		int* validMove(int inCol, int inRow) const;	// no "const" for Pawns b/c need to setEnPassant()  
		void setEnPassant(bool);
		bool getEnPassant() const;


	protected:

		bool enPassant;
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






	class Queen : public ChessPiece {

	public:

		Queen();
		Queen(int inCol, int inRow, team_type color);
		class QueenMoveError {};
		int* validMove(int inCol, int inRow) const;

	protected:	// for Rook and Bishop access to these getPath()'s

		int* getLateralPath(int inCol, int inRow) const;
		int* getDiagonalPath(int inCol, int inRow) const;
		int* buildPath(signed int colSign, signed int rowSign, int inCol, int inRow) const; // getDiagonalPath() helper function
	};






	class Bishop : public Queen {

	public:
		Bishop();
		Bishop(int inCol, int inRow, team_type color);
		class BishopMoveError {};
		int* validMove(int inCol, int inRow) const;
		
	private:

		int* getPath(int inCol, int inRow) const;
		
	};






	class Rook : public Queen {

	public:

		Rook();
		Rook(int inCol, int inRow, team_type color);
		class RookMoveError {};
		int* validMove(int inCol, int inRow) const;

	private:

		int* getPath(int inCol, int inRow) const;

	};







	class King : public ChessPiece {

	public:

		King();
		King(int inCol, int inRow, team_type color);
		class KingMoveError {};
		int* validMove(int inCol, int inRow) const;
		bool getCastleStatus();
		void setCastleStatus(bool arg);
		bool getCheckStatus();
		void setCheckStatus(bool arg);
		bool getMateStatus();
		void setMateStatus(bool arg);

	private:

		bool castle;	// true as long as king has never moved yet
		bool check;
		bool checkMate;
		int* getPath(int inCol, int inRow) const;
		
	};

} // closes namespace

#endif