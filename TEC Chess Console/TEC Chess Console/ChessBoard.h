/*/-------------------------------------------------------------------------------------//
	Filename:           ChessBoard.h
	Contributor:        Sonja Braden
	Date:               10/16/2020
	Reference:
	Description:        
//-------------------------------------------------------------------------------------/*/


#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "DerivedTeams.h"

namespace chess {

	class ChessBoard {

	public:

		ChessBoard();
		ChessBoard(const ChessBoard&);

		void move(int pos1, int pos2, int move1, int move2);
		void printBoard() const;
		
		// Check status Accessors and Mutators
		ChessPiece::team_type getWinner();
		void setWinner(ChessPiece::team_type arg);

		// Turn Accessors and Mutators
		ChessPiece::team_type getTurn();
		void setTurn(ChessPiece::team_type arg);

		static const int BOARD_SIZE = 8;
		
		class DrawSignal {};
		class WinSignal {};

	private:

		// main data members
		Grid grid;
		ChessPiece::team_type turn;
		ChessPiece::team_type winner;
		History history;
		
		WhiteTeam whiteT;
		BlackTeam blackT;

		void copy(const ChessBoard&);
		void initPieces();

		// Private Grid Element Accessors/Mutators
		ChessPiece* getElement(int col, int row) const;
		void setElement(int col, int row, ChessPiece* ptr);
		ChessPiece::team_type getTeam(int pos1, int pos2) const;
		ChessPiece::piece_type getPiece(int pos1, int pos2) const;
		

	};



} // closes namespace

#endif