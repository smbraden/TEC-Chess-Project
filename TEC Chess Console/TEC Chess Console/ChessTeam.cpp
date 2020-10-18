/*/-------------------------------------------------------------------------------------//
    Filename:           ChessTeam.cpp
    Contributor:        Sonja Braden
    Date:               10/16/2020
    Reference:

    Description:        Implementation  of the ChessTeam class.
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include <cassert>
#include "ChessTeam.h"

#define toGrid(c, r) (r * BOARD_SIZE + c)
#define inBounds2(a, b) (a < BOARD_SIZE && b < BOARD_SIZE && a >= 0 && b >= 0 )
#define inBounds4(a, b, c, d) (a >= 0 && b >= 0 && c >= 0 && d >= 0 &&  \
                            a < BOARD_SIZE&& b < BOARD_SIZE&& c < BOARD_SIZE&& d < BOARD_SIZE)


using namespace std;

namespace chess {


    // Default sets to a white team, without a grid
    ChessTeam::ChessTeam()
    {
        kCol = 4;
        kRow = 0;
        team = ChessPiece::team_type::white;
        gridPtr = nullptr;
        checkmateStatus = false;
    }





    ChessTeam::ChessTeam(ChessPiece::team_type t, Grid* g, bool m)
    {
        if (t == ChessPiece::team_type::white) {
            kCol = 4;
            kRow = 0;
        }
        else {
            kCol = 4;
            kRow = 7;
        }

        team = t;
        gridPtr = g;
        checkmateStatus = m;
    }






    ChessTeam::ChessTeam(const ChessTeam& arg)
    {
        kCol = arg.kCol;
        kRow = arg.kRow;
        team = arg.team;
        gridPtr = arg.gridPtr;
        checkmateStatus = arg.checkmateStatus;
    }






    ChessTeam ChessTeam::operator=(const ChessTeam& arg) {

        kCol = arg.kCol;
        kRow = arg.kRow;
        team = arg.team;
        gridPtr = arg.gridPtr;
        checkmateStatus = arg.checkmateStatus;
    }






    ChessPiece::team_type ChessTeam::getTeam(int pos1, int pos2) const
    {
        assert(isPiece(pos1, pos2));
        return getElement(pos1, pos2)->getTeamType();
    }






    ChessPiece::piece_type ChessTeam::getPiece(int pos1, int pos2) const
    {
        assert(isPiece(pos1, pos2));
        return getElement(pos1, pos2)->getPieceType();
    }






    ChessPiece* ChessTeam::getElement(int col, int row) const
    {
        return gridPtr->getElement(row, col);
    }






    ChessPiece* ChessTeam::setElement(int col, int row, ChessPiece* ptr)
    {
        gridPtr->setElement(col, row, ptr);
    }







    bool ChessTeam::getCheckmateStatus() const
    {
        return checkmateStatus;
    }






    ChessPiece::team_type ChessTeam::getTeam() const
    {
        return team;
    }







    Grid* ChessTeam::getGridPtr()
    {
        return gridPtr;
    }





    void ChessTeam::setGridPtr(Grid* arg)
    {
        gridPtr = arg;
    }






    void ChessTeam::setCheckmateStatus(bool arg)
    {
        checkmateStatus = arg;
    }






    int ChessTeam::getKCol() const
    {
        return kCol;
    }






    int ChessTeam::getKRow() const
    {
        return kRow;
    }








    // if path is nullptr, then there was no path (ie, knight or single move)
    void ChessTeam::evaluatePath(int* path) const
    {
        if (path != nullptr) {
            int i = 0;
            int x = path[2 * i];
            int y = path[2 * i + 1];

            while (x != -1 && y != -1 && i < (MAX_PATH * 2)) {

                assert(inBounds2(x, y));
                if (getElement(x, y) != nullptr) {    // if an object is in path 
                    delete[] path;
                    path = nullptr;
                    throw IndirectPathError();
                }

                i++;
                x = path[2 * i];
                y = path[2 * i + 1];
            }
            delete[] path;
            path = nullptr;
        }
    }













    // Note:    inTeam is the team whose turn it is to move
    void ChessTeam::move(int pos1, int pos2, int move1, int move2, ChessPiece::team_type inTeamType)
    {
        if (!inBounds4(pos1, pos2, move1, move2)) {
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

            Grid tempGrid = *gridPtr;
            
            try {

                if (getPiece(pos1, pos2) == ChessPiece::piece_type::pawn) { // Pawns have special rules to assess
                    evaluatePath(validPawnMove(pos1, pos2, move1, move2));  // might throw piece or ilegal move error
                    pawnPromote(pos1, pos2, move1, move2);                  // if moving to 8th rank move, promote pawn
                }
                else if (getPiece(pos1, pos2) == ChessPiece::piece_type::king) {
                    if (!Castle(pos1, pos2, move1, move2)) {
                        evaluatePath(getElement(pos1, pos2)->validMove(move1, move2));
                        ((King*)getElement(pos1, pos2))->setCastleStatus(false);
                    }
                    setKing(move1, move2);
                }
                else {  // all the other pieces
                    evaluatePath(getElement(pos1, pos2)->validMove(move1, move2));// throws PieceMoveError, IlegalMoveError
                    if (getPiece(pos1, pos2) == ChessPiece::piece_type::rook)
                        ((Rook*)getElement(pos1, pos2))->setCastleStatus(false);
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

            if (isCheck()) {
                
                gridPtr = &tempGrid;
                throw CheckError();
            }
        }
    }






    void ChessTeam::setPiece(int pos1, int pos2, int move1, int move2)
    {
        if (isEnPassant(pos1, pos2, move1, move2))
            remove(move1, pos2);
        else if (isPiece(move1, move2))
            remove(move1, move2);
                                                                
        setElement(move1, move2, getElement(pos1, pos2));       // map the object with the destination coordinate
        getElement(pos1, pos2)->setPosition(move1, move2);      // set the object's internal position
        setElement(pos1, pos2, nullptr);                        // set previous coordinate to empty
    }





       
    void ChessTeam::remove(int x, int y)
    {
        gridPtr->remove(x, y);
    }






  

    bool ChessTeam::isPiece(int inCol, int inRow) const
    {
        if (inBounds2(inCol, inRow) && getElement(inCol, inRow) != nullptr)
            return true;
        return false;
    }







    int* ChessTeam::validPawnMove(int pos1, int pos2, int move1, int move2) const
    {

        assert(getPiece(pos1, pos2) == ChessPiece::piece_type::pawn);   // terminate if not pawn
                                                                        // isPiece(pos1, pos2) is implied
        int* path = nullptr;

        if (isCapture(pos1, pos2, move1, move2) ||
            isEnPassant(pos1, pos2, move1, move2) ||
            simpleAdvance(pos1, pos2, move1, move2)) {

            try {
                path = getElement(pos1, pos2)->validMove(move1, move2);
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
    bool ChessTeam::isCapture(int pos1, int pos2, int move1, int move2) const
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
    bool ChessTeam::simpleAdvance(int pos1, int pos2, int move1, int move2) const
    {
        if (!isPiece(move1, move2) && pos1 == move1)    // destination is empty square, 
            return true;                                // and same column as current position
        return false;                                   // setPosition() takes care of the specifics
    }






    // Purpose:         Checks for a valid En Passant move
    // Precondition:    The move  and current position are in bounds
    // Return:          True if a valid En Passant move
    //                  False if not En Passant move, or not Pawn
    bool ChessTeam::isEnPassant(int pos1, int pos2, int move1, int move2) const
    {
        assert(inBounds4(pos1, pos2, move1, move2));

        if (isPiece(pos1, pos2) && getPiece(pos1, pos2) != ChessPiece::piece_type::pawn) {
            return false;
        }
        if (isPiece(pos1, pos2) && getTeam(pos1, pos2) == ChessPiece::team_type::white) {
            if (pos2 != 4 || move2 != 5)    // if current position is not fifth rank
                return false;               // and moving to the proper row
            // if either of the objects to the left or right has enPassant == true
            else if (move1 == (pos1 - 1) && isPiece(pos1 - 1, pos2) && ((Pawn*)getElement(pos1 - 1, pos2))->getEnPassant())
                return true;
            else if (move1 == (pos1 + 1) && isPiece(pos1 + 1, pos2) && ((Pawn*)getElement(pos1 + 1, pos2))->getEnPassant())
                return true;
        }
        else {  // if (getTeam(pos1, pos2) == ChessPiece::team_type::black)
            if (pos2 != 3 || move2 != 2)    // if current position is not fifth rank
                return false;               // and moving to the proper row
            // if either of the objects to the left or right has enPassant == true
            else if (move1 == (pos1 - 1) && isPiece(pos1 - 1, pos2) && ((Pawn*)getElement(pos1 - 1, pos2))->getEnPassant())
                return true;
            else if (move1 == (pos1 + 1) && isPiece(pos1 + 1, pos2) && ((Pawn*)getElement(pos1 + 1, pos2))->getEnPassant())
                return true;
        }

        return false;
    }







    // IN PROGRESS: Promotion with options needs implementing, currently promotes to queen
    void ChessTeam::pawnPromote(int pos1, int pos2, int move1, int move2)
    {
        assert(inBounds4(pos1, pos2, move1, move2));
        ChessPiece::team_type team = getTeam(pos1, pos2);

        if (isPiece(pos1, pos2) && getPiece(pos1, pos2) == ChessPiece::piece_type::pawn) {
            if ((team == ChessPiece::team_type::white && move2 == 7) ||
                (team == ChessPiece::team_type::black && move2 == 0)) {
                // later, promote with options HERE
                Queen* qPtr = new Queen(pos1, pos2, team);
                remove(pos1, pos2);
                setElement(pos1, pos2, qPtr);
            }
        }
    }






    // Purpose:         Resets all enPassant to false, except the moving piece, if Pawn
    // Precondition:    The move  and current position are in bounds
    void ChessTeam::resetEnPassant(int pos1, int pos2)
    {
        //Pawn* ptr = nullptr;

        for (int c = 0; c < BOARD_SIZE; c++) {
            for (int r = 0; r < BOARD_SIZE; r++) {      //  !(pos1 == c && pos2 == r)
                if (isPiece(c, r) && getPiece(c, r) == ChessPiece::piece_type::pawn) {
                    ((Pawn*)getElement(c, r))->setEnPassant(false);
                }
            }
        }

        if (getPiece(pos1, pos2) == ChessPiece::piece_type::pawn) {     // This might need more specific conditions
            ((Pawn*)getElement(pos1, pos2))->setEnPassant(true);
        }
    }






    bool ChessTeam::isCheck() const
    {
        int row;
        int col;

        row = kRow;
        col = kCol;

        // if there is attacking queen or rook from laterals
        if (checkLaterals(col, row))
            return true;
        // if threatened by pawn from corners
        else if (checkCorners(col, row))
            return true;
        // else if there is an attacking queen or bishop in diagonals
        else if (checkDiagonals(col, row))
            return true;
        // else if there are any attacking knights
        else if (checkKnight(col, row))
            return true;

        return false;
    }






    bool ChessTeam::isCheck(int pos1, int pos2) const
    {
        // if there is attacking queen or rook from laterals
        if (checkLaterals(pos1, pos2))
            return true;
        // if threatened by pawn from corners
        else if (checkCorners(pos1, pos2))
            return true;
        // else if there is an attacking queen or bishop in diagonals
        else if (checkDiagonals(pos1, pos2))
            return true;
        // else if there are any attacking knights
        else if (checkKnight(pos1, pos2))
            return true;

        return false;
    }






    bool ChessTeam::checkLaterals(int kCol, int kRow) const
    {
        if (singleLateral(kCol, kRow, 1, 0) ||
            singleLateral(kCol, kRow, -1, 0) ||
            singleLateral(kCol, kRow, 0, 1) ||
            singleLateral(kCol, kRow, 0, -1))
            return true;

        return false;
    }






    //    Precondition: Either colSign or rowSign is 0
    //                  Either colSign or RowSign is 1 or -1
    //                  kCol is the king's column
    //                  kRow is the king's row
    bool ChessTeam::singleLateral(int kCol, int kRow, int colSign, int rowSign) const
    {
        int nextCol = kCol + colSign;
        int nextRow = kRow + rowSign;

        while (inBounds2(nextCol, nextRow) && !isPiece(nextCol, nextRow)) {
            nextCol = nextCol + colSign;
            nextRow = nextRow + rowSign;
        }

        if (isPiece(nextCol, nextRow) && getTeam(nextCol, nextRow) != team) {
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
    bool ChessTeam::checkCorners(int kCol, int kRow) const
    {
        int left = kCol - 1;
        int right = kCol + 1;
        int pRow;

        pRow = (team == ChessPiece::team_type::white) ? (kRow + 1) : (kRow - 1);

        if ((isPiece(right, pRow) && getTeam(right, pRow) != team
            && getPiece(right, pRow) == ChessPiece::piece_type::pawn) ||
            (isPiece(left, pRow) && getTeam(left, pRow) != team
                && getPiece(left, pRow) == ChessPiece::piece_type::pawn))
            return true;

        return false;
    }






    // Precondition:    colSign and rowSign are 1 or -1
    bool ChessTeam::checkDiagonals(int kCol, int kRow) const
    {
        if (singleDiagonal(kCol, kRow, 1, -1) ||
            singleDiagonal(kCol, kRow, 1, 1) ||
            singleDiagonal(kCol, kRow, -1, 1) ||
            singleDiagonal(kCol, kRow, -1, -1))
            return true;

        return false; // if not threatened from diagonal by opponent queen or bishop
    }







    bool ChessTeam::singleDiagonal(int kCol, int kRow, int colSign, int rowSign) const
    {
        int nextCol = kCol + colSign;
        int nextRow = kRow + rowSign;

        while (inBounds2(nextCol, nextRow) && !isPiece(nextCol, nextRow)) {
            nextCol = nextCol + colSign;
            nextRow = nextRow + rowSign;
        }

        if (isPiece(nextCol, nextRow) && getTeam(nextCol, nextRow) != team) {
            if (getPiece(nextCol, nextRow) == ChessPiece::piece_type::queen ||
                getPiece(nextCol, nextRow) == ChessPiece::piece_type::bishop)
                return true;
            else if (getPiece(nextCol, nextRow) == ChessPiece::piece_type::king &&
                abs(nextCol - kCol) == 1 && abs(nextRow - kRow) == 1)
                return true;
        }

        return false;
    }







    bool ChessTeam::checkKnight(int kCol, int kRow) const
    {
        // if threatened by an opponent knight
        if (singleKnight(kCol, kRow, 1, 2) || singleKnight(kCol, kRow, 1, -2) ||
            singleKnight(kCol, kRow, -1, 2) || singleKnight(kCol, kRow, -1, -2) ||
            singleKnight(kCol, kRow, 2, 1) || singleKnight(kCol, kRow, -2, 1) ||
            singleKnight(kCol, kRow, 2, -1) || singleKnight(kCol, kRow, -2, -1))
            return true;

        return false;
    }






    // Precondition: Either colSign or rowSign is in {2, -2} and,
    //               Either colSign or RowSign is in {1, -1}
    //               kCol is the king's column
    //               kRow is the king's row
    bool ChessTeam::singleKnight(int kCol, int kRow, int colSign, int rowSign) const
    {
        int col = kCol + colSign;
        int row = kRow + rowSign;

        if (isPiece(col, row) && getTeam(col, row) != team
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

    bool ChessTeam::Castle(int pos1, int pos2, int move1, int move2)
    {
        assert(isPiece(pos1, pos2));
        
        // confirm the basic conditions
        if (getPiece(pos1, pos2) != ChessPiece::piece_type::king || !((King*)getElement(pos1, pos2))->getCastleStatus() || isCheck())
            return false;

        if (team == ChessPiece::team_type::white) {
            if (move1 == 2 && move2 == 0) {
                if (isPiece(0, 0) && getPiece(0, 0) == ChessPiece::piece_type::rook && ((Rook*)getElement(0, 0))->getCastleStatus()) {
                    if (validCastlePath(4, 0, 0, 0)) {
                        ((Rook*)getElement(0, 0))->setCastleStatus(false);
                        ((King*)getElement(4, 0))->setCastleStatus(false);
                        setPiece(0, 0, 3, 0);
                        return true;
                    }
                }
            }
            else if (move1 == 6 && move2 == 0) {
                if (isPiece(7, 0) && getPiece(7, 0) == ChessPiece::piece_type::rook && ((Rook*)getElement(7, 0))->getCastleStatus()) {
                    if (validCastlePath(4, 0, 7, 0)) {
                        ((Rook*)getElement(7, 0))->setCastleStatus(false);
                        ((King*)getElement(4, 0))->setCastleStatus(false);
                        setPiece(7, 0, 5, 0);
                        return true;
                    }
                }
            }
        }
        else {  // if team == ChessPiece::team_type::black
            if (move1 == 6 && move2 == 7) {
                if (isPiece(7, 7) && getPiece(7, 7) == ChessPiece::piece_type::rook && ((Rook*)getElement(7, 7))->getCastleStatus()) {
                    if (validCastlePath(4, 7, 7, 7)) {
                        ((Rook*)getElement(7, 7))->setCastleStatus(false);
                        ((King*)getElement(4, 7))->setCastleStatus(false);
                        setPiece(7, 7, 5, 7);
                        return true;
                    }
                }
            }
            else if (move1 == 2 && move2 == 7) {
                if (isPiece(0, 7) && getPiece(0, 7) == ChessPiece::piece_type::rook && ((Rook*)getElement(0, 7))->getCastleStatus()) {
                    if (validCastlePath(4, 7, 0, 7)) {
                        ((Rook*)getElement(0, 7))->setCastleStatus(false);
                        ((King*)getElement(4, 7))->setCastleStatus(false);
                        setPiece(0, 7, 3, 7);
                        return true;
                    }
                }
            }
        }

        return false;
    }







    bool ChessTeam::validCastlePath(int k1, int k2, int r1, int r2)
    {
        int sign = -(k1 - r1) / abs(k1 - r1);
        int nextCol = k1 + sign;
        
        // while no piece obstructing path, and no square in path checked
        while (!isPiece(nextCol, k2) && !isCheck(nextCol, k2))
            nextCol = nextCol + sign;

        if (nextCol == r1)  // if the first obstructing piece is the castling rook
            return true;

        return false;
    }






    void ChessTeam::setKing(int move1, int move2)
    {
        assert(inBounds2(move1, move2));
        
        kCol = move1;
        kRow = move2;
    }






    void ChessTeam::setTeam(ChessPiece::team_type t)
    {
        team = t;
    }






    void ChessTeam::setGridPtr(Grid* g)
    {
        gridPtr = g;
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