/*/-------------------------------------------------------------------------------------//
    Filename:           ChessBoard.cpp
    Contributor:        Sonja Braden
    Date:               10/4/2020
    Reference:

    Description:        Implementation  of the ChessBoard class, used for creating objects
                        with properties of a chess board, including enforcement of
                        the rules of chess.
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include <cassert>
#include "S_ChessBoard.h"

#define inBounds4(a, b, c, d) (a >= 0 && b >= 0 && c >= 0 && d >= 0 &&  \
                            a < BOARD_SIZE&& b < BOARD_SIZE&& c < BOARD_SIZE&& d < BOARD_SIZE)
#define inBounds2(a, b) (a < BOARD_SIZE && b < BOARD_SIZE && a >= 0 && b >= 0 )

//#define accessGrid(col, row) (grid[row * BOARD_SIZE + col])

using namespace std;

namespace chess {



    ChessBoard::ChessBoard()
    {
        // Allocate for the grid
        grid = new ChessPiece* [BOARD_SIZE * BOARD_SIZE];

        // initialize a "blank" grid
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                setElement(j, i, nullptr);

        // instantiate the pieces and map them on grid
        initPieces();

        whiteT.setTeam(ChessPiece::team_type::white);
        whiteT.setGridPtr(grid);
        blackT.setKing(4, 0);

        blackT.setTeam(ChessPiece::team_type::black);
        blackT.setGridPtr(grid);
        blackT.setKing(4, 7);

        Winner = ChessPiece::team_type::nullType;
    }






    ChessBoard::ChessBoard(const ChessBoard& arg)
    {
        copy(arg);
    }







    ChessBoard::~ChessBoard()
    {
        clear();
    }






    ChessBoard ChessBoard::operator=(const ChessBoard& right)
    {
        if (this != &right) {
            clear();
            copy(right);
        }

        return *this;
    }






    void ChessBoard::moveWhite(int pos1, int pos2, int move1, int move2)
    {
        if (getTeam(pos1, pos2) == ChessPiece::team_type::white)
            whiteT.move(pos1, pos2, move1, move2, ChessPiece::team_type::white);
        else
            throw TurnMoveError();

        /*
        if (isPiece(pos1, pos2))
            if (getTeam(pos1, pos2) == ChessPiece::team_type::white)
                whiteT.move(pos1, pos2, move1, move2, ChessPiece::team_type::white);
            else
                throw TurnMoveError();
        else
            throw EmptySquareError();
            */

    }







    void ChessBoard::moveBlack(int pos1, int pos2, int move1, int move2)
    {
        if (getTeam(pos1, pos2) == ChessPiece::team_type::black)
            blackT.move(pos1, pos2, move1, move2, ChessPiece::team_type::black);
        else
            throw TurnMoveError();
        
        /*
        if (isPiece(pos1, pos2))
            if (getTeam(pos1, pos2) == ChessPiece::team_type::black)
                blackT.move(pos1, pos2, move1, move2, ChessPiece::team_type::black);
            else
                throw TurnMoveError();
        else
            throw EmptySquareError();
            */
    }






    void ChessBoard::printBoard() const
    {

        int row_label = 8;

        // upper column labels
        std::cout << "  ";
        for (char col_label = 'a'; col_label < 'i'; col_label++)
            std::cout << col_label << "  ";
        std::cout << endl;

        //black-oriented would be: (int row = 0; row < BOARD_SIZE; row++)
        for (int row = (BOARD_SIZE - 1); row >= 0; row--) {
            cout << row_label << " ";   // row labels
            for (int col = 0; col < BOARD_SIZE; col++) {

                if (getElement(col, row) == nullptr)
                    std::cout << "__";
                else {
                    ChessPiece::team_type team = getTeam(col, row);     // grid[col][row]->getTeamType();
                    ChessPiece::piece_type piece = getPiece(col, row);   // grid[col][row]->getPieceType();
                    std::cout << static_cast<std::underlying_type<ChessPiece::team_type>::type>(team)
                        << static_cast<std::underlying_type<ChessPiece::team_type>::type>(piece);
                    // cast the team and piece types beack to underlying types for printing
                }

                std::cout << " ";
            }
            std::cout << row_label; // row labels
            std::cout << endl;
            row_label--;
        }

        // lower column labels
        std::cout << "  ";
        for (char col_label = 'a'; col_label < 'i'; col_label++)
            std::cout << col_label << "  ";
        std::cout << endl;
    }







    ChessPiece::team_type ChessBoard::getWinner()
    {
        return Winner;
    }






    void ChessBoard::setWinner(ChessPiece::team_type arg) {

        Winner = arg;
    }






    void ChessBoard::initPieces()
    {
        
        // instantiate and map the white team
        setElement(0, 0, new Rook(0, 0, ChessPiece::team_type::white));
        setElement(1, 0, new Knight(1, 0, ChessPiece::team_type::white));
        setElement(2, 0, new Bishop(2, 0, ChessPiece::team_type::white));
        setElement(3, 0, new Queen(3, 0, ChessPiece::team_type::white));
        setElement(4, 0, new King(4, 0, ChessPiece::team_type::white));
        setElement(5, 0, new Bishop(5, 0, ChessPiece::team_type::white));
        setElement(6, 0, new Knight(6, 0, ChessPiece::team_type::white));
        setElement(7, 0, new Rook(7, 0, ChessPiece::team_type::white));

        // white pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
            setElement(i, 6, new Pawn(i, 6, ChessPiece::team_type::white, false));
        }

        // instantiate and map the black team pieces
        setElement(0, 7, new Rook(0, 7, ChessPiece::team_type::black));
        setElement(1, 7, new Knight(1, 7, ChessPiece::team_type::black));
        setElement(2, 7, new Bishop(2, 7, ChessPiece::team_type::black));
        setElement(3, 7, new Queen(3, 7, ChessPiece::team_type::black));
        setElement(4, 7, new King(4, 7, ChessPiece::team_type::black));
        setElement(5, 7, new Bishop(5, 7, ChessPiece::team_type::black));
        setElement(6, 7, new Knight(6, 7, ChessPiece::team_type::black));
        setElement(7, 7, new Rook(7, 7, ChessPiece::team_type::black));

        // black pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
             setElement(i, 6, new Pawn(i, 6, ChessPiece::team_type::black, false));
        }
    }







    void ChessBoard::remove(int x, int y)
    {
        if (getElement(x, y) != nullptr) {
            ChessPiece* objPtr = getElement(x, y);
            delete objPtr;                      // destroy the object
            setElement(x, y, nullptr);          // set the grid square to nullptr
        }
    }





    // Purpose:         Helper to assignment operator and destructor
    // Precondition:    Only to be called from assignment operator or destructor
    void ChessBoard::clear()
    {
        // deallocate all the ChessPiece objects
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                remove(i, j);

        // deallocate the grid of ChessPiece poiters
        delete[] grid;
        grid = nullptr;
        whiteT.setGridPtr(nullptr); // leave other members of white an black team?
        blackT.setGridPtr(nullptr);
    }






    // Purpose:         Helper to assignment operator and copy constructor
    // Precondition:    Only to be called from assignment operator or copy constructor
    void ChessBoard::copy(const ChessBoard& arg)
    {
        grid = new ChessPiece * [BOARD_SIZE * BOARD_SIZE];

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {

                ChessPiece* ptr = nullptr;

                if (arg.getElement(i, j) == nullptr)
                    ChessPiece* ptr = nullptr;
                else if (arg.getPiece(i, j) == ChessPiece::piece_type::pawn) {
                    bool passVal = ((Pawn*)arg.getElement(i, j))->getEnPassant();
                    ptr = new Pawn(i, j, arg.getTeam(i, j), passVal);
                }
                else if (arg.getPiece(i, j) == ChessPiece::piece_type::rook) {
                    ptr = new Rook(i, j, arg.getTeam(i, j));
                }
                else if (arg.getPiece(i, j) == ChessPiece::piece_type::knight) {
                    ptr = new Knight(i, j, arg.getTeam(i, j));
                }
                else if (arg.getPiece(i, j) == ChessPiece::piece_type::bishop) {
                    ptr = new Bishop(i, j, arg.getTeam(i, j));
                }
                else if (arg.getPiece(i, j) == ChessPiece::piece_type::king) {
                    ptr = new King(i, j, arg.getTeam(i, j));
                }
                else {  // if (grid[i][j]->getPieceType() == ChessPiece::piece_type::queen) 
                    ptr = new Queen(i, j, arg.getTeam(i, j));
                }

                setElement(i, j, ptr);
            }
        }

        Winner = arg.Winner;

        whiteT.setGridPtr(grid);
        whiteT.setKing(arg.whiteT.getKCol(), arg.whiteT.getKRow());
        whiteT.setTeam(ChessPiece::team_type::white);
        whiteT.setCheckmateStatus(arg.whiteT.getCheckmateStatus());

        blackT.setGridPtr(grid);
        blackT.setKing(arg.blackT.getKCol(), arg.blackT.getKRow());
        blackT.setTeam(ChessPiece::team_type::black);
        blackT.setCheckmateStatus(arg.blackT.getCheckmateStatus());
    }






    // Precondition:    isPiece(row, col) == true
    ChessPiece* ChessBoard::getElement(int col, int row) const
    {
        assert(isPiece(row, col));
        return grid[row * BOARD_SIZE + col];
    }




    // Precondition:    inBounds2(row, col) == true
    ChessPiece* ChessBoard::setElement(int col, int row, ChessPiece* ptr)
    {
        assert(inBounds2(col, row));
        grid[row * BOARD_SIZE + col] = ptr;
    }






    bool ChessBoard::isPiece(int inCol, int inRow) const
    {
        if (inBounds2(inCol, inRow) && getElement(inCol, inRow) != nullptr)
            return true;
        return false;
    }





    // Precondition:    isPiece(pos1, pos2) == true
    ChessPiece::team_type ChessBoard::getTeam(int pos1, int pos2) const
    {
        assert(isPiece(pos1, pos2));
        return (grid[pos1 * BOARD_SIZE + pos2])->getTeamType();
    }





    // Precondition:    isPiece(pos1, pos2) == true
    ChessPiece::piece_type ChessBoard::getPiece(int pos1, int pos2) const
    {
        assert(isPiece(pos1, pos2));
        return (grid[pos1 * BOARD_SIZE + pos2])->getPieceType();
    }




}  // closes namespace






    /*
    //    Precondition: Either colSign or rowSign is 0
    //                  Either colSign or RowSign is 1 or -1
    //                  kCol is the king's column
    //                  kRow is the king's row
    bool ChessBoard::singleLateral(ChessPiece::team_type kingTeam, int kCol, int kRow, int colSign, int rowSign) const
    {
        int nextRow = kRow + rowSign;
        int nextCol = kCol + colSign;

        if (colSign != 0) {
            while (nextCol < BOARD_SIZE && nextCol >= 0 && !isPiece(nextCol, kRow))
                nextCol = nextCol + colSign;

            if (isPiece(nextCol, kRow) && getTeam(nextCol, kRow) != kingTeam
                && (getPiece(nextCol, kRow) == ChessPiece::piece_type::queen
                || getPiece(nextCol, kRow) == ChessPiece::piece_type::rook))
                return true;
        }
        else if (rowSign != 0) {  // if (kCol == nextCol)
            while (nextRow < BOARD_SIZE && nextRow >= 0 && !isPiece(kCol, nextRow))
                nextRow = nextRow + rowSign;

            if (isPiece(kCol, nextRow) && getTeam(nextCol, kRow) != kingTeam
                && (getPiece(kCol, nextRow) == ChessPiece::piece_type::queen
                || getPiece(kCol, nextRow) == ChessPiece::piece_type::rook))
                return true;
        }

        return false;
    }
    */