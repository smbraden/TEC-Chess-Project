/*/-------------------------------------------------------------------------------------//
    Filename:           ChessBoard.cpp
    Contributor:        Sonja Braden
    Date:               10/16/2020
    Reference:
    Description:        Implementation  of the ChessBoard class, used for creating objects
                        with properties of a chess board, including enforcement of
                        the rules of chess. 
                        
                        Note: Annoyingly, I originally indexed the Board coordinates as 
						(Column, Row) because this is how a chess board is labeled
						(eg, a1, a2, b5, etc. where letters are columns ).
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include <cassert>
#include "ChessBoard.h"
// #include "ChessExceptions.h"


namespace chess {



    ChessBoard::ChessBoard()
    {
        // grid = Grid();
        history = History();
        turnMachine = ChessTeam();
        winner = ChessPiece::team_type::nullType;
        draw = false;
    }






    inline bool ChessBoard::inBounds2(const int a, const int b)  const
    {
        return ((a < BOARD_SIZE) && (b < BOARD_SIZE)
            && a >= 0 && b >= 0);
    }






    inline bool ChessBoard::inBounds4(const int a, const int b, const int c, const int d)  const
    {
        return (a >= 0 && b >= 0 && c >= 0 && d >= 0
            && (a < BOARD_SIZE) && (b < BOARD_SIZE)
            && (c < BOARD_SIZE) && (d < BOARD_SIZE));
    }






    void ChessBoard::move(int pos1, int pos2, int move1, int move2)
    {
        // Could get rid of winner and draw members
        // turnMachine.move(pos1, pos2, move1, move2);

        try {
            turnMachine.move(pos1, pos2, move1, move2);
        }
        catch (const chess_except::WinSignal& e) {
            winner = (turnMachine.getTurnTeam() == ChessPiece::team_type::white) ?
                ChessPiece::team_type::black : ChessPiece::team_type::white;
            throw e;
        }
        catch (const chess_except::DrawSignal& e) {
            draw = true;
            throw e;
        }
        

        if (history.newPage(turnMachine.getTurnTeam(), turnMachine.getGrid()))      // newPage() returns true when 3-fold repetition reached
            throw chess_except::DrawSignal("The cause is 3-fold repetition of the game state...");
    }






    void ChessBoard::printBoard() const
    {
        int row_label = 8;

        // upper column labels
        std::cout << "  ";
        for (char col_label = 'a'; col_label < 'i'; col_label++)
            std::cout << col_label << "  ";
        std::cout << std::endl;

        //black-oriented would be: (int row = 0; row < BOARD_SIZE; row++)
        for (int row = (BOARD_SIZE - 1); row >= 0; row--) {
            std::cout << row_label << " ";   // row labels
            for (int col = 0; col < BOARD_SIZE; col++) {

                if (!isPiece(col, row))
                    std::cout << "__";
                else {
                    ChessPiece::team_type team = getTeamType(col, row);
                    ChessPiece::piece_type piece = getPieceType(col, row);
                    std::cout << static_cast<std::underlying_type<ChessPiece::team_type>::type>(team)
                        << static_cast<std::underlying_type<ChessPiece::team_type>::type>(piece);
                    // cast the team and piece types beack to underlying types for printing
                }

                std::cout << " ";
            }
            std::cout << row_label; // row labels
            std::cout << std::endl;
            row_label--;
        }

        // lower column labels
        std::cout << "  ";
        for (char col_label = 'a'; col_label < 'i'; col_label++)
            std::cout << col_label << "  ";
        std::cout << std::endl;
    }





    
    ChessPiece::team_type ChessBoard::getWinner()
    {
        return winner;
    }





    ChessPiece::team_type ChessBoard::getTurnTeam()
    {
        return turnMachine.getTurnTeam();
    }






    bool ChessBoard::isPiece(int pos1, int pos2) const
    {

        return turnMachine.isPiece(pos1, pos2);
    }






    // Precondition:    isPiece(pos1, pos2) == true
    ChessPiece::team_type ChessBoard::getTeamType(int pos1, int pos2) const
    {
        assert(turnMachine.isPiece(pos1, pos2));
        return turnMachine.getTeamType(pos1, pos2);
    }





    // Precondition:    isPiece(pos1, pos2) == true
    ChessPiece::piece_type ChessBoard::getPieceType(int pos1, int pos2) const
    {
        assert(turnMachine.isPiece(pos1, pos2));
        return turnMachine.getPieceType(pos1, pos2);
    }



}  // closes namespace



















    /*
    void ChessBoard::initPieces()
    {
        // uncomment this to more quickly test a possible stalemate
        // setElement(0, 6, new Rook(0, 6, ChessPiece::team_type::white, false));
        // setElement(1, 0, new King(1, 0, ChessPiece::team_type::white, false));

        // setElement(2, 7, new Rook(2, 7, ChessPiece::team_type::black, false));
        // setElement(1, 1, new Pawn(1, 1, ChessPiece::team_type::black, false));
        // setElement(1, 2, new King(1, 2, ChessPiece::team_type::black, false));
        // setElement(1, 3, new Pawn(1, 3, ChessPiece::team_type::black, false));

        // these moves give stalemate:
        // a7 -> c7
        // c8 -> c7



        // instantiate and map the white team
        setElement(0, 0, new Rook(0, 0, ChessPiece::team_type::white, false));
        setElement(1, 0, new Knight(1, 0, ChessPiece::team_type::white));
        setElement(2, 0, new Bishop(2, 0, ChessPiece::team_type::white));
        setElement(3, 0, new Queen(3, 0, ChessPiece::team_type::white));
        setElement(4, 0, new King(4, 0, ChessPiece::team_type::white, false));
        setElement(5, 0, new Bishop(5, 0, ChessPiece::team_type::white));
        setElement(6, 0, new Knight(6, 0, ChessPiece::team_type::white));
        setElement(7, 0, new Rook(7, 0, ChessPiece::team_type::white, false));

        // white pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
            setElement(i, 1, new Pawn(i, 1, ChessPiece::team_type::white, false));
        }

        // instantiate and map the black team pieces
        setElement(0, 7, new Rook(0, 7, ChessPiece::team_type::black, false));
        setElement(1, 7, new Knight(1, 7, ChessPiece::team_type::black));
        setElement(2, 7, new Bishop(2, 7, ChessPiece::team_type::black));
        setElement(3, 7, new Queen(3, 7, ChessPiece::team_type::black));
        setElement(4, 7, new King(4, 7, ChessPiece::team_type::black, false));
        setElement(5, 7, new Bishop(5, 7, ChessPiece::team_type::black));
        setElement(6, 7, new Knight(6, 7, ChessPiece::team_type::black));
        setElement(7, 7, new Rook(7, 7, ChessPiece::team_type::black, false));

        // black pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
             setElement(i, 6, new Pawn(i, 6, ChessPiece::team_type::black, false));
        }

    }
    */





    /*
        void ChessBoard::printBoard() const
        {
            int row_label = 8;

            // upper column labels
            std::cout << "  ";
            for (char col_label = 'a'; col_label < 'i'; col_label++)
                std::cout << col_label << "  ";
            std::cout << std::endl;

            //black-oriented would be: (int row = 0; row < BOARD_SIZE; row++)
            for (int row = (BOARD_SIZE - 1); row >= 0; row--) {
                std::cout << row_label << " ";   // row labels
                for (int col = 0; col < BOARD_SIZE; col++) {

                    if (!grid.isPiece(col, row))
                        std::cout << "__";
                    else {
                        ChessPiece::team_type team = getTeam(col, row);
                        ChessPiece::piece_type piece = getPiece(col, row);
                        std::cout << static_cast<std::underlying_type<ChessPiece::team_type>::type>(team)
                            << static_cast<std::underlying_type<ChessPiece::team_type>::type>(piece);
                        // cast the team and piece types beack to underlying types for printing
                    }

                    std::cout << " ";
                }
                std::cout << row_label; // row labels
                std::cout << std::endl;
                row_label--;
            }

            // lower column labels
            std::cout << "  ";
            for (char col_label = 'a'; col_label < 'i'; col_label++)
                std::cout << col_label << "  ";
            std::cout << std::endl;
        }
        */