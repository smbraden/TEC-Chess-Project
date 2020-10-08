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
        // isPiece() is checked in move(),  but getTeam() has the precondition
        if (isPiece(pos1, pos2))    // that the object at pos1, po2 is real
            if (getTeam(pos1, pos2) == ChessPiece::team_type::white)
                move(pos1, pos2, move1, move2, ChessPiece::team_type::white);
            else
                throw TurnMoveError();
        else
            throw EmptySquareError();

    }







    void ChessBoard::moveBlack(int pos1, int pos2, int move1, int move2)
    {
        if(isPiece(pos1, pos2))
            if (getTeam(pos1, pos2) == ChessPiece::team_type::black)
                move(pos1, pos2, move1, move2, ChessPiece::team_type::black);
            else
                throw TurnMoveError();
        else
            throw EmptySquareError();
    }






    
    ChessPiece::team_type ChessBoard::getTeam(int pos1, int pos2) const
    {
        assert(isPiece(pos1, pos2));
        return grid[pos1][pos2]->getTeamType();
    }
    




    
    ChessPiece::piece_type ChessBoard::getPiece(int pos1, int pos2) const
    {
        assert(isPiece(pos1, pos2));
        return grid[pos1][pos2]->getPieceType();
    }
    




    

    void ChessBoard::printBoard() const
    {   
       
        int row_label = 8;
        
        // upper column labels
        std::cout << "  ";
        for (char col_label = 'a'; col_label < 'i'; col_label++)
            std::cout << col_label << "  ";
        std::cout << endl;

        for (int row = (BOARD_SIZE - 1); row >= 0; row--) { //black-oriented: (int row = 0; row < BOARD_SIZE; row++)
            cout << row_label << " ";   // row labels
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






    void ChessBoard::initPieces()
    {
        // instantiate and map the white team
        grid[0][0] = new Rook(0, 0, ChessPiece::team_type::white);
        grid[1][0] = new Knight(1, 0, ChessPiece::team_type::white);
        grid[2][0] = new Bishop(2, 0, ChessPiece::team_type::white);
        grid[3][0] = new Queen(3, 0, ChessPiece::team_type::white);
        grid[4][0] = new King(4, 0, ChessPiece::team_type::white);
        grid[5][0] = new Bishop(5, 0, ChessPiece::team_type::white);
        grid[6][0] = new Knight(6, 0, ChessPiece::team_type::white);
        grid[7][0] = new Rook(7, 0, ChessPiece::team_type::white);

        // white pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
            grid[i][1] = new Pawn(i, 1, ChessPiece::team_type::white);
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





    // if path is nullptr, then there was no path (ie, knight or single move)
    void ChessBoard::evaluatePath(int* path) const
    {
        if (path != nullptr) {
            int i = 0;
            int x = path[2 * i];
            int y = path[2 * i + 1];
            
            while (x != -1 && y != -1 && i < (MAX_PATH * 2)) {
                
                assert(x < BOARD_SIZE && y < BOARD_SIZE && x >= 0 && y >= 0);
                if (grid[x][y] != nullptr) {    // if an object is in path 
                    delete [] path;
                    path = nullptr;
                    
                    throw IndirectPathError();
                }

                i++;
                x = path[2 * i];
                y = path[2 * i + 1];
            }
            delete [] path;
            path = nullptr;
        }
    }





    // inTeam is the team whose turn it is to move
    void ChessBoard::move(int pos1, int pos2, int move1, int move2, ChessPiece::team_type inTeamType)
    {
        if (move1 >= BOARD_SIZE || move2 >= BOARD_SIZE || pos1 >= BOARD_SIZE || pos2 >= BOARD_SIZE || 
                                                    move1 < 0 || move2 < 0 || pos1 < 0 || pos2 < 0) {
            throw BoundsError();
        }
        else if (!isPiece(pos1, pos2)) { // moving a non-exsistent piece   
            throw EmptySquareError();
        }
        else if (getTeam(pos1, pos2) != inTeamType) {   // player whose turn it is, is moving the opponent's piece
            throw TurnMoveError();
        }
        else if (pos1 == move1 && pos2 == move2) {      // the source is the destination
            throw NoTurnPassError();
        }
        else if (isPiece(move1, move2) && getTeam(move1, move2) == inTeamType) {    // destination occupied by a piece
            throw SelfCapturError();                                                // belonging to the moving player
        }
        else {  // basic rules have been followed. Now, are the rules followed for the specific piece?

            try {
                // Pawn moves require extra information from the board
                if (getPiece(pos1, pos2) == ChessPiece::piece_type::pawn) {
                    int* path = validPawnMove(pos1, pos2, move1, move2);                // might throw piece move, or ilegal move error
                    evaluatePath(path);
                }
                else {  // For all the other pieces    
                    int* path = grid[pos1][pos2]->validMove(move1, move2);    // might throw a piece move error
                    evaluatePath(path);                                         // might throw an ilegal move error
                }
            }
            catch (ChessPiece::PieceMoveError e) {
                throw ChessPiece::PieceMoveError();
            }
            catch (IndirectPathError e) {
                throw IndirectPathError();
            }

            resetEnPassant(pos1, pos2); // resets all EnPassant to false, except the 
                                        // most recently moved piece            
            
            // SelfCapture block should ensure that getTeam(move1, move2) != getTeam(pos1, pos2)
            if (isPiece(move1, move2))
                remove(move1, move2);
            grid[move1][move2] = grid[pos1][pos2];          // map the object with the destination coordinate
            grid[pos1][pos2]->setPosition(move1, move2);    // set the object's internal position
            grid[pos1][pos2] = nullptr;                     // set previous coordinate to empty
        }
    }






    void ChessBoard::remove(int pos1, int pos2)
    {
        if (grid[pos1][pos2] != nullptr) {
            ChessPiece* objPtr = grid[pos1][pos2];
            delete objPtr;
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
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::rook) {
                    grid[i][j] = new Rook(i, j, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::knight) {
                    grid[i][j] = new Knight(i, j, grid[i][j]->getTeamType());
                }
                else if (grid[i][j]->getPieceType() == ChessPiece::piece_type::bishop) {
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







    int* ChessBoard::validPawnMove(int pos1, int pos2, int move1, int move2)
    {

        assert(getPiece(pos1, pos2) == ChessPiece::piece_type::pawn);   // terminate if not pawn
                                                                        // isPiece(pos1, pos2) is implied
        int* path = nullptr;
        
        if (isCapture(pos1, pos2, move1, move2) || 
                enPassant(pos1, pos2, move1, move2) ||
                    simpleAdvance(pos1, pos2, move1, move2)) {   
            
            try {
                path = grid[pos1][pos2]->validMove(move1, move2);
            }
            catch (ChessPiece::PieceMoveError e) {
                throw ChessPiece::PieceMoveError();
            }
        }
        else {
            throw ChessPiece::PieceMoveError();     // it's invalid move if neither
        }                                           // SimpleAdvance(), nor isCapture()

        return path;
    }






    // helper function to pawnMove()
    bool ChessBoard::isCapture(int pos1, int pos2, int move1, int move2)
    {
        /* if opponent occupies destination */
        if (isPiece(move1, move2) && getTeam(move1, move2) != getTeam(pos1, pos2)) { 
            /*single diagonal move, white piece*/
            if (getTeam(pos1, pos2) == ChessPiece::team_type::white &&
                move2 == pos2 + 1 && abs(pos1 - move1) == 1) {
                return true;
            }
            /*single diagonal move, black piece*/
            else if (getTeam(pos1, pos2) == ChessPiece::team_type::black &&
                pos2 == move2 + 1 && abs(pos1 - move1) == 1) {
                return true;
            }
        }

        return false; // function could be one if statement, but w/ annoyingly long condition
    }






    // helper function to pawnMove()
    bool ChessBoard::simpleAdvance(int pos1, int pos2, int move1, int move2)
    {
        if (!isPiece(move1, move2) && pos1 == move1)    // destination is empty square, 
            return true;                                // and same column as current position
        return false;                                   // setPosition() takes care of the specifics
    }






    bool ChessBoard::enPassant(int pos1, int pos2, int move1, int move2)
    {
        // if current position is one space ahead of the opponent's fifth rank,
        // and if either of the objects to the left or right has enPassant == true 
            // if move is to the diagonal, 'behind' the opponent (pseudo-capture),
            // then return true
        // else, return false

        return true;
    }






    void ChessBoard::resetEnPassant(int pos1, int pos2)
    {
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {  // for all pawns that are not the current piece
                if (!(c == pos1 && r == pos2) && getPiece(pos1, pos2) == ChessPiece::piece_type::pawn) {
                    grid[pos1][pos2]->setEnPassant(false);  // gotta add this enPassant business to the base class
                }
            }
        }
    }





}  // closes namespace


