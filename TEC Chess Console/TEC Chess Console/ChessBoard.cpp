/*/-------------------------------------------------------------------------------------//
    Filename:           ChessBoard.cpp
    Contributor:        Sonja Braden
    Date:               10/16/2020
    Reference:
    Description:        Implementation  of the ChessBoard class, used for creating objects
                        with properties of a chess board, including enforcement of
                        the rules of chess. 
                        
                        Note: Annoyingly, I have indexed the Board coordinates as 
						(Column, Row) because this is how a chess board is labeled
						(eg, a1, a2, b5, etc. where letters are columns ).
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include <cassert>
#include "ChessBoard.h"


#define inBounds2(a, b) (a < BOARD_SIZE && b < BOARD_SIZE && a >= 0 && b >= 0 )
#define inBounds4(a, b, c, d) (a >= 0 && b >= 0 && c >= 0 && d >= 0 &&  \
                            a < BOARD_SIZE&& b < BOARD_SIZE&& c < BOARD_SIZE&& d < BOARD_SIZE)


using namespace std;

namespace chess {



    ChessBoard::ChessBoard()
    {
        initPieces();   // instantiate the pieces and map them on grid

        whiteT.setGridPtr(&grid);
        // whiteT.setTeam(ChessPiece::team_type::white);
        // blackT.setKing(4, 0);

        blackT.setGridPtr(&grid);
        // blackT.setTeam(ChessPiece::team_type::black);
        // blackT.setKing(4, 7);

        Winner = ChessPiece::team_type::nullType;
    }






    ChessBoard::ChessBoard(const ChessBoard& arg)
    {
        grid = arg.grid;

        Winner = arg.Winner;

        whiteT.setGridPtr(&grid);
        whiteT.setKing(arg.whiteT.getKCol(), arg.whiteT.getKRow());
        whiteT.setTeam(ChessPiece::team_type::white);
        whiteT.setCheckmateStatus(arg.whiteT.getCheckmateStatus());

        blackT.setGridPtr(&grid);
        blackT.setKing(arg.blackT.getKCol(), arg.blackT.getKRow());
        blackT.setTeam(ChessPiece::team_type::black);
        blackT.setCheckmateStatus(arg.blackT.getCheckmateStatus());
    }






    void ChessBoard::moveWhite(int pos1, int pos2, int move1, int move2)
    {
        whiteT.move(pos1, pos2, move1, move2);
    }







    void ChessBoard::moveBlack(int pos1, int pos2, int move1, int move2)
    {
        blackT.move(pos1, pos2, move1, move2);
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

                if (!grid.isPiece(col, row))
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
            setElement(i, 1, new Pawn(i, 1, ChessPiece::team_type::white, false));
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





    
    // Purpose:         Helper to assignment operator and copy constructor
    // Precondition:    Only to be called from assignment operator or copy constructor
    void ChessBoard::copy(const ChessBoard& arg)
    {
        
        grid = arg.grid;

        Winner = arg.Winner;

        whiteT.setGridPtr(&grid);
        whiteT.setKing(arg.whiteT.getKCol(), arg.whiteT.getKRow());
        whiteT.setTeam(ChessPiece::team_type::white);
        whiteT.setCheckmateStatus(arg.whiteT.getCheckmateStatus());

        blackT.setGridPtr(&grid);
        blackT.setKing(arg.blackT.getKCol(), arg.blackT.getKRow());
        blackT.setTeam(ChessPiece::team_type::black);
        blackT.setCheckmateStatus(arg.blackT.getCheckmateStatus());
    }






    // Precondition:    isPiece(row, col) == true
    ChessPiece* ChessBoard::getElement(int col, int row) const
    {
        return grid.getElement(col, row);
    }




    // Precondition:    inBounds2(row, col) == true
    void ChessBoard::setElement(int col, int row, ChessPiece* ptr)
    {
        grid.setElement(col, row, ptr);
    }





    // Precondition:    isPiece(pos1, pos2) == true
    ChessPiece::team_type ChessBoard::getTeam(int pos1, int pos2) const
    {
        assert(grid.isPiece(pos1, pos2));
        return grid.getElement(pos1, pos2)->getTeamType();
    }





    // Precondition:    isPiece(pos1, pos2) == true
    ChessPiece::piece_type ChessBoard::getPiece(int pos1, int pos2) const
    {
        assert(grid.isPiece(pos1, pos2));
        return grid.getElement(pos1, pos2)->getPieceType();
    }




}  // closes namespace

