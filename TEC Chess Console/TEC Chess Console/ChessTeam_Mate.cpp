/*/-------------------------------------------------------------------------------------//
    Filename:           ChessTeam_Mate.h
    Contributor:        Sonja Braden
    Date:               11/1/2020
    Description:        This file includes the implementations of ChessTeam members
                        that facilitate the identitfaction of Checkmates and Check
//-------------------------------------------------------------------------------------/*/

#include "ChessTeam.h"


namespace chess {


    bool ChessTeam::isCheckmate()
    {
        int kCol = turn.kCol;
        int kRow = turn.kRow;

        if (!isCheck(kCol, kRow) || !KingIsTrapped())   // if king cornered and/or smothered
            return false;
        
        // next, identify a block or capture that relieves the check,
        // and/or determine if there is Double check 
        // (which can only occur by combinations of different pieces)
        // If the king has been found to be cornered/smothered, a double check will imply checkmate
        int attack1 = -1;
        int attack2 = -1;
        int totalAttackers = 0;
       
        if (checkLaterals(kCol, kRow, attack1, attack2)) {
            totalAttackers++;
            if (!findBlockCapture(attack1, attack2)) {
                return true;
            }
        }

        if (checkDiagonals(kCol, kRow, attack1, attack2)) {
            if ( (++totalAttackers) > 1 || !findBlockCapture(attack1, attack2))
                return true;
        }
        
        if (checkCorners(kCol, kRow, attack1, attack2)) {
            if ( (++totalAttackers) > 1 || !findBlockCapture(attack1, attack2))
                return true;
        }
            
        if (checkKnight(kCol, kRow, attack1, attack2)) {
            if ( (++totalAttackers) > 1 || !findBlockCapture(attack1, attack2))
                return true;
        }

        return false;
    }





    bool ChessTeam::isCheck(int pos1, int pos2) const
    {
        int dummyArg1;
        int dummyArg2;
        // if there is attacking queen or rook from laterals
        if (checkLaterals(pos1, pos2, dummyArg1, dummyArg2))
            return true;
        // if threatened by pawn from corners
        else if (checkCorners(pos1, pos2, dummyArg1, dummyArg2))
            return true;
        // else if there is an attacking queen or bishop in diagonals
        else if (checkDiagonals(pos1, pos2, dummyArg1, dummyArg2))
            return true;
        // else if there are any attacking knights
        else if (checkKnight(pos1, pos2, dummyArg1, dummyArg2))
            return true;

        return false;
    }






    bool ChessTeam::KingIsTrapped() 
    {

        int* points = getElement(turn.kCol, turn.kRow)->getTrapSet();
        int counter = 0;

        while (points[counter] != ChessPiece::ARRAY_END) {
            try {   // must try/catch if we are to reuse functions from ChessPiece classes
                ChessTeam testTeam = isValidMove(turn.kCol, turn.kRow, points[counter], points[counter + 1]);
                if (!testTeam.isCheck(points[counter], points[counter + 1]))
                    return false;
            }
            catch (const chess_except::InvalidMoveExcep& e) {
                
            }
            counter += 2;
        }   // complete loop without any successful moves

        delete[] points;

        return true;
    }







    bool ChessTeam::checkLaterals(int kCol, int kRow, int& attack1, int& attack2) const
    {
        if (singleLateral(kCol, kRow, 1, 0, attack1, attack2) ||
            singleLateral(kCol, kRow, -1, 0, attack1, attack2) ||
            singleLateral(kCol, kRow, 0, 1, attack1, attack2) ||
            singleLateral(kCol, kRow, 0, -1, attack1, attack2))
            return true;

        return false;
    }






    bool ChessTeam::singleLateral(int kCol, int kRow, int colSign, int rowSign, int& attack1, int& attack2) const
    {
        attack1 = kCol + colSign;
        attack2 = kRow + rowSign;

        while (inBounds2(attack1, attack2) && !isPiece(attack1, attack2)) {
            attack1 = attack1 + colSign;
            attack2 = attack2 + rowSign;
        }

        if (isPiece(attack1, attack2) && getTeamType(attack1, attack2) != turn.team) {
            if (getPieceType(attack1, attack2) == ChessPiece::piece_type::queen
                || getPieceType(attack1, attack2) == ChessPiece::piece_type::rook)
                return true;
            else if (getPieceType(attack1, attack2) == ChessPiece::piece_type::king &&
                (abs(attack1 - kCol) == 1 || abs(attack2 - kRow) == 1))
                return true;
        }

        return false;
    }






    bool  ChessTeam::checkDiagonals(int kCol, int kRow, int& attack1, int& attack2) const
    {
        if (singleDiagonal(kCol, kRow, 1, -1, attack1, attack2) ||
            singleDiagonal(kCol, kRow, 1, 1, attack1, attack2) ||
            singleDiagonal(kCol, kRow, -1, 1, attack1, attack2) ||
            singleDiagonal(kCol, kRow, -1, -1, attack1, attack2))
            return true;

        return false; // if not threatened from diagonal by opponent queen or bishop
    }






    bool ChessTeam::singleDiagonal(int kCol, int kRow, int colSign, int rowSign, int& attack1, int& attack2) const
    {
        attack1 = kCol + colSign;
        attack2 = kRow + rowSign;

        while (inBounds2(attack1, attack2) && !isPiece(attack1, attack2)) {
            attack1 = attack1 + colSign;
            attack2 = attack2 + rowSign;
        }

        if (isPiece(attack1, attack2) && getTeamType(attack1, attack2) != turn.team) {
            if (getPieceType(attack1, attack2) == ChessPiece::piece_type::queen ||
                getPieceType(attack1, attack2) == ChessPiece::piece_type::bishop)
                return true;
            else if (getPieceType(attack1, attack2) == ChessPiece::piece_type::king &&
                abs(attack1 - kCol) == 1 && abs(attack2 - kRow) == 1)
                return true;
        }

        return false;
    }






    bool ChessTeam::checkKnight(int kCol, int kRow, int& attack1, int& attack2) const
    {
        // if threatened by an opponent knight
        if (singleKnight(kCol, kRow, 1, 2, attack1, attack2) || 
            singleKnight(kCol, kRow, 1, -2, attack1, attack2) ||
            singleKnight(kCol, kRow, -1, 2, attack1, attack2) || 
            singleKnight(kCol, kRow, -1, -2, attack1, attack2) ||
            singleKnight(kCol, kRow, 2, 1, attack1, attack2) || 
            singleKnight(kCol, kRow, 2, -1, attack1, attack2) || 
            singleKnight(kCol, kRow, -2, 1, attack1, attack2) ||
            singleKnight(kCol, kRow, -2, -1, attack1, attack2))
            return true;

        return false;
    }






    bool ChessTeam::singleKnight(int kCol, int kRow, int colSign, int rowSign, int& attack1, int& attack2) const
    {
        attack1 = kCol + colSign;
        attack2 = kRow + rowSign;

        if (isPiece(attack1, attack2) && getTeamType(attack1, attack2) != turn.team
            && getPieceType(attack1, attack2) == ChessPiece::piece_type::knight)
            return true;
        
        return false;
    }





    // if threatened by pawn
    bool ChessTeam::checkCorners(int kCol, int kRow, int& attack1, int& attack2) const
    {
        int left = kCol - 1;
        int right = kCol + 1;

        attack2 = (turn.team == ChessPiece::team_type::white) ? (kRow + 1) : (kRow - 1);

        if (isPiece(right, attack2) && getTeamType(right, attack2) != turn.team
            && getPieceType(right, attack2) == ChessPiece::piece_type::pawn) {
            attack1 = right;
            return true;
        }
        if (isPiece(left, attack2) && getTeamType(left, attack2) != turn.team
            && getPieceType(left, attack2) == ChessPiece::piece_type::pawn) {
            attack1 = left;
            return true;
        }

        return false;
    }





    bool ChessTeam::findBlockCapture(int attack1, int attack2)
    {
        // if there is a block of this attack    
        if (findBlock(attack1, attack2) || findCapture(attack1, attack2))
            return true;
        
        return false;
    }






    bool ChessTeam::findBlock(int attack1, int attack2)
    {
        // get the path from attacker to king, if there is one
        int* path = grid.getElement(attack1, attack2)->validMove(turn.kCol, turn.kRow);
        int k = 0;
        
        if (path != nullptr) {
            while (path[2 * k] != ChessPiece::ARRAY_END && (2 * k) < ChessPiece::MAX_PATH_LEN) {  // && path[2 * k + 1] != ChessPiece::ARRAY_END

                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        if (isPiece(i, j) && getTeamType(i, j) == turn.team && i != turn.kCol && j != turn.kRow) {
                            try {
                                isValidMove(i, j, path[2 * k], path[2 * k + 1]);
                                return true;    // will execute only if we find a legal move 
                            }
                            catch (const chess_except::InvalidMoveExcep& e) {

                            }
                        }
                    }
                }
                k++;    // increment array access counter
            }
        }

        delete[] path;
        return false;
    }







    bool ChessTeam::findCapture(int attack1, int attack2)
    {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (isPiece(i, j) && getTeamType(i, j) == turn.team && i != turn.kCol && j != turn.kRow) {
                    try {
                        isValidMove(i, j, attack1, attack2);
                        return true;    // will execute only if we find a legal move 
                    }
                    catch (const chess_except::InvalidMoveExcep& e) {

                    }
                }
            }
        }   // checked all, and no pieces capable of capture

        return false;
    }


    //------------------------End Checkmate functions-----------------------//

}