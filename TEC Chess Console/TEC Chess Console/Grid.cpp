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
		int SPACES = BOARD_SIZE * BOARD_SIZE;
		for (int i = 0; i < SPACES; i++)
			grid[i] = nullptr;
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






	inline int Grid::toGrid(const int c, const int r) const
	{
		return (c + BOARD_SIZE * r);
	}






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
		return grid[toGrid(col, row)];
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
		grid[toGrid(col, row)] = ptr;
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
					ptr = new Rook(i, j, arg.getElement(i, j)->getTeamType());
				}
				else if (arg.getElement(i, j)->getPieceType() == ChessPiece::piece_type::knight) {
					ptr = new Knight(i, j, arg.getElement(i, j)->getTeamType());
				}
				else if (arg.getElement(i, j)->getPieceType() == ChessPiece::piece_type::bishop) {
					ptr = new Bishop(i, j, arg.getElement(i, j)->getTeamType());
				}
				else if (arg.getElement(i, j)->getPieceType() == ChessPiece::piece_type::king) {
					ptr = new King(i, j, arg.getElement(i, j)->getTeamType());
				}
				else {  // if (grid[i][j]->getPieceType() == ChessPiece::piece_type::queen) 
					ptr = new Queen(i, j, arg.getElement(i, j)->getTeamType());
				}

				setElement(i, j, ptr);	// set each new element in grid
			}
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
		if (inBounds2(col, row) && grid[toGrid(col, row)] != nullptr)
			return true;
		return false;
	}
};


