/*/-------------------------------------------------------------------------------------//
	Filename:           DerivedPieces.cpp
	Contributors:       Sonja Braden
	Date:               10/4/2020
	Reference:
	Description:		Implementation of all the derived ChessPieces
//-------------------------------------------------------------------------------------/*/


#include "DerivedPieces.h"
#include <cstdlib>


namespace chess {


	//------------------------------Pawn-----------------------------------//

	Pawn::Pawn() : ChessPiece()
	{
		enPassant = false;
		piece = piece_type::pawn;
	}






	Pawn::Pawn(int inCol, int inRow, team_type color, bool passVal) : ChessPiece(inCol, inRow, color)
	{
		enPassant = passVal;
		piece = piece_type::pawn;
	}






	
	int* Pawn::validMove(int inCol, int inRow) const
	{
		int* path = nullptr;
		team_type team = getTeamType();
		int col = getCol();
		int row = getRow();
		
		if (team == team_type::black) {

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 6 && inRow == 4 && col == inCol) || (inRow == (row - 1) && col == inCol)) {
				if (row == 6 && inRow == 4)			// col == inCol implied
					path = getPath(inCol, inRow);	// only need path if moved two spaces
			  }
			else if (!(row == inRow + 1 && abs(col - inCol) == 1)) // diagonal capture, no path
				// throw PieceMoveError();
				throw chess_except::PieceMoveError("Invalid Pawn move.");
		}
		else { //  if (team == white)

			// if starting row and move two rows forward, or otherwise move only one row forward 
			if ((row == 1 && inRow == 3 && col == inCol) || (inRow == row + 1 && col == inCol)) {
				if (row == 1 && inRow == 3)			//  col == inCol
					path = getPath(inCol, inRow);	// only need path if moved two spaces
			}
			else if (!(inRow == row + 1 && abs(col - inCol) == 1)) // diagonal capture, no path
				// throw PieceMoveError();
				throw chess_except::PieceMoveError("Invalid Pawn move.");
		}

		return path; // could be condensed, but with lengthy, less-readable condition statements
	}






	
	bool Pawn::getEnPassant() const
	{
		return enPassant;
	}






	void Pawn::setEnPassant(bool arg)
	{
		enPassant = arg;
	}
	





	// Precondition:	the move was a 2-space advance from the initial row
	int* Pawn::getPath(int inCol, int inRow) const
	{
		int* path = nullptr;
		int row = getRow();
		team_type team = getTeamType();

		if (abs(inRow - getRow()) == 2) {

			path = new int[MAX_PATH_LEN];
			for (int i = 0; i < MAX_PATH_LEN; i++) {
				path[i] = ARRAY_END;
			}

			path[0] = inCol;
			path[1] = (team == team_type::black ? inRow + 1 : row + 1);
			
		}
		return path;	// path is nullptr if no spaces between position and destination
	}
	





	int* Pawn::getTrapSet() const
	{
		int rowShift = (team == team_type::white) ? 1 : -1;

		const int SIZE = 7;
		int* coordinates = new int[SIZE];  // 3 coordinates plus null terminator
		int displacement = -1;

		for (int j = 0; j < (SIZE - 1); j += 2) {
			coordinates[j] = col + displacement;
			coordinates[j + 1] = row + rowShift;
			displacement++;
		}
		coordinates[SIZE - 1] = ARRAY_END;

		return coordinates;
		
	}






	//------------------------------Knight-----------------------------------//

	Knight::Knight() : ChessPiece()
	{
		piece = piece_type::knight;
	}






	Knight::Knight(int inCol, int inRow, team_type color) : ChessPiece(inCol, inRow, color)
	{
		piece = piece_type::knight;
	}






	// Return:		nullptr by default for all Kight moves b/c their path is irrelevant
	int* Knight::validMove(int inCol, int inRow) const
	{
		int col = getCol();
		int row = getRow();

		bool cond1 = abs(col - inCol) == 2 && abs(row - inRow) == 1; // (1, 0) ---> (0, 2)
		bool cond2 = abs(row - inRow) == 2 && abs(col - inCol) == 1;

		if (!(cond1 || cond2)) {	// neither satisfied
			// throw PieceMoveError();
			throw chess_except::PieceMoveError("Invalid Knight move.");
		}
		
		return nullptr;
	}






	int* Knight::getPath(int inCol, int inRow) const
	{
		return nullptr;	// no path for knights, they can leap
	}






	int* Knight::getTrapSet() const
	{
		const int SIZE = 17;
		int* coordinates = new int[SIZE]; // 8 coordinates plus null terminator

		coordinates[0] = col - 2;
		coordinates[1] = row + 1;
		coordinates[2] = col - 1;
		coordinates[3] = row + 2;

		coordinates[4] = col + 1;
		coordinates[5] = row + 2;
		coordinates[6] = col + 2;
		coordinates[7] = row + 1;

		coordinates[8] = col + 2;
		coordinates[9] = row - 1;
		coordinates[10] = col + 1;
		coordinates[11] = row - 2;

		coordinates[12] = col - 1;
		coordinates[13] = row - 2;
		coordinates[14] = col - 2;
		coordinates[15] = row - 1;

		coordinates[16] = ARRAY_END;

		return coordinates;
	}




	//------------------------------Queen-----------------------------------//

	Queen::Queen() : ChessPiece()
	{
		piece = piece_type::queen;
	}






	Queen::Queen(int inCol, int inRow, team_type color) : ChessPiece(inCol, inRow, color)
	{
		piece = piece_type::queen;
	}






	int* Queen::validMove(int inCol, int inRow) const
	{
		static int* path = nullptr;
		int row = getRow();
		int col = getCol();
		team_type team = getTeamType();

		bool rookMove = ((row == inRow) || (col == inCol));
		bool bishopMove = ((col - inCol) == (row - inRow) || (col - inCol) == -(row - inRow));
		
		if (rookMove) {
			path = getLateralPath(inCol, inRow);
		}											// Rook and Bishop getPath()'s from Queen.
		else if (bishopMove) {
			path = getDiagonalPath(inCol, inRow);
		}
		else {
			// throw PieceMoveError();
			throw chess_except::PieceMoveError("Invalid Queen move.");
		}

		return path;
	}






	int* Queen::getLateralPath(int inCol, int inRow) const
	{
		int* path = nullptr;
		int col = getCol();
		int row = getRow();

		if (abs(inCol - col) > 1 || abs(inRow - row) > 1) {	// if more than 1 squares traversed

			path = new int[MAX_PATH_LEN];
			for (int i = 0; i < MAX_PATH_LEN; i++) {
				path[i] = ARRAY_END;
			}

			int j = 0;
			int next = 0;

			if (col == inCol) {		// same column

				next = (row > inRow) ? inRow + 1 : row + 1;

				while (next != row && next != inRow) {

					path[2 * j] = inCol;
					path[2 * j + 1] = next;
					next++;
					j++;
				}
				
			}
			else if (row == inRow) {	// same column

				next = (col > inCol) ? inCol + 1 : col + 1;

				while (next != col && next != inCol) {

					path[2 * j + 1] = inRow;
					path[2 * j] = next;
					next++;
					j++;
				}
			}
		}
		return path;
	}





	
	
	int* Queen::buildPath(signed int colSign, signed int rowSign, int inCol, int inRow) const {

		int* path = new int[MAX_PATH_LEN];
		for (int i = 0; i < MAX_PATH_LEN; i++) {
			path[i] = ARRAY_END;
		}

		int row = getRow();
		int col = getCol();

		int nextRow = row + rowSign;
		int nextCol = col + colSign;
		int j = 0;
		while (nextRow != inRow && nextCol != inCol) {
			path[j * 2] = nextCol;
			path[j * 2 + 1] = nextRow;
			j++;
			nextRow = nextRow + rowSign;
			nextCol = nextCol + colSign;
		}

		return path;
	}






	// Alternative to the above getDiagonalPath(), uses helper function
	int* Queen::getDiagonalPath(int inCol, int inRow) const
	{
		int* path = nullptr;
		int col = getCol();
		int row = getRow();

		if (abs(inCol - col) == 1 && abs(inRow - row) == 1)	// moved by only 1 space
			return path;
		else {

			if (col > inCol && row < inRow) {
				path = buildPath(-1, 1, inCol, inRow);
			}
			else if (col < inCol && row < inRow) {
				path = buildPath(1, 1, inCol, inRow);
			}
			else if (col < inCol && row > inRow) {
				path = buildPath(1, -1, inCol, inRow);
			}
			else if (col > inCol && row > inRow) {
				path = buildPath(-1, -1, inCol, inRow);
			}
		}

		return path;
	}







	int* Queen::getTrapSet() const
	{
		const int SIZE = 17;
		int* coordinates = new int[SIZE]; // 8 coordinates plus null terminator

		coordinates[0] = col;
		coordinates[1] = row + 1;

		coordinates[2] = col;
		coordinates[3] = row - 1;

		coordinates[4] = col + 1;
		coordinates[5] = row;

		coordinates[6] = col - 1;
		coordinates[7] = row;

		coordinates[8] = col - 1;
		coordinates[9] = row - 1;

		coordinates[10] = col + 1;
		coordinates[11] = row - 1;

		coordinates[12] = col + 1;
		coordinates[13] = row + 1;

		coordinates[14] = col - 1;
		coordinates[15] = row + 1;

		coordinates[16] = ARRAY_END;

		return coordinates;
	}







	//------------------------------Rook-----------------------------------//

	Rook::Rook() : Queen()
	{
		piece = piece_type::rook;
		castle = true;
	}






	Rook::Rook(int inCol, int inRow, team_type color, bool c) : Queen(inCol, inRow, color)
	{
		piece = piece_type::rook;
		castle = c;
	}






	int* Rook::validMove(int inCol, int inRow) const
	{
		int* path = nullptr;
		int col = getCol();
		int row = getRow();


		if ((row == inRow) || (col == inCol)) // if moving only along columns or rows
			path = getPath(inCol, inRow);
		else
			throw chess_except::PieceMoveError("Invalid Rook move.");
			// throw PieceMoveError();

		return path;
	}






	bool Rook::getCastleStatus()
	{
		return castle;
	}






	void Rook::setCastleStatus(bool arg)
	{
		castle = arg;
	}






	int* Rook::getPath(int inCol, int inRow) const
	{
		return getLateralPath(inCol, inRow);
	}






	int* Rook::getTrapSet() const
	{
		const int SIZE = 9;
		int* coordinates = new int[SIZE]; // 4 coordinates plus null terminator

		coordinates[0] = col;
		coordinates[1] = row + 1;

		coordinates[2] = col;
		coordinates[3] = row - 1;

		coordinates[4] = col + 1;
		coordinates[5] = row;

		coordinates[6] = col - 1;
		coordinates[7] = row;

		coordinates[8] = ARRAY_END;

		return coordinates;
	}





	//------------------------------Bishop-----------------------------------//

	Bishop::Bishop() : Queen()
	{
		piece = piece_type::bishop;
	}







	Bishop::Bishop(int inCol, int inRow, team_type color) : Queen(inCol, inRow, color)
	{
		piece = piece_type::bishop;
	}






	int* Bishop::validMove(int inCol, int inRow) const
	{
		int* path = nullptr;
		int col = getCol();
		int row = getRow();

		if ((col - inCol) == (row - inRow) || (col - inCol) == -(row - inRow))
			path = getPath(inCol, inRow);
		else
			throw chess_except::PieceMoveError("Invalid Bishop move.");
			// throw PieceMoveError();
		
		return path;
	}






	int* Bishop::getPath(int inCol, int inRow) const
	{
		return getDiagonalPath(inCol, inRow);
	}





	

	int* Bishop::getTrapSet() const
	{
		const int SIZE = 9;
		int* coordinates = new int[SIZE]; // 4 coordinates plus null terminator

		coordinates[0] = col - 1;
		coordinates[1] = row - 1;

		coordinates[2] = col + 1;
		coordinates[3] = row - 1;

		coordinates[4] = col + 1;
		coordinates[5] = row + 1;

		coordinates[6] = col - 1;
		coordinates[7] = row + 1;

		coordinates[8] = ARRAY_END;

		return coordinates;
	}





	//------------------------------King-----------------------------------//

	King::King() : ChessPiece()
	{
		piece = piece_type::king;
		castle = true;
	}






	King::King(int inCol, int inRow, team_type color, bool c) : ChessPiece(inCol, inRow, color)
	{
		piece = piece_type::king;
		castle = c;
	}






	// Like the Knight, the "path" for King is irrelevant,
	// as he only moves space by space. Path only concern space between the position 
	// and destination. Nullptr will be returned by default

	int* King::validMove(int inCol, int inRow) const
	{
		int row = getRow();
		int col = getCol();

		// if ((inRow > row + 1) || (inRow < row - 1) || (inCol > col + 1) || (inCol < col - 1))
		if (!((inRow <= row + 1) && (inRow >= row - 1) && (inCol <= col + 1) && (inCol >= col - 1))) 
			throw chess_except::PieceMoveError("Invalid King move.");
			// throw PieceMoveError();


		return  nullptr;
	}






	bool King::getCastleStatus()
	{
		return castle;
	}






	void King::setCastleStatus(bool arg)
	{
		castle = arg;
	}






	int* King::getPath(int inCol, int inRow) const
	{
		return nullptr;	// no path for Kings, they only move by 1 space at a time
	}






	int* King::getTrapSet() const
	{
		const int SIZE = 17;
		int* coordinates = new int[SIZE]; // 8 coordinates plus null terminator

		coordinates[0] = col;
		coordinates[1] = row + 1;

		coordinates[2] = col;
		coordinates[3] = row - 1;

		coordinates[4] = col + 1;
		coordinates[5] = row;

		coordinates[6] = col - 1;
		coordinates[7] = row;

		coordinates[8] = col - 1;
		coordinates[9] = row - 1;

		coordinates[10] = col + 1;
		coordinates[11] = row - 1;

		coordinates[12] = col + 1;
		coordinates[13] = row + 1;

		coordinates[14] = col - 1;
		coordinates[15] = row + 1;

		coordinates[16] = ARRAY_END;

		return coordinates;
	}




}	// closes namespace










/*

Some alternative implementations...


int* Queen::getDiagonalPath(int inCol, int inRow) const
{
	int* path = nullptr;
	int col = getCol();
	int row = getRow();

	if (abs(inCol - col) == 1 && abs(inRow - row) == 1)	// moved by only 1 space
		return nullptr;
	else {
		path = new int[2 * MAX_PATH]{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };	// function for this?

		if (row < inRow && col > inCol) {

			//	__ x2 __ __
			//	__ __ __ __
			//	__ __ __ x1
			//	__ __ __ __

			int nextRow = row + 1;
			int nextCol = col - 1;
			int j = 0;
			while (nextRow != inRow && nextCol != inCol) {
				path[j * 2] = nextCol;
				path[j * 2 + 1] = nextRow;
				j++;
				nextRow++;
				nextCol--;
			}
		}
		else if (row < inRow && col < inCol) {

			//	__ __ __ x2
			//	__ __ __ __
			//	__ x1 __ __
			//	__ __ __ __

			int nextRow = row + 1;
			int nextCol = col + 1;
			int j = 0;
			while (nextRow != inRow && nextCol != inCol) {
				path[j * 2] = nextCol;
				path[j * 2 + 1] = nextRow;
				j++;
				nextRow++;
				nextCol++;
			}
		}
		else if (row > inRow && col < inCol) {

			//	__ __ __ __
			//	__ x1 __ __
			//	__ __ __ __
			//	__ __ __ x2

			int nextRow = row - 1;
			int nextCol = col + 1;
			int j = 0;
			while (nextRow != inRow && nextCol != inCol) {
				path[j * 2] = nextCol;
				path[j * 2 + 1] = nextRow;
				j++;
				nextRow--;
				nextCol++;
			}
		}
		else if (row > inRow && col > inCol) {

			//	__ __ __ x1
			//	__ __ __ __
			//	__ x2 __ __
			//	__ __ __ __

			int nextRow = row - 1;
			int nextCol = col - 1;
			int j = 0;
			while (nextRow != inRow && nextCol != inCol) {
				path[j * 2] = nextCol;
				path[j * 2 + 1] = nextRow;
				j++;
				nextRow--;
				nextCol--;
			}
		}
	}

	return path;
}

*/





/*

int* Queen::getLateralPath(int inCol, int inRow) const
	{
		int* path = nullptr;
		int col = getCol();
		int row = getRow();

		if (abs(inCol - col) > 1 || abs(inRow - row) > 1) {	// if more than 1 squares traversed

			path = new int[2 * MAX_PATH]{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
			int j = 0;

			if (col == inCol) {	// same column

				if (row > inRow) {

					int nextRow = inRow + 1;
					while (nextRow != row) {

						path[2 * j] = inCol;
						path[2 * j + 1] = nextRow;
						nextRow++;
						j++;
					}
				}
				else {	// if row < inRow

					int nextRow = row + 1;
					while (nextRow != inRow) {

						path[2 * j] = inCol;
						path[2 * j + 1] = nextRow;
						nextRow++;
						j++;
					}
				}
			}
			else if (row == inRow) {	// same column

				if (col > inCol) {

					int nextCol = inCol + 1;
					while (nextCol != col) {

						path[2 * j + 1] = inRow;
						path[2 * j] = nextCol;
						nextCol++;
						j++;
					}
				}
				else {	// if col < inCol

					int nextCol = col + 1;
					while (nextCol != inCol) {

						path[2 * j + 1] = inRow;
						path[2 * j] = nextCol;
						nextCol++;
						j++;
					}
				}
			}
		}

		return path;
	}


*/