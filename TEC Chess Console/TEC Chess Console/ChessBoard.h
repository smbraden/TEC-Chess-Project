/*/-------------------------------------------------------------------------------------//
	Filename:           ChessBoard.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:        Annoyingly, I have index the Board coordinates as [Column][Row],
						as this is how a chess board is labeled 
						(eg, a1, a2, b5, etc. where letters are columns ).
//-------------------------------------------------------------------------------------/*/


#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include  "DerivedPieces.h"

namespace chess {

	class ChessBoard {

	public:

		ChessBoard();
		ChessBoard(const ChessBoard&);
		~ChessBoard();
		ChessBoard operator=(const ChessBoard&);

		void moveWhite(int pos1, int pos2, int move1, int move2); // indices 0-7 
		void moveBlack(int pos1, int pos2, int move1, int move2); // (col ,row)
		ChessPiece::team_type getTeam(int pos1, int pos2) const;
		ChessPiece::piece_type getPiece(int pos1, int pos2) const;
		void printBoard() const;
		bool blackCheck();
		bool whiteCheck();

		class SelfCapturError {};	// moving a piece to a position already occupied by that team
		class NoTurnPassError {};	// Equivalent to moving a piece to it's current position
		class TurnMoveError {};		// when a player attempts to move the opponent's piece
		class BoundsError {};		// for moves that go out of board bounds
		class EmptySquareError {};	// Attempt to move an empty square
		class IndirectPathError {};	// For attempts to jump over other pieces if not knight 
		class IlegalMoveError {};	// any other illegal moves
		class CheckError {};		// if King in Check, must escape the check

		const int MAX_PATH = 7; // 6 spaces for max path, and 1 more for an extra delimiter
		static const int BOARD_SIZE = 8;
		const int SPACES = 64;

	private:

		// main data members
		ChessPiece* grid[BOARD_SIZE][BOARD_SIZE];
		int wKingRow;
		int wKingCol;
		int bKingRow;
		int bKingCol;

		// helper functions
		void initPieces();
		void evaluatePath(int* path) const;
		void move(int pos1, int pos2, int move1, int move2, ChessPiece::team_type inTeam);
		void remove(int x, int y);
		void setPiece(int pos1, int pos2, int move1, int move2);
		void clear();
		void copy(const ChessBoard&);
		bool isPiece(int inCol, int inRow) const;
		int* validPawnMove(int pos1, int pos2, int move1, int move2) const;

		// Pawn-related functions
		bool isCapture(int pos1, int pos2, int move1, int move2) const;
		bool simpleAdvance(int pos1, int pos2, int move1, int move2) const;
		bool isEnPassant(int pos1, int pos2, int move1, int move2) const;
		void pawnPromote(int pos1, int pos2, int move1, int move2);
		void resetEnPassant(int pos1, int pos2);

		// King-related functions
		bool isCastle(int pos1, int pos2, int move1, int move2);
		void setKing(int pos1, int pos2, int move1, int move2);

		// determines if the given position and suit places a king in check
		void isCheck(ChessPiece::team_type team) const;

		// isCheck() helper functions
		bool checkLaterals(ChessPiece::team_type kingTeam, int kCol, int kRow) const;
		bool singleLateral(ChessPiece::team_type kingTeam, int kCol, int kRow, int colSign, int rowSign) const;
		bool checkCorners(ChessPiece::team_type kingTeam, int kCol, int kRow) const;
		bool checkDiagonals(ChessPiece::team_type kingTeam, int kCol, int kRow) const;
		bool singleDiagonal(ChessPiece::team_type kingTeam, int kCol, int kRow, int colSign, int rowSign) const;
		bool checkKnight(ChessPiece::team_type kingTeam, int kCol, int kRow) const;
		bool singleKnight(ChessPiece::team_type kingTeam,int kCol, int kRow, int colSign, int rowSign) const;
		
	};



} // closes namespace

#endif