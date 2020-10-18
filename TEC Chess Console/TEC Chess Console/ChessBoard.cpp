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

#define inBounds4(a, b, c, d) (a >= 0 && b >= 0 && c >= 0 && d >= 0 &&  \
                            a < BOARD_SIZE&& b < BOARD_SIZE&& c < BOARD_SIZE&& d < BOARD_SIZE)
#define inBounds2(a, b) (a < BOARD_SIZE && b < BOARD_SIZE && a >= 0 && b >= 0 )

using namespace std;

namespace chess {



    ChessBoard::ChessBoard()
    {
        wKingRow = 0;
        wKingCol = 4;
        bKingRow = 7;
        bKingCol = 4;
        checkmateStatus = false;
        Winner = ChessPiece::team_type::nullType;

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

        //black-oriented would be: (int row = 0; row < BOARD_SIZE; row++)
        for (int row = (BOARD_SIZE - 1); row >= 0; row--) {
            cout << row_label << " ";   // row labels
            for (int col = 0; col < BOARD_SIZE; col++) {

                if (grid[col][row] == nullptr)
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








    bool ChessBoard::getCheckmateStatus()
    {
        return checkmateStatus;
    }






    void ChessBoard::setCheckmateStatus(bool arg)
    {
        checkmateStatus = arg;
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
        grid[0][0] = new Rook(0, 0, ChessPiece::team_type::white);
        grid[1][0] = new Knight(1, 0, ChessPiece::team_type::white);
        grid[2][0] = new Bishop(2, 0, ChessPiece::team_type::white);
        grid[3][0] = new Queen(3, 0, ChessPiece::team_type::white);
        grid[4][0] = new King(4, 0, ChessPiece::team_type::white);
        grid[5][0] = new Bishop(5, 0, ChessPiece::team_type::white);
        grid[6][0] = new Knight(6, 0, ChessPiece::team_type::white);
        grid[7][0] = new Rook(7, 0, ChessPiece::team_type::white);

        // white pawns
        Pawn* pPtr =nullptr;
        for (int i = 0; i < BOARD_SIZE; i++) {
            grid[i][1] = new Pawn(i, 1, ChessPiece::team_type::white, false);
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
            grid[i][6] = new Pawn(i, 6, ChessPiece::team_type::black, false);
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
                
                assert(inBounds2(x, y));
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






    // Note:    inTeam is the team whose turn it is to move
    void ChessBoard::move(int pos1, int pos2, int move1, int move2, ChessPiece::team_type inTeamType)
    {
        if (!inBounds4(pos1, pos2, move1, move2)){
            throw BoundsError();
        }
        else if (!isPiece(pos1, pos2))  // moving a non-exsistent piece   
            throw EmptySquareError();
        else if (getTeam(pos1, pos2) != inTeamType)     // wrong team being move
            throw TurnMoveError();
        else if (pos1 == move1 && pos2 == move2)        // the source is the destination
            throw NoTurnPassError();
        else if (isPiece(move1, move2) && getTeam(move1, move2) == inTeamType)  // destination occupied by a piece
            throw SelfCapturError();                                            // belonging to the moving player
        else {  // basic rules have been followed. Now, are the rules followed for the specific piece?

            ChessBoard tempBoard = *this;

            try {
                
                if (getPiece(pos1, pos2) == ChessPiece::piece_type::pawn) { // Pawns have special rules to assess
                    evaluatePath(validPawnMove(pos1, pos2, move1, move2));  // might throw piece or ilegal move error
                    pawnPromote(pos1, pos2, move1, move2);                  // if moving to 8th rank move, promote pawn
                }
                else if (getPiece(pos1, pos2) == ChessPiece::piece_type::king) {
                    if (!Castle(pos1, pos2, move1, move2)) {                
                        evaluatePath(grid[pos1][pos2]->validMove(move1, move2));
                        ((King*)grid[pos1][pos2])->setCastleStatus(false);
                    }
                    setKing(pos1, pos2, move1, move2);
                }
                else {  // all the other pieces
                    evaluatePath(grid[pos1][pos2]->validMove(move1, move2));// throws PieceMoveError, IlegalMoveError
                    if (getPiece(pos1, pos2) == ChessPiece::piece_type::rook)
                        ((Rook*)grid[pos1][pos2])->setCastleStatus(false);
                }

            }
            catch (ChessPiece::PieceMoveError e) {
                throw ChessPiece::PieceMoveError();
            }
            catch (IndirectPathError e) {
                throw IndirectPathError();
            }

            // pawnPromote(pos1, pos2, move1, move2);  // if moving to 8th rank move, promote pawn
            setPiece(pos1, pos2, move1, move2);     // set new pos on grid and internally, remove captures
            resetEnPassant(move1, move2);           // resets all EnPassant to false, except a moved pawn
            
            if(isCheck(inTeamType)) {   // throws CheckError if move results in Check
                *this = tempBoard;
                throw CheckError();
            }
        }
    }






    void ChessBoard::setPiece(int pos1, int pos2, int move1, int move2)
    {
        if (isEnPassant(pos1, pos2, move1, move2))
            remove(move1, pos2);
        else if (isPiece(move1, move2))
            remove(move1, move2);

        grid[move1][move2] = grid[pos1][pos2];          // map the object with the destination coordinate
        grid[pos1][pos2]->setPosition(move1, move2);    // set the object's internal position
        grid[pos1][pos2] = nullptr;                     // set previous coordinate to empty
    }






    void ChessBoard::remove(int x, int y)
    {
        if (grid[x][y] != nullptr) {
            ChessPiece* objPtr = grid[x][y];                      
            delete objPtr;                      // destroy the object
            grid[x][y] = nullptr;               // set the grid square to nullptr
        }
    }






    void ChessBoard::clear()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                remove(i, j);
    }






    // Precodition:     The board has been cleared
    void ChessBoard::copy(const ChessBoard& arg)
    {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                
                if (arg.grid[i][j] == nullptr)
                    grid[i][j] = nullptr;
                else if (arg.getPiece(i, j) == ChessPiece::piece_type::pawn) {
                    bool passVal = ((Pawn*)arg.grid[i][j])->getEnPassant();
                    grid[i][j] = new Pawn(i, j, arg.getTeam(i, j), passVal);
                }
                else if (arg.getPiece(i, j) == ChessPiece::piece_type::rook) {
                    grid[i][j] = new Rook(i, j, arg.getTeam(i, j));
                }
                else if (arg.getPiece(i, j) == ChessPiece::piece_type::knight) {
                    grid[i][j] = new Knight(i, j, arg.getTeam(i, j));
                }
                else if (arg.getPiece(i, j) == ChessPiece::piece_type::bishop) {
                    grid[i][j] = new Bishop(i, j, arg.getTeam(i, j));
                }
                else if (arg.getPiece(i, j) == ChessPiece::piece_type::king) {
                    grid[i][j] = new King(i, j, arg.getTeam(i, j));
                }
                else {  // if (grid[i][j]->getPieceType() == ChessPiece::piece_type::queen) 
                    grid[i][j] = new Queen(i, j, arg.getTeam(i, j));
                }
            }
        }

        wKingRow = arg.wKingRow;
        wKingCol = arg.wKingCol;
        bKingRow = arg.bKingRow;
        bKingCol = arg.bKingCol;
        Winner = arg.Winner;
        checkmateStatus = arg.checkmateStatus;
    }







    bool ChessBoard::isPiece(int inCol, int inRow) const
    {
        if (inBounds2(inCol, inRow) && grid[inCol][inRow] != nullptr)
            return true;
        return false;
    }







    int* ChessBoard::validPawnMove(int pos1, int pos2, int move1, int move2) const
    {

        assert(getPiece(pos1, pos2) == ChessPiece::piece_type::pawn);   // terminate if not pawn
                                                                        // isPiece(pos1, pos2) is implied
        int* path = nullptr;
        
        if (isCapture(pos1, pos2, move1, move2) || 
                isEnPassant(pos1, pos2, move1, move2) ||
                    simpleAdvance(pos1, pos2, move1, move2)) {   
            
            try {
                path = grid[pos1][pos2]->validMove(move1, move2);
            }
            catch (ChessPiece::PieceMoveError e) {
                throw ChessPiece::PieceMoveError();
            }
        }
        else {
            throw ChessPiece::PieceMoveError();     // it's an invalid move if neither
        }                                           // SimpleAdvance(), isCapture(), nor isEnPassant()

        return path;
    }






    // Purpose:     Helper function to pawnMove()
    bool ChessBoard::isCapture(int pos1, int pos2, int move1, int move2) const
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






    // Purpose:     Helper function to pawnMove()
    bool ChessBoard::simpleAdvance(int pos1, int pos2, int move1, int move2) const
    {
        if (!isPiece(move1, move2) && pos1 == move1)    // destination is empty square, 
            return true;                                // and same column as current position
        return false;                                   // setPosition() takes care of the specifics
    }






    // Purpose:         Checks for a valid En Passant move
    // Precondition:    The move  and current position are in bounds
    // Return:          True if a valid En Passant move
    //                  False if not En Passant move, or not Pawn
    bool ChessBoard::isEnPassant(int pos1, int pos2, int move1, int move2) const
    {
        assert(inBounds4(pos1, pos2, move1, move2));

        if (isPiece(pos1, pos2) && getPiece(pos1, pos2) != ChessPiece::piece_type::pawn) {
            return false;
        }
        if (isPiece(pos1, pos2) && getTeam(pos1, pos2) == ChessPiece::team_type::white) {
            if (pos2 != 4 || move2 != 5)    // if current position is not fifth rank
                return false;               // and moving to the proper row
            // if either of the objects to the left or right has enPassant == true
            else if (move1 == (pos1 - 1) && isPiece(pos1 - 1, pos2) && ((Pawn*)grid[pos1 - 1][pos2])->getEnPassant())
                return true;
            else if (move1 == (pos1 + 1) && isPiece(pos1 + 1, pos2) && ((Pawn*)grid[pos1 + 1][pos2])->getEnPassant())
                return true;
        }
        else {  // if (getTeam(pos1, pos2) == ChessPiece::team_type::black)
            if (pos2 != 3 || move2 != 2)    // if current position is not fifth rank
                return false;               // and moving to the proper row
            // if either of the objects to the left or right has enPassant == true
            else if (move1 == (pos1 - 1) && isPiece(pos1 - 1, pos2) && ((Pawn*)grid[pos1 - 1][pos2])->getEnPassant())
                return true;
            else if (move1 == (pos1 + 1) && isPiece(pos1 + 1, pos2) && ((Pawn*)grid[pos1 + 1][pos2])->getEnPassant())
                return true;
        }

        return false;
    }







    // IN PROGRESS: Promotion with options needs implementing, currently promotes to queen
    void ChessBoard::pawnPromote(int pos1, int pos2, int move1, int move2)
    {
        assert(inBounds4(pos1, pos2, move1, move2));
        ChessPiece::team_type team = getTeam(pos1, pos2);

        if (isPiece(pos1, pos2) && getPiece(pos1, pos2) == ChessPiece::piece_type::pawn) {
            if ((team == ChessPiece::team_type::white && move2 == 7) ||
                (team == ChessPiece::team_type::black && move2 == 0)) {
                // later, promote with options HERE
                Queen* qPtr = new Queen(pos1, pos2, team);
                remove(pos1, pos2);
                grid[pos1][pos2] = qPtr;
            }
        }
    }





    
    // Purpose:         Resets all enPassant to false, except the moving piece, if Pawn
    // Precondition:    The move  and current position are in bounds
    void ChessBoard::resetEnPassant(int pos1, int pos2)
    {
        //Pawn* ptr = nullptr;

        for (int c = 0; c < BOARD_SIZE; c++) {
            for (int r = 0; r < BOARD_SIZE; r++) {      //  !(pos1 == c && pos2 == r)
                if (isPiece(c, r) && getPiece(c, r) == ChessPiece::piece_type::pawn) {
                    ((Pawn*)grid[c][r])->setEnPassant(false);
                }
            }
        }

        if (getPiece(pos1, pos2) == ChessPiece::piece_type::pawn) {     // This might need more specific conditions
            ((Pawn*)grid[pos1][pos2])->setEnPassant(true);
        }
    }






    bool ChessBoard::isCheck(ChessPiece::team_type team) const
    {
        int kRow;
        int kCol;
        
        if (team == ChessPiece::team_type::white) {
            kRow = wKingRow;
            kCol = wKingCol;
        }
        else {  // if (getTeam(pos1, pos2) == ChessPiece::team_type::blakc)
            kRow = bKingRow;
            kCol = bKingCol;
        }

        // if there is attacking queen or rook from laterals
        if (checkLaterals(team, kCol, kRow))
            return true;
        // if threatened by pawn from corners
        else if (checkCorners(team, kCol, kRow))
            return true;
        // else if there is an attacking queen or bishop in diagonals
        else if (checkDiagonals(team, kCol, kRow))
            return true;
        // else if there are any attacking knights
        else if (checkKnight(team, kCol, kRow))
            return true;
        
        return false;
    }






    bool ChessBoard::isCheck(ChessPiece::team_type team, int pos1, int pos2) const
    {
        // if there is attacking queen or rook from laterals
        if (checkLaterals(team, pos1, pos2))
            return true;
        // if threatened by pawn from corners
        else if (checkCorners(team, pos1, pos2))
            return true;
        // else if there is an attacking queen or bishop in diagonals
        else if (checkDiagonals(team, pos1, pos2))
            return true;
        // else if there are any attacking knights
        else if (checkKnight(team, pos1, pos2))
            return true;

        return false;
    }






    bool ChessBoard::checkLaterals(ChessPiece::team_type kingTeam, int kCol, int kRow) const
    {
        if (singleLateral(kingTeam, kCol, kRow,  1, 0) ||
            singleLateral(kingTeam, kCol, kRow, -1, 0) ||
            singleLateral(kingTeam, kCol, kRow, 0,  1) ||
            singleLateral(kingTeam, kCol, kRow, 0, -1))
            return true;

        return false;
    }




    

    //    Precondition: Either colSign or rowSign is 0
    //                  Either colSign or RowSign is 1 or -1
    //                  kCol is the king's column
    //                  kRow is the king's row
    bool ChessBoard::singleLateral(ChessPiece::team_type kingTeam, int kCol, int kRow, int colSign, int rowSign) const
    {
        int nextCol = kCol + colSign;
        int nextRow = kRow + rowSign;

        while (inBounds2(nextCol, nextRow) && !isPiece(nextCol, nextRow)) {
            nextCol = nextCol + colSign;
            nextRow = nextRow + rowSign;
        }

        if (isPiece(nextCol, nextRow) && getTeam(nextCol, nextRow) != kingTeam) {
            if (getPiece(nextCol, nextRow) == ChessPiece::piece_type::queen
                || getPiece(nextCol, nextRow) == ChessPiece::piece_type::rook)
                return true;
            else if (getPiece(nextCol, nextRow) == ChessPiece::piece_type::king &&
                (abs(nextCol - kCol) == 1 || abs(nextRow - kRow) == 1))
                return true;
        }
        
        
        return false;
    }





    // if threatened by pawn
    bool ChessBoard::checkCorners(ChessPiece::team_type kingTeam, int kCol, int kRow) const
    {
        int left = kCol - 1;
        int right = kCol + 1;
        int pRow;

        pRow = (kingTeam == ChessPiece::team_type::white) ? (kRow + 1) : (kRow - 1);

        if ((isPiece(right, pRow) && getTeam(right, pRow) != kingTeam
            && getPiece(right, pRow) == ChessPiece::piece_type::pawn) ||
            (isPiece(left, pRow) && getTeam(left, pRow) != kingTeam
                && getPiece(left, pRow) == ChessPiece::piece_type::pawn))
            return true;

        return false;
    }





    
    // Precondition:    colSign and rowSign are 1 or -1
    bool ChessBoard::checkDiagonals(ChessPiece::team_type kingTeam, int kCol, int kRow) const
    {
        if (singleDiagonal(kingTeam, kCol, kRow, 1, -1) ||
            singleDiagonal(kingTeam, kCol, kRow, 1,  1) ||
            singleDiagonal(kingTeam, kCol, kRow, -1, 1) ||
            singleDiagonal(kingTeam, kCol, kRow, -1, -1))
           return true;

        return false; // if not threatened from diagonal by opponent queen or bishop
    }







    bool ChessBoard::singleDiagonal(ChessPiece::team_type kingTeam, int kCol, int kRow, int colSign, int rowSign) const
    {
        int nextCol = kCol + colSign;
        int nextRow = kRow + rowSign;

        while (inBounds2(nextCol, nextRow) && !isPiece(nextCol, nextRow)) {
            nextCol = nextCol + colSign;
            nextRow = nextRow + rowSign;
        }

        if (isPiece(nextCol, nextRow) && getTeam(nextCol, nextRow) != kingTeam ) {
            if (getPiece(nextCol, nextRow) == ChessPiece::piece_type::queen ||
                getPiece(nextCol, nextRow) == ChessPiece::piece_type::bishop)
                return true;
            else if (getPiece(nextCol, nextRow) == ChessPiece::piece_type::king && 
                abs(nextCol - kCol) == 1 && abs(nextRow - kRow) == 1)
                return true;
        }
        
        return false;
    }






    
    bool ChessBoard::checkKnight(ChessPiece::team_type kingTeam, int kCol, int kRow) const
    {
        // if threatened by an opponent knight
        if (singleKnight(kingTeam, kCol, kRow,  1,  2) || singleKnight(kingTeam, kCol, kRow,  1, -2) ||
            singleKnight(kingTeam, kCol, kRow, -1,  2) || singleKnight(kingTeam, kCol, kRow, -1, -2) ||
            singleKnight(kingTeam, kCol, kRow,  2,  1) || singleKnight(kingTeam, kCol, kRow, -2,  1) ||
            singleKnight(kingTeam, kCol, kRow,  2, -1) || singleKnight(kingTeam, kCol, kRow, -2, -1))
            return true;
        
        return false;
    }






    // Precondition: Either colSign or rowSign is in {2, -2} and,
    //               Either colSign or RowSign is in {1, -1}
    //               kCol is the king's column
    //               kRow is the king's row
    bool ChessBoard::singleKnight(ChessPiece::team_type kingTeam, int kCol, int kRow, int colSign, int rowSign) const
    {
        int col = kCol + colSign;
        int row = kRow + rowSign;

        if (isPiece(col, row) && getTeam(col, row) != kingTeam 
            && getPiece(col, row) == ChessPiece::piece_type::knight)
            return true;
        
        return false;
    }





    // Might be nice to add an exception throw embedded in this function
    // in order to provide feedback about the nature of the invalid move 
    // (ie, if the rook or king have been moved previously vs. a checked square in the path, etc)

    // Return:  true if a valid castling move
    // Post:    If invalid castle move, no change
    //          If valid castle move:
    //              - Both castling pieces have Piece.castle == false
    //              - The castling rook has been set to post-castling position
    //              - The king has not been placed in the new position, move() will reposition the king

    bool ChessBoard::Castle(int pos1, int pos2, int move1, int move2)
    {
        assert(isPiece(pos1, pos2));
        ChessPiece::team_type team = getTeam(pos1, pos2);

        // confirm the basic conditions
        if (getPiece(pos1, pos2) != ChessPiece::piece_type::king || !((King*)grid[pos1][pos2])->getCastleStatus() || isCheck(team))
            return false;
        
        if (team == ChessPiece::team_type::white) {
            if (move1 == 2 && move2 == 0) {
                if (isPiece(0, 0) && getPiece(0, 0) == ChessPiece::piece_type::rook && ((Rook*)grid[0][0])->getCastleStatus()) {
                    if (validCastlePath(4, 0, 0, 0)) {
                        ((Rook*)grid[0][0])->setCastleStatus(false);
                        ((King*)grid[4][0])->setCastleStatus(false);
                        setPiece(0, 0, 3, 0);
                        return true;
                    }
                }
            }
            else if(move1 == 6 && move2 == 0) {
                if (isPiece(7, 0) && getPiece(7, 0) == ChessPiece::piece_type::rook && ((Rook*)grid[7][0])->getCastleStatus()) {
                    if (validCastlePath(4, 0, 7, 0)) {
                        ((Rook*)grid[7][0])->setCastleStatus(false);
                        ((King*)grid[4][0])->setCastleStatus(false);
                        setPiece(7, 0, 5, 0);
                        return true;
                    }
                }
            }
        }
        else {  // if team == ChessPiece::team_type::black
            if (move1 == 6 && move2 == 7) {
                if (isPiece(7, 7) && getPiece(7, 7) == ChessPiece::piece_type::rook && ((Rook*)grid[7][7])->getCastleStatus()) {
                    if (validCastlePath(4, 7, 7, 7)) {
                        ((Rook*)grid[7][7])->setCastleStatus(false);
                        ((King*)grid[4][7])->setCastleStatus(false);
                        setPiece(7, 7, 5, 7);
                        return true;
                    }
                }
            }
            else if (move1 == 2 && move2 == 7) {
                if (isPiece(0, 7) && getPiece(0, 7) == ChessPiece::piece_type::rook && ((Rook*)grid[0][7])->getCastleStatus()) {
                     if (validCastlePath(4, 7, 0, 7)) {
                        ((Rook*)grid[0][7])->setCastleStatus(false);
                        ((King*)grid[4][7])->setCastleStatus(false);
                        setPiece(0, 7, 3, 7);
                        return true;
                     }
                }
            }
        }
       
        return false;
    }







    bool ChessBoard::validCastlePath(int k1, int k2, int r1, int r2)
    {
        int sign = -(k1 - r1) / abs(k1 - r1);
        int nextCol = k1 + sign;
        ChessPiece::team_type kTeam = getTeam(k1, k2);
        // while no piece obstructing path, and no square in path checked
        while (!isPiece(nextCol, k2) && !isCheck(kTeam, nextCol, k2))     
            nextCol = nextCol + sign;
            
        if (nextCol == r1)  // if the first obstructing piece is the castling rook
            return true;

        return false;
    }






    void ChessBoard::setKing(int pos1, int pos2, int move1, int move2)
    {
        assert(inBounds4(pos1, pos2, move1, move2));
        if (getTeam(pos1, pos2) == ChessPiece::team_type::white) {
            wKingCol = move1;
            wKingRow = move2;
        }
        else { // if (inTeam == ChessPiece::team_type::black)
            bKingCol = move1;
            bKingRow = move2;
        }
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