/*/-------------------------------------------------------------------------------------//
    Filename:           ChessBoard.cpp
    Contributor:        Sonja Braden
    Date:               9/23/2020
    Reference:          

    Description:        Implementation  of the ChessBoard class, used for creating objects
                        with properties of a chess board, including enforcement of
                        the rules of chess.
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include "ChessBoard.h"

using namespace std;

namespace chess {
    
    ChessBoard::ChessBoard()
    {
        // initialize a"blank" grid
        for (int i = 0; i < BOARD_SIZE; i++) {

            for (int j = 0; j < BOARD_SIZE; j++) {
                grid[j][i] = nullptr;
            }
        }

        // instantiate the pieces and map them on grid
        initPieces();
    }
    






    int ChessBoard::moveWhite(int pos1, int pos2, int move1, int move2)
    {
        move(pos1, pos2, move1, move2, ChessPiece::white);
        return 0;
    }







    int ChessBoard::moveBlack(int pos1, int pos2, int move1, int move2)
    {
        move(pos1, pos2, move1, move2, ChessPiece::black);
        return 0;
    }







    void ChessBoard::printBoard()
    {
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {

                if (grid[col][row] == nullptr) {
                    cout << "__" << endl;
                }
                else
                {
                    cout << grid[col][row]->getTeamType() << grid[col][row]->getPieceType() << endl;
                }
            }
        }
    }







    void ChessBoard::initPieces()
    {
        // set the white team
        Castle wC1(0, 0);
        Knight wN1(1, 0);
        Rook wR1(2, 0);
        Queen wQ(3, 0);
        King wK(4, 0);
        Rook wR2(5, 0);
        Knight wN2(6, 0);
        Castle wC2(7, 0);

        Pawn wP1(0, 1);
        Pawn wP2(1, 1);
        Pawn wP3(2, 1);
        Pawn wP4(3, 1);
        Pawn wP5(4, 1);
        Pawn wP6(5, 1);
        Pawn wP7(6, 1);
        Pawn wP8(7, 1);

        // map the white pieces on grid
        grid[0][0] = &wC1;
        grid[1][0] = &wN1;
        grid[2][0] = &wR1;
        grid[3][0] = &wQ;
        grid[4][0] = &wK;
        grid[5][0] = &wR2;
        grid[6][0] = &wN2;
        grid[7][0] = &wC2;

        grid[0][1] = &wP1;
        grid[1][1] = &wP2;
        grid[2][1] = &wP3;
        grid[3][1] = &wP4;
        grid[4][1] = &wP5;
        grid[5][1] = &wP6;
        grid[6][1] = &wP7;
        grid[7][1] = &wP8;

        // instantiate the black team pieces
        Castle bC1(0, 7, ChessPiece::black);
        Knight bN1(1, 7, ChessPiece::black);
        Rook bR1(2, 7, ChessPiece::black);
        Queen bQ(3, 7, ChessPiece::black);
        King bK(4, 7, ChessPiece::black);
        Rook bR2(5, 7, ChessPiece::black);
        Knight bN2(6, 7, ChessPiece::black);
        Castle bC2(7, 7, ChessPiece::black);

        Pawn bP1(0, 6, ChessPiece::black);
        Pawn bP2(1, 6, ChessPiece::black);
        Pawn bP3(2, 6, ChessPiece::black);
        Pawn bP4(3, 6, ChessPiece::black);
        Pawn bP5(4, 6, ChessPiece::black);
        Pawn bP6(5, 6, ChessPiece::black);
        Pawn bP7(6, 6, ChessPiece::black);
        Pawn bP8(7, 6, ChessPiece::black);

        // map the black pieces on grid
        grid[0][7] = &bC1;
        grid[1][7] = &bN1;
        grid[2][7] = &bR1;
        grid[3][7] = &bQ;
        grid[4][7] = &bK;
        grid[5][7] = &bR2;
        grid[6][7] = &bN2;
        grid[7][7] = &bC2;

        grid[0][6] = &bP1;
        grid[1][6] = &bP2;
        grid[2][6] = &bP3;
        grid[3][6] = &bP4;
        grid[4][6] = &bP5;
        grid[5][6] = &bP6;
        grid[6][6] = &bP7;
        grid[7][6] = &bP8;

    }






    bool ChessBoard::evaluatePath(int* path)
    {
        return false;
    }






    void ChessBoard::move(int pos1, int pos2, int move1, int move2, ChessPiece::team_type inTeamType)
    {
        if (move1 >= BOARD_SIZE || move2 >= BOARD_SIZE) {
            throw BoundsError();
        }
        else if (grid[pos1][pos2]->getTeamType() != inTeamType) {
            throw TurnMoveError();
        }
        else if (grid[move1][move2]->getTeamType() == inTeamType) {
            throw IlegalMoveError();
        }
        else if (pos1 == move1 && pos2 == move2) {
            throw NoTurnPassError();
        }
        else if (grid[pos1][pos2] == nullptr) { // !!!! not sure how to resolve the warning on this line
            throw EmptySquareError();
        }
        else {

            try {
                int* path = (grid[pos1][pos2]->setPosition(move1, move2));    // SetPosition may throw an ex
                bool clearPath = true;
                // if path is nullptr, but no exception was thrown yet, we have either
                // a knight or piece that did not traverse any squares to reach the destination
                if (path != nullptr) {
                    // otherwise we must check that the path positions in grid do not 
                    // point to an ChessPiece object to verify to valid move 
                    int i = 0 ;
                    
                    while (clearPath && path[i] != -1) {

                        int nextCol = path[2 * i];
                        int nextRow = path[2 * i + 1];
                        if (grid[nextCol][nextRow] != nullptr) {
                            clearPath = false;
                        }
                        i++;
                    }
                    delete[] path;
                }

                if (!clearPath) {
                    throw IlegalMoveError();
                }
            }
            catch (ChessPiece::PieceMoveError e) {
                throw ChessPiece::PieceMoveError();
            }
        }
    }






    int ChessBoard::remove(int pos1, int pos2)
    {
        if (grid[pos1][pos2] != nullptr) {
            
            // later could allocate pieces dynamically
            // and delete when removed from board
            grid[pos1][pos2] = nullptr;
            
            return 1;   // success
        }
        
        return 0;   // it was a nullptr
    }

}  // closes namespace


