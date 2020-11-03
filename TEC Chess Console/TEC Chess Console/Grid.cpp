/*/-------------------------------------------------------------------------------------//
	Filename:           Grid.h
	Contributor:        Sonja Braden
	Date:               10/16/2020
	Reference:
	Description:        Implementation  of the Grid class, used for managing the dynamic
						dynamic ChessPiece objects via an array of pointers
//-------------------------------------------------------------------------------------/*/

#include "Grid.h"



namespace chess {
	
	Grid::Grid()
	{
		// initialize a "blank" grid
		// int SPACES = BOARD_SIZE * BOARD_SIZE;
		
		for (int i = 0; i < BOARD_SIZE; i++)
			for(int j = 0; j < BOARD_SIZE; j++)
				grid[i][j] = nullptr;
		
		initPieces();
	}
	
	
	
	
	
	
	Grid::Grid(const Grid& arg)
	{
		copy(arg);
	}
	
	
	
	
	
	
	Grid::~Grid()
	{
		clear();
	}




	Grid Grid::operator=(const Grid& right) {
		
		if (this != &right) {
			clear();
			copy(right);
		}

		return *this;
	}





	/*
	inline int Grid::toGrid(const int c, const int r) const
	{
		return (c + BOARD_SIZE * r);
	}
	*/





	inline bool Grid::inBounds2(const int a, const int b) const
	{
		return ((a < BOARD_SIZE) && (b < BOARD_SIZE)
			&& a >= 0 && b >= 0);
	}






	inline bool Grid::inBounds4(const int a, const int b, const int c, const int d) const
	{
		return (a >= 0 && b >= 0 && c >= 0 && d >= 0
			&& (a < BOARD_SIZE) && (b < BOARD_SIZE)
			&& (c < BOARD_SIZE) && (d < BOARD_SIZE));
	}






	ChessPiece* Grid::getElement(int col, int row) const
	{
		assert(inBounds2(col, row));
		// return grid[toGrid(col, row)];
		return grid[col][row];
	}






	ChessPiece::piece_type Grid::getPieceType(int col, int row) const
	{
		assert(isPiece(col, row));
		return getElement(col, row)->getPieceType();
	}






	ChessPiece::team_type Grid::getTeamType(int col, int row) const
	{
		assert(isPiece(col, row));
		return getElement(col, row)->getTeamType();
	}






	void Grid::setElement(int col, int row, ChessPiece* ptr)
	{
		assert(inBounds2(col, row));
		// grid[toGrid(col, row)] = ptr;
		grid[col][row] = ptr;
	}





	void Grid::copy(const Grid& arg)
	{
		for (int j = 0; j < BOARD_SIZE; j++) {
			for (int i = 0; i < BOARD_SIZE; i++) {

				ChessPiece* ptr = nullptr;

				if (!arg.isPiece(i, j))
					ptr = nullptr;
				else if (arg.getElement(i, j)->getPieceType() == ChessPiece::piece_type::pawn) {
					bool passVal = ((Pawn*)arg.getElement(i, j))->getEnPassant();
					ptr = new Pawn(i, j, arg.getElement(i, j)->getTeamType(), passVal);
				}
				else if (arg.getElement(i, j)->getPieceType() == ChessPiece::piece_type::rook) {
					bool CastleVal = ((Rook*)arg.getElement(i, j))->getCastleStatus();
					ptr = new Rook(i, j, arg.getElement(i, j)->getTeamType(), CastleVal);
				}
				else if (arg.getElement(i, j)->getPieceType() == ChessPiece::piece_type::knight) {
					ptr = new Knight(i, j, arg.getElement(i, j)->getTeamType());
				}
				else if (arg.getElement(i, j)->getPieceType() == ChessPiece::piece_type::bishop) {
					ptr = new Bishop(i, j, arg.getElement(i, j)->getTeamType());
				}
				else if (arg.getElement(i, j)->getPieceType() == ChessPiece::piece_type::king) {
					bool CastleVal = ((King*)arg.getElement(i, j))->getCastleStatus();
					ptr = new King(i, j, arg.getElement(i, j)->getTeamType(), CastleVal);
				}
				else {  // if (grid[i][j]->getPieceType() == ChessPiece::piece_type::queen) 
					ptr = new Queen(i, j, arg.getElement(i, j)->getTeamType());
				}

				setElement(i, j, ptr);	// set each new element in grid
			}
		}
	}






	void Grid::initPieces()
	{
		/*// uncomment this to more quickly test a possible stalemate
		setElement(0, 6, new Rook(0, 6, ChessPiece::team_type::white, false));
		setElement(1, 0, new King(1, 0, ChessPiece::team_type::white, false));

		setElement(2, 7, new Rook(2, 7, ChessPiece::team_type::black, false));
		setElement(1, 1, new Pawn(1, 1, ChessPiece::team_type::black, false));
		setElement(1, 2, new King(1, 2, ChessPiece::team_type::black, false));
		setElement(1, 3, new Pawn(1, 3, ChessPiece::team_type::black, false));

		// these moves give stalemate:
		// a7 -> c7
		// c8 -> c7
		*/


		// instantiate and map the white team
		setElement(0, 0, new Rook(0, 0, ChessPiece::team_type::white, true));
		setElement(1, 0, new Knight(1, 0, ChessPiece::team_type::white));
		setElement(2, 0, new Bishop(2, 0, ChessPiece::team_type::white));
		setElement(3, 0, new Queen(3, 0, ChessPiece::team_type::white));
		setElement(4, 0, new King(4, 0, ChessPiece::team_type::white, true));
		setElement(5, 0, new Bishop(5, 0, ChessPiece::team_type::white));
		setElement(6, 0, new Knight(6, 0, ChessPiece::team_type::white));
		setElement(7, 0, new Rook(7, 0, ChessPiece::team_type::white, true));

		// white pawns
		for (int i = 0; i < BOARD_SIZE; i++) {
			setElement(i, 1, new Pawn(i, 1, ChessPiece::team_type::white, false));
		}

		// instantiate and map the black team pieces
		setElement(0, 7, new Rook(0, 7, ChessPiece::team_type::black, true));
		setElement(1, 7, new Knight(1, 7, ChessPiece::team_type::black));
		setElement(2, 7, new Bishop(2, 7, ChessPiece::team_type::black));
		setElement(3, 7, new Queen(3, 7, ChessPiece::team_type::black));
		setElement(4, 7, new King(4, 7, ChessPiece::team_type::black, true));
		setElement(5, 7, new Bishop(5, 7, ChessPiece::team_type::black));
		setElement(6, 7, new Knight(6, 7, ChessPiece::team_type::black));
		setElement(7, 7, new Rook(7, 7, ChessPiece::team_type::black, true));

		// black pawns
		for (int i = 0; i < BOARD_SIZE; i++) {
			setElement(i, 6, new Pawn(i, 6, ChessPiece::team_type::black, false));
		}

	}






	void Grid::remove(int c, int r)
	{
		if (isPiece(c, r)) {
			ChessPiece* objPtr = getElement(c, r);
			delete objPtr;                      // destroy the object
			setElement(c, r, nullptr);          // set the grid square to nullptr
		}
	}







	void Grid::clear()
	{
		// deallocate all the ChessPiece objects
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				remove(i, j);
	}






	bool Grid::isPiece(int col, int row) const
	{
		// if (inBounds2(col, row) && grid[toGrid(col, row)] != nullptr)
		if (inBounds2(col, row) && grid[col][row] != nullptr)
			return true;
		return false;
	}
};


