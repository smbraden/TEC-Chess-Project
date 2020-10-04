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
#include "ChessBoard.h"

using namespace std;

namespace chess {
    
    ChessBoard::ChessBoard()
    {
        // initialize a "blank" grid
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






    void ChessBoard::moveWhite(int pos1, int pos2, int move1, int move2)
    {
        if (isPiece(pos1, pos2))
            if (grid[pos1][pos2]->getTeamType() == ChessPiece::team_type::white)
                move(pos1, pos2, move1, move2, ChessPiece::team_type::white);
            else
                throw TurnMoveError();
        else
            throw EmptySquareError();

    }







    void ChessBoard::moveBlack(int pos1, int pos2, int move1, int move2)
    {
        if(isPiece(pos1, pos2))
            if (grid[pos1][pos2]->getTeamType() == ChessPiece::team_type::black)
                move(pos1, pos2, move1, move2, ChessPiece::team_type::black);
            else
                throw TurnMoveError();
        else
            throw EmptySquareError();
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
                                                            // for user from black perspective of board
        for (int row = (BOARD_SIZE - 1); row >= 0; row--) { // (int row = 0; row < BOARD_SIZE; row++)
            for (int col = 0; col < BOARD_SIZE; col++) {

                if (grid[col][row] == nullptr)
                    std::cout << "__";
                else {
                    ChessPiece::team_type team = grid[col][row]->getTeamType();
                    ChessPiece::piece_type piece = grid[col][row]->getPieceType();
                    std::cout << static_cast<std::underlying_type<ChessPiece::team_type>::type>(team)
                            << static_cast<std::underlying_type<ChessPiece::team_type>::type>(piece);
                    // cast the team and piece types beack to underlying types for printing
                }
                std::cout << "  ";
            }
            std::cout << endl;
            // uncomment/comment out this block for more/less spaces in board console print
            /*
            for (int i = 0; i < 32; i++)
                std::cout << " ";
            std::cout << endl;
            */
        }
    }







    void ChessBoard::initPieces()
    {
        // instantiate and map the white team
        grid[0][0] = new Rook(0, 0);
        grid[1][0] = new Knight(1, 0);
        grid[2][0] = new Bishop(2, 0);
        grid[3][0] = new Queen(3, 0);
        grid[4][0] = new King(4, 0);
        grid[5][0] = new Bishop(5, 0);
        grid[6][0] = new Knight(6, 0);
        grid[7][0] = new Rook(7, 0);

        // white pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
            grid[i][1] = new Pawn(i, 1);
        }

        // instantiate and map the black team pieces
        grid[0][7] = new Rook(0, 7, ChessPiece::team_type::black);
        grid[1][7] = new Knight(1, 7, ChessPiece::team_type::black);
        grid[2][7] = new Bishop(2, 7, ChessPiece::team_type::black);
        grid[3][7] = new Queen(3, 7, ChessPiece::team_type::black);
        grid[4][7] = new King(4, 7, ChessPiece::team_type::black);
        grid[5][7] = new Bishop(5, 7, ChessPiece::team_type::black);
        grid[6][7] = new Knight(6, 7, ChessPiece::team_type::black);
        grid[7][7] = new Rook(7, 7, ChessPiece::team_type::black);
               
        // black pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
            grid[i][6] = new Pawn(i, 6, ChessPiece::team_type::black);
        }
    }





    // if the path is nullptr, then there was no path (ie, knight or single move)
    void ChessBoard::evaluatePath(int* path) const
    {
        if (path != nullptr) {
            int i = 0;
            while (path[2 * i] != -1 && path[2 * i + 1] != -1) {
                if (grid[2 * i][2 * i + 1] != nullptr) {
                    delete path;
                    path = nullptr;
                    //return false;
                    throw IlegalMoveError();
                }
                i++;
            }

            delete path;
            path = nullptr;
        }
        // return true;
    }





    
    void ChessBoard::move(int pos1, int pos2, int move1, int move2, ChessPiece::team_type inTeamType)
    {
        if (move1 >= BOARD_SIZE || move2 >= BOARD_SIZE || pos1 >= BOARD_SIZE || pos2 >= BOARD_SIZE) {
            throw BoundsError();
        }
        else if (!isPiece(pos1, pos2)) {
            throw EmptySquareError();
        }
        else if (grid[pos1][pos2]->getTeamType() != inTeamType) {
            throw TurnMoveError();
        }
        else if (grid[move1][move2] != nullptr && grid[move1][move2]->getTeamType() == inTeamType) {    
            throw IlegalMoveError();
        }
        else if (pos1 == move1 && pos2 == move2) {  // this might be redundant with the previous condition
            throw NoTurnPassError();
        }
        else {

            try {
                int* path = (grid[pos1][pos2]->setPosition(move1, move2));    // might throw a piece move error
                evaluatePath(path);                         // might throw an ilegal move error
                grid[move1][move2] = grid[pos1][pos2];     // map the object from the new board coordinate
                grid[pos1][pos2] = nullptr;
            }
            catch (ChessPiece::PieceMoveError e) {
                throw ChessPiece::PieceMoveError();
            }
            catch (IlegalMoveError e) {
                throw IlegalMoveError();
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
                    grid[i][j] = new Pawn(i, j, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::castle) {
                    grid[i][j] = new Rook(i, j, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::knight) {
                    grid[i][j] = new Knight(i, j, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::rook) {
                    grid[i][j] = new Bishop(i, j, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::king) {
                    grid[i][j] = new King(i, j, grid[i][j]->getTeamType());
                }
                else {  // if (grid[i][j]->getPieceType() == ChessPiece::piece_type::queen) 
                    grid[i][j] = new Queen(i, j, grid[i][j]->getTeamType());
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


