/*/-------------------------------------------------------------------------------------//
    Filename:           ChessTeam.cpp
    Contributor:        Sonja Braden
    Date:               10/16/2020
    Reference:          

    Description:        Implementation  of the ChessTeam class.
//-------------------------------------------------------------------------------------/*/

#include "ChessTeam.h"


namespace chess {


    // Default sets to a white team
    ChessTeam::ChessTeam()
    {
        kCol = 4;
        kRow = 0;
        team = ChessPiece::team_type::white;
        grid = Grid();
        checkmateStatus = false;
    }





    ChessTeam::ChessTeam(ChessPiece::team_type t, Grid g, bool m)
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
        grid = g;
        checkmateStatus = m;
    }





    
    ChessPiece::team_type ChessTeam::getTeam(int pos1, int pos2) const
    {
        return grid.getTeamType(pos1, pos2);
    }






    ChessPiece::piece_type ChessTeam::getPiece(int pos1, int pos2) const
    {
        return grid.getPieceType(pos1, pos2);
    }
    




    
    ChessPiece* ChessTeam::getElement(int col, int row) const
    {
        return grid.getElement(col, row);
    }






    void ChessTeam::setElement(int col, int row, ChessPiece* ptr)
    {
        grid.setElement(col, row, ptr);
    }
    






    bool ChessTeam::getCheckmateStatus() const
    {
        return checkmateStatus;
    }






    ChessPiece::team_type ChessTeam::getTeam() const
    {
        return team;
    }







    void ChessTeam::setCheckmateStatus(bool arg)
    {
        checkmateStatus = arg;
    }






    Grid ChessTeam::getGrid() const
    {
        return grid;
    }






    int ChessTeam::getKCol() const
    {
        return kCol;
    }






    int ChessTeam::getKRow() const
    {
        return kRow;
    }







    inline bool ChessTeam::inBounds2(const int a, const int b)  const
    {
        return ((a < BOARD_SIZE) && (b < BOARD_SIZE)
            && a >= 0 && b >= 0);
    }






    inline bool ChessTeam::inBounds4(const int a, const int b, const int c, const int d)  const
    {
        return (a >= 0 && b >= 0 && c >= 0 && d >= 0
            && (a < BOARD_SIZE) && (b < BOARD_SIZE)
            && (c < BOARD_SIZE) && (d < BOARD_SIZE));
    }







    // if path is nullptr, then there was no path (ie, knight or single move)
    void ChessTeam::evaluatePath(int* path) const
    {
        if (path != nullptr) {
            int i = 0;
            int x = path[2 * i];
            int y = path[2 * i + 1];

            while (x != ChessPiece::ARRAY_END && i < (MAX_PATH * 2)) { // && y != ChessPiece::ARRAY_END

                assert(inBounds2(x, y));
                if (isPiece(x, y)) {    // if an object is in path 
                    delete[] path;
                    path = nullptr;
                    throw chess_except::IndirectPathError();
                }

                i++;
                x = path[2 * i];
                y = path[2 * i + 1];
            }
            delete[] path;
            path = nullptr;
        }
    }






    // Purpose:     checks if a move is valid, but does not account for 
    //              action/inaction regarding a Checked king; this is done in move()
    ChessTeam ChessTeam::isValidMove(int pos1, int pos2, int move1, int move2) const
    {
        ChessTeam testTeam(*this);

        if (!inBounds4(pos1, pos2, move1, move2))
            throw chess_except::BoundsError();
        else if (!isPiece(pos1, pos2))
            throw chess_except::EmptySquareError();
        else if (getTeam(pos1, pos2) != team)
            throw chess_except::TurnMoveError();
        else if (pos1 == move1 && pos2 == move2)
            throw chess_except::NoTurnPassError();
        else if (isPiece(move1, move2) && getTeam(move1, move2) == team)
            throw chess_except::SelfCapturError();
        else {  // basic rules have been followed. Next, are the rules followed for the specific piece?

            if (testTeam.getPiece(pos1, pos2) == ChessPiece::piece_type::pawn) {
                testTeam.evaluatePath(testTeam.validPawnMove(pos1, pos2, move1, move2)); // throws PieceMoveError, IlegalMoveError
                testTeam.pawnPromote(pos1, pos2, move1, move2); // mutator
            }
            else if (getPiece(pos1, pos2) == ChessPiece::piece_type::king) {
                if (!testTeam.Castle(pos1, pos2, move1, move2)) { // mutator
                    testTeam.evaluatePath(testTeam.getElement(pos1, pos2)->validMove(move1, move2));// throws PieceMoveError, IlegalMoveError
                    ((King*)testTeam.getElement(pos1, pos2))->setCastleStatus(false);
                }
                testTeam.setKing(move1, move2);// mutator
            }
            else {  // for all the other pieces
                testTeam.evaluatePath(testTeam.getElement(pos1, pos2)->validMove(move1, move2));// throws PieceMoveError, IlegalMoveError
                if (testTeam.getPiece(pos1, pos2) == ChessPiece::piece_type::rook)
                    ((Rook*)testTeam.getElement(pos1, pos2))->setCastleStatus(false);
            }

            // pawnPromote(pos1, pos2, move1, move2);  // if moving to 8th rank move, promote pawn
            testTeam.setPiece(pos1, pos2, move1, move2);     // set new pos on grid and internally, remove captures
            testTeam.resetEnPassant(move1, move2);           // resets all EnPassant to false, except a moved pawn

        }
        return testTeam;
    }


  





    // Note:    inTeam is the team whose turn it is to move
    void ChessTeam::move(int pos1, int pos2, int move1, int move2)
    {
        // isValidMove() throws exception for client if not a valid move,
        // or if it executes to completion, then the new move has been set 
        // in the returned ChessTeam object
        ChessTeam testTeam = isValidMove(pos1, pos2, move1, move2);

        if (testTeam.isCheck(testTeam.kCol, testTeam.kRow))
            throw chess_except::CheckError();
        
        *this = testTeam;
    }







    void ChessTeam::setPiece(int pos1, int pos2, int move1, int move2)
    {
        // after this, isEnPassant() called twice in move() in the case of pawn moves, 
        // could set a flag to capture the result, 
        // in order to reduce it to one isEnPassant() call per move() call
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
        grid.remove(x, y);
    }






  

    bool ChessTeam::isPiece(int inCol, int inRow) const
    {
        return grid.isPiece(inCol, inRow);
    }






    int* ChessTeam::validPawnMove(int pos1, int pos2, int move1, int move2) const
    {

        assert(getPiece(pos1, pos2) == ChessPiece::piece_type::pawn);   // terminate if not pawn
                                                                        // isPiece(pos1, pos2) is implied
        int* path = nullptr;

        if (isCapture(pos1, pos2, move1, move2) ||
            isEnPassant(pos1, pos2, move1, move2) ||
            simpleAdvance(pos1, pos2, move1, move2)) {

            path = getElement(pos1, pos2)->validMove(move1, move2);
        }
        else {
            throw chess_except::PieceMoveError("Invalid Pawn move."); // it's an invalid move if neither
        }                                               // SimpleAdvance(), isCapture(), nor isEnPassant()

        return path;
    }






    // Purpose:     Helper function to pawnMove()
    bool ChessTeam::isCapture(int pos1, int pos2, int move1, int move2) const
    {
        // if opponent occupies destination
        if (isPiece(move1, move2) && getTeam(move1, move2) != getTeam(pos1, pos2)) {
            // single diagonal move, white piece
            if (getTeam(pos1, pos2) == ChessPiece::team_type::white &&
                move2 == pos2 + 1 && abs(pos1 - move1) == 1) {
                return true;
            }
            // single diagonal move, black piece
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
            else if (move1 == (pos1 - 1) && isPiece(pos1 - 1, pos2) 
                && ((Pawn*)getElement(pos1 - 1, pos2))->getEnPassant())
                return true;
            else if (move1 == (pos1 + 1) && isPiece(pos1 + 1, pos2) 
                && ((Pawn*)getElement(pos1 + 1, pos2))->getEnPassant())
                return true;
        }
        else {  // if (getTeam(pos1, pos2) == ChessPiece::team_type::black)
            if (pos2 != 3 || move2 != 2)    // if current position is not fifth rank
                return false;               // and moving to the proper row
            // if either of the objects to the left or right has enPassant == true
            else if (move1 == (pos1 - 1) && isPiece(pos1 - 1, pos2) 
                && ((Pawn*)getElement(pos1 - 1, pos2))->getEnPassant())
                return true;
            else if (move1 == (pos1 + 1) && isPiece(pos1 + 1, pos2) 
                && ((Pawn*)getElement(pos1 + 1, pos2))->getEnPassant())
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
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {      //  !(pos1 == c && pos2 == r)
                if (isPiece(c, r) && getPiece(c, r) == ChessPiece::piece_type::pawn) {
                    ((Pawn*)getElement(c, r))->setEnPassant(false);
                }
            }
        }

        // should already be true: isPiece(pos, pos2) == true
        if (isPiece(pos1, pos2) && getPiece(pos1, pos2) == ChessPiece::piece_type::pawn) {     // This might need more specific conditions
            ((Pawn*)getElement(pos1, pos2))->setEnPassant(true);
        }
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
        if (getPiece(pos1, pos2) != ChessPiece::piece_type::king 
            || !((King*)getElement(pos1, pos2))->getCastleStatus() || isCheck(kCol, kRow))
            return false;

        if (team == ChessPiece::team_type::white) {
            if (move1 == 2 && move2 == 0) {
                if (isPiece(0, 0) && getPiece(0, 0) == ChessPiece::piece_type::rook 
                    && ((Rook*)getElement(0, 0))->getCastleStatus()) {
                    if (validCastlePath(4, 0, 0, 0)) {
                        ((Rook*)getElement(0, 0))->setCastleStatus(false);
                        ((King*)getElement(4, 0))->setCastleStatus(false);
                        setPiece(0, 0, 3, 0);
                        return true;
                    }
                }
            }
            else if (move1 == 6 && move2 == 0) {
                if (isPiece(7, 0) && getPiece(7, 0) == ChessPiece::piece_type::rook 
                    && ((Rook*)getElement(7, 0))->getCastleStatus()) {
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
                if (isPiece(7, 7) && getPiece(7, 7) == ChessPiece::piece_type::rook 
                    && ((Rook*)getElement(7, 7))->getCastleStatus()) {
                    if (validCastlePath(4, 7, 7, 7)) {
                        ((Rook*)getElement(7, 7))->setCastleStatus(false);
                        ((King*)getElement(4, 7))->setCastleStatus(false);
                        setPiece(7, 7, 5, 7);
                        return true;
                    }
                }
            }
            else if (move1 == 2 && move2 == 7) {
                if (isPiece(0, 7) && getPiece(0, 7) == ChessPiece::piece_type::rook 
                    && ((Rook*)getElement(0, 7))->getCastleStatus()) {
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






    void ChessTeam::setGrid(const Grid& arg)
    {
        grid = arg;
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





    // determines whether a piece has any legal moves available (ie 'trapped' or not)
    bool ChessTeam::isTrapped(int pos1, int pos2) const
    {
        int* points = nullptr;
        int counter = 0;

        if (!isPiece(pos1, pos2))
            return false;

        else {
            // the integers in 'coodinates' may range from -1 to 8
            points = getElement(pos1, pos2)->getTrapSet(pos1, pos2);
        }

        while (points[counter] != ChessPiece::ARRAY_END) {
            try {   // must try/catch if we are to reuse functions from ChessPiece classes
                isValidMove(pos1, pos2, points[counter], points[counter + 1]);
                return false;   // only executes is it is a valid move
            }
            catch (const chess_except::InvalidMoveExcep& e) {
                counter += 2;
            }
        }   // complete loop without any successful moves

        delete[] points;

        return true;   // must be trapped
    }






    bool ChessTeam::isStalemate()
    {
        if (isCheck(kCol, kRow))
            return false;
        else { // if no legal moves
            
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {

                    if (isPiece(i, j) && getTeam(i, j) == team && !isTrapped(i, j)) {
                        // if a piece from this team has somewhere to go
                        return false;
                    }   
                }
            }   // tested every piece on the board, without finding a legal move
            return true;
        }
    }
}  // closes namespace





