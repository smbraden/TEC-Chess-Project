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
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                grid[j][i] = nullptr;
              
        // instantiate the pieces and map them on grid
        initPieces();
    }






    ChessBoard::ChessBoard(const ChessBoard& arg)
    {
        copy(arg);
    }
    






    ChessBoard::~ChessBoard()
    {
        clear();
    }
    





    ChessBoard ChessBoard::operator=(const ChessBoard right)
    {
        if (this != &right) {
            clear();
            copy(right);
        }

        return *this;
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

                if (grid[col][row] == nullptr)
                    cout << "__";
                else
                    cout << grid[col][row]->getTeamType() << grid[col][row]->getPieceType();
                cout << " ";
            }
            cout << endl;
        }
    }







    void ChessBoard::initPieces()
    {
        // set the white team
        // Castle wC1(0, 0);
        Castle* wC1 = new Castle(0, 0);
        Knight* wN1 = new Knight(1, 0);
        Rook* wR1 = new Rook(2, 0);
        Queen* wQ = new Queen(3, 0);
        King* wK = new King(4, 0);
        Rook* wR2 = new Rook(5, 0);
        Knight* wN2 = new Knight(6, 0);
        Castle* wC2 = new Castle(7, 0);

        // map the white pieces on grid
        grid[0][0] = wC1;
        grid[1][0] = wN1;
        grid[2][0] = wR1;
        grid[3][0] = wQ;
        grid[4][0] = wK;
        grid[5][0] = wR2;
        grid[6][0] = wN2;
        grid[7][0] = wC2;


        for (int i = 0; i < BOARD_SIZE; i++) {
            grid[i][1] = new Pawn(i, 1);
        }

        // instantiate the black team pieces
        Castle* bC1 = new Castle(0, 7, ChessPiece::black);
        Knight* bN1 = new Knight(1, 7, ChessPiece::black);
        Rook* bR1 = new Rook(2, 7, ChessPiece::black);
        Queen* bQ = new Queen(3, 7, ChessPiece::black);
        King* bK = new King(4, 7, ChessPiece::black);
        Rook* bR2 = new Rook(5, 7, ChessPiece::black);
        Knight* bN2 = new Knight(6, 7, ChessPiece::black);
        Castle* bC2 = new Castle(7, 7, ChessPiece::black);

        // map the black pieces on grid
        grid[0][7] = bC1;
        grid[1][7] = bN1;
        grid[2][7] = bR1;
        grid[3][7] = bQ;
        grid[4][7] = bK;
        grid[5][7] = bR2;
        grid[6][7] = bN2;
        grid[7][7] = bC2;

        for (int i = 0; i < BOARD_SIZE; i++) {
            grid[i][6] = new Pawn(i, 6, ChessPiece::black);
        }
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






    void ChessBoard::remove(int pos1, int pos2)
    {
        if (grid[pos1][pos2] != nullptr) {
            
            delete grid[pos1][pos2];
            grid[pos1][pos2] = nullptr;
        }
    }







    void ChessBoard::clear()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                remove(i, j);
    }






    // precodition: the board has been cleared
    void ChessBoard::copy(const ChessBoard arg)
    {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (arg.grid[i][j] == nullptr)
                    grid[i][j] = nullptr;
                else if (grid[i][j]->getPieceType() == ChessPiece::pawn) {
                    grid[i][j] = new Pawn(j, i, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::castle) {
                    grid[i][j] = new Castle(j, i, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::knight) {
                    grid[i][j] = new Knight(j, i, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::rook) {
                    grid[i][j] = new Rook(j, i, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::king) {
                    grid[i][j] = new King(j, i, grid[i][j]->getTeamType());
                }
                else {  // if (grid[i][j]->getPieceType() == ChessPiece::queen) 
                    grid[i][j] = new Queen(j, i, grid[i][j]->getTeamType());
                }
            }
        }
    }

}  // closes namespace


