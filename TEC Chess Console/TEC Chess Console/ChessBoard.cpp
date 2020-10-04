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
        move(pos1, pos2, move1, move2, ChessPiece::team_type::white);
        return 0;
    }







    int ChessBoard::moveBlack(int pos1, int pos2, int move1, int move2)
    {
        move(pos1, pos2, move1, move2, ChessPiece::team_type::black);
        return 0;
    }






    
    ChessPiece::team_type ChessBoard::getTeam(int pos1, int pos2) const
    {
        if (isPiece(pos1, pos2))
            return grid[pos1][pos2]->getTeamType();
        return ChessPiece::team_type::none;
    }
    




    
    ChessPiece::piece_type ChessBoard::getPiece(int pos1, int pos2) const
    {
        if (isPiece(pos1, pos2))
            return grid[pos1][pos2]->getPieceType();
        return ChessPiece::piece_type::none;
    }
    




    

    void ChessBoard::printBoard() const
    {
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {

                if (grid[col][row] == nullptr)
                    cout << "__";
                else {
                    ChessPiece::team_type team = grid[col][row]->getTeamType();
                    ChessPiece::piece_type piece = grid[col][row]->getPieceType();
                    cout << static_cast<underlying_type<ChessPiece::team_type>::type>(team) 
                            << static_cast<underlying_type<ChessPiece::team_type>::type>(piece);
                    // cast teh team and piece types beack to underlying types for printing
                }
                cout << " ";
            }
            cout << endl;
        }
    }







    void ChessBoard::initPieces()
    {
        // instantiate and map the white team
        grid[0][0] = new Castle(0, 0);
        grid[1][0] = new Knight(1, 0);
        grid[2][0] = new Rook(2, 0);
        grid[3][0] = new Queen(3, 0);
        grid[4][0] = new King(4, 0);
        grid[5][0] = new Rook(5, 0);
        grid[6][0] = new Knight(6, 0);
        grid[7][0] = new Castle(7, 0);

        // white pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
            grid[i][1] = new Pawn(i, 1);
        }

        // instantiate and map the black team pieces
        grid[0][7] = new Castle(0, 7, ChessPiece::team_type::black);
        grid[1][7] = new Knight(1, 7, ChessPiece::team_type::black);
        grid[2][7] = new Rook(2, 7, ChessPiece::team_type::black);
        grid[3][7] = new Queen(3, 7, ChessPiece::team_type::black);
        grid[4][7] = new King(4, 7, ChessPiece::team_type::black);
        grid[5][7] = new Rook(5, 7, ChessPiece::team_type::black);
        grid[6][7] = new Knight(6, 7, ChessPiece::team_type::black);
        grid[7][7] = new Castle(7, 7, ChessPiece::team_type::black);
               
        // black pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
            grid[i][6] = new Pawn(i, 6, ChessPiece::team_type::black);
        }
    }






    void ChessBoard::evaluatePath(int* path) const
    {
        int i = 0;
        while (path[2 * i] != -1 && path[2 * i + 1] != -1) {
            if (grid[2*i][2*i+1] != nullptr) {
                delete path;
                path = nullptr;
                //return false;
                throw IlegalMoveError();
            }
            i++;
        }

        delete path;
        path = nullptr;
        // return true;
    }





    //
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
        else if (isPiece(pos1, pos2)) {
            throw EmptySquareError();
        }
        else {

            try {
                int* path = (grid[pos1][pos2]->setPosition(move1, move2));    // SetPosition may throw an ex
                bool clearPath = true;
                evaluatePath(path);     // may throw an ilegal move error
            }
            catch (ChessPiece::PieceMoveError e) {
                throw ChessPiece::PieceMoveError();
            }
            catch (ChessBoard::IlegalMoveError e) {
                throw ChessBoard::IlegalMoveError();
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
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::pawn) {
                    grid[i][j] = new Pawn(j, i, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::castle) {
                    grid[i][j] = new Castle(j, i, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::knight) {
                    grid[i][j] = new Knight(j, i, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::rook) {
                    grid[i][j] = new Rook(j, i, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::king) {
                    grid[i][j] = new King(j, i, grid[i][j]->getTeamType());
                }
                else {  // if (grid[i][j]->getPieceType() == ChessPiece::piece_type::queen) 
                    grid[i][j] = new Queen(j, i, grid[i][j]->getTeamType());
                }
            }
        }
    }







    bool ChessBoard::isPiece(int inCol, int inRow) const
    {
        if (grid[inCol][inRow] != nullptr)
            return true;
        return false;
    }

}  // closes namespace


