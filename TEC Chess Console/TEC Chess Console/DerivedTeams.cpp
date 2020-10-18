/*/-------------------------------------------------------------------------------------//
	Filename:           DerivedTeams.cpp
	Contributor:        Sonja Braden
	Date:               10/18/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/

#include "DerivedTeams.h"

#define inBounds2(a, b) (a < BOARD_SIZE && b < BOARD_SIZE && a >= 0 && b >= 0 )
#define inBounds4(a, b, c, d) (a >= 0 && b >= 0 && c >= 0 && d >= 0 &&  \
                            a < BOARD_SIZE&& b < BOARD_SIZE&& c < BOARD_SIZE&& d < BOARD_SIZE)


namespace chess {

	WhiteTeam::WhiteTeam()
	{
		kCol = 4;
		kRow = 0;
		team = ChessPiece::team_type::white;
		gridPtr = nullptr;
		checkmateStatus = false;
	}






	WhiteTeam::WhiteTeam(Grid* g, bool m)
	{
		kCol = 4;
		kRow = 0;
		team = ChessPiece::team_type::white;
		gridPtr = g;
		checkmateStatus = m;
	}






	bool WhiteTeam::isCapture(int pos1, int pos2, int move1, int move2) const
	{
		/* if opponent occupies destination */
		if (isPiece(move1, move2) && getTeam(move1, move2) != getTeam(pos1, pos2) &&
										move2 == pos2 + 1 && abs(pos1 - move1) == 1) {
			return true;
		}
		return false;
	}






	bool WhiteTeam::isEnPassant(int pos1, int pos2, int move1, int move2) const
	{
		assert(inBounds4(pos1, pos2, move1, move2));

		if (isPiece(pos1, pos2) && getPiece(pos1, pos2) != ChessPiece::piece_type::pawn) {
			return false;
		}
		
		if (pos2 != 4 || move2 != 5)    // if current position is not fifth rank
			return false;               // and moving to the proper row
		// if either of the objects to the left or right has enPassant == true
		else if (move1 == (pos1 - 1) && isPiece(pos1 - 1, pos2) 
				&& ((Pawn*)getElement(pos1 - 1, pos2))->getEnPassant())
			return true;
		else if (move1 == (pos1 + 1) && isPiece(pos1 + 1, pos2) 
				&& ((Pawn*)getElement(pos1 + 1, pos2))->getEnPassant())
			return true;
		
		return false;
	}






	void WhiteTeam::pawnPromote(int pos1, int pos2, int move1, int move2)
	{
		assert(inBounds4(pos1, pos2, move1, move2));
		ChessPiece::team_type team = getTeam(pos1, pos2);

		if (isPiece(pos1, pos2) && getPiece(pos1, pos2) == ChessPiece::piece_type::pawn 
																			&& move2 == 7) {
			
			// later, promote with options HERE
			Queen* qPtr = new Queen(pos1, pos2, team);
			remove(pos1, pos2);
			setElement(pos1, pos2, qPtr);
		}
	}






	bool WhiteTeam::Castle(int pos1, int pos2, int move1, int move2)
	{
		assert(isPiece(pos1, pos2));

		// confirm the basic conditions
		if (getPiece(pos1, pos2) != ChessPiece::piece_type::king || 
				!((King*)getElement(pos1, pos2))->getCastleStatus() || isCheck())
			return false;

		if (move1 == 2 && move2 == 0) {
			if (isPiece(0, 0) && getPiece(0, 0) == ChessPiece::piece_type::rook 
									&& ((Rook*)getElement(0, 0))->getCastleStatus()) {
				if (validCastlePath(4, 0, 0, 0)) {
					((Rook*)getElement(0, 0))->setCastleStatus(false);
					((King*)getElement(4, 0))->setCastleStatus(false);
					setPiece(0, 0, 3, 0);
					return true;
				}
			}
		}
		else if (move1 == 6 && move2 == 0) {
			if (isPiece(7, 0) && getPiece(7, 0) == ChessPiece::piece_type::rook 
									&& ((Rook*)getElement(7, 0))->getCastleStatus()) {
				if (validCastlePath(4, 0, 7, 0)) {
					((Rook*)getElement(7, 0))->setCastleStatus(false);
					((King*)getElement(4, 0))->setCastleStatus(false);
					setPiece(7, 0, 5, 0);
					return true;
				}
			}
		}
		
		return false;
	}






	bool WhiteTeam::checkCorners(int kCol, int kRow) const
	{
		int left = kCol - 1;
		int right = kCol + 1;
		int pRow = kRow + 1;

		if ((isPiece(right, pRow) && getTeam(right, pRow) != team
			&& getPiece(right, pRow) == ChessPiece::piece_type::pawn) ||
			(isPiece(left, pRow) && getTeam(left, pRow) != team
				&& getPiece(left, pRow) == ChessPiece::piece_type::pawn))
			return true;

		return false;
	}






	BlackTeam::BlackTeam()
	{
		kCol = 4;
		kRow = 7;
		team = ChessPiece::team_type::black;
		gridPtr = nullptr;
		checkmateStatus = false;
	}






	BlackTeam::BlackTeam(Grid* g, bool m)
	{
		kCol = 4;
		kRow = 7;
		team = ChessPiece::team_type::black;
		gridPtr = g;
		checkmateStatus = m;
	}






	bool BlackTeam::isCapture(int pos1, int pos2, int move1, int move2) const
	{
		/* if opponent occupies destination */
		if (isPiece(move1, move2) && getTeam(move1, move2) != getTeam(pos1, pos2) 
									&& pos2 == move2 + 1 && abs(pos1 - move1) == 1) {
			return true;
		}
		return false; 
	}






	bool BlackTeam::isEnPassant(int pos1, int pos2, int move1, int move2) const
	{
		assert(inBounds4(pos1, pos2, move1, move2));

		if (isPiece(pos1, pos2) && getPiece(pos1, pos2) != ChessPiece::piece_type::pawn) {
			return false;
		}

		if (pos2 != 3 || move2 != 2)    // if current position is not fifth rank
			return false;               // and moving to the proper row
		// if either of the objects to the left or right has enPassant == true
		else if (move1 == (pos1 - 1) && isPiece(pos1 - 1, pos2) 
				&& ((Pawn*)getElement(pos1 - 1, pos2))->getEnPassant())
			return true;
		else if (move1 == (pos1 + 1) && isPiece(pos1 + 1, pos2) 
				&& ((Pawn*)getElement(pos1 + 1, pos2))->getEnPassant())
			return true;
		
		return false;
	}






	void BlackTeam::pawnPromote(int pos1, int pos2, int move1, int move2)
	{
		assert(inBounds4(pos1, pos2, move1, move2));
		ChessPiece::team_type team = getTeam(pos1, pos2);

		if (isPiece(pos1, pos2) && getPiece(pos1, pos2) == ChessPiece::piece_type::pawn
																		&& move2 == 0) {
			
			// later, promote with options HERE
			Queen* qPtr = new Queen(pos1, pos2, team);
			remove(pos1, pos2);
			setElement(pos1, pos2, qPtr);
		}
	}






	bool BlackTeam::Castle(int pos1, int pos2, int move1, int move2)
	{
		assert(isPiece(pos1, pos2));

		// confirm the basic conditions
		if (getPiece(pos1, pos2) != ChessPiece::piece_type::king 
					|| !((King*)getElement(pos1, pos2))->getCastleStatus() || isCheck())
			return false;

		if (move1 == 6 && move2 == 7) {
			if (isPiece(7, 7) && getPiece(7, 7) == ChessPiece::piece_type::rook 
					&& ((Rook*)getElement(7, 7))->getCastleStatus()) {
				if (validCastlePath(4, 7, 7, 7)) {
					((Rook*)getElement(7, 7))->setCastleStatus(false);
					((King*)getElement(4, 7))->setCastleStatus(false);
					setPiece(7, 7, 5, 7);
					return true;
				}
			}
		}
		else if (move1 == 2 && move2 == 7) {
			if (isPiece(0, 7) && getPiece(0, 7) == ChessPiece::piece_type::rook 
					&& ((Rook*)getElement(0, 7))->getCastleStatus()) {
				if (validCastlePath(4, 7, 0, 7)) {
					((Rook*)getElement(0, 7))->setCastleStatus(false);
					((King*)getElement(4, 7))->setCastleStatus(false);
					setPiece(0, 7, 3, 7);
					return true;
				}
			}
		}
		

		return false;
	}






	bool BlackTeam::checkCorners(int kCol, int kRow) const
	{
		int left = kCol - 1;
		int right = kCol + 1;
		int pRow = kRow - 1;

		if ((isPiece(right, pRow) && getTeam(right, pRow) != team
			&& getPiece(right, pRow) == ChessPiece::piece_type::pawn) ||
			(isPiece(left, pRow) && getTeam(left, pRow) != team
				&& getPiece(left, pRow) == ChessPiece::piece_type::pawn))
			return true;

		return false;
	}

}


