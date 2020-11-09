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
		int* validMove(int inCol, int inRow) const;
		void setEnPassant(bool);
		bool getEnPassant() const;
		int* getTrapSet() const;

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
		int* getTrapSet() const;

	private:

		int* getPath(int inCol, int inRow) const;

	};






	class Queen : public ChessPiece {

	public:

		Queen();
		Queen(int inCol, int inRow, team_type color);
		class QueenMoveError {};
		int* validMove(int inCol, int inRow) const;
		int* getTrapSet() const;

	protected:	// for Rook and Bishop access to these getPath()'s

		int* getLateralPath(int inCol, int inRow) const;
		int* getDiagonalPath(int inCol, int inRow) const;
		// helper function to getDiagonalPath() 
		int* buildPath(signed int colSign, signed int rowSign, int inCol, int inRow) const;
	};






	class Bishop : public Queen {

	public:
		Bishop();
		Bishop(int inCol, int inRow, team_type color);
		class BishopMoveError {};
		int* validMove(int inCol, int inRow) const;
		int* getTrapSet() const;

	private:

		int* getPath(int inCol, int inRow) const;
		
	};






	class Rook : public Queen {

	public:

		Rook();
		Rook(int inCol, int inRow, team_type color, bool c);
		class RookMoveError {};
		int* validMove(int inCol, int inRow) const;
		int* getTrapSet() const;
		bool getCastleStatus();
		void setCastleStatus(bool arg);

	private:

		bool castle;	// true as long as rook  has never moved yet
		int* getPath(int inCol, int inRow) const;

	};







	class King : public ChessPiece {

	public:

		King();
		King(int inCol, int inRow, team_type color, bool c);
		class KingMoveError {};
		int* validMove(int inCol, int inRow) const;
		int* getTrapSet() const;
		bool getCastleStatus();
		void setCastleStatus(bool arg);
		
	private:

		bool castle;	// true as long as king has never moved yet
		int* getPath(int inCol, int inRow) const;
		
	};

} // closes namespace

#endif