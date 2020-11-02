/*/-------------------------------------------------------------------------------------//
    Filename:           ChessTeam_Mate.h
    Contributor:        Sonja Braden
    Date:               11/1/2020
    Description:        This file includes the implementations of ChessTeam members
                        that facilitate the identitfaction of Checkmates
//-------------------------------------------------------------------------------------/*/

#include "ChessTeam.h"


namespace chess {


    bool ChessTeam::isCheckmate()
    {
        if (!isCheck(kCol, kRow) || !KingIsTrapped())   // if king cornered and/or smothered
            return false;
        
        // next, identify a block or capture that relieves the check,
        // and/or determine if there is Double check,
        // which implies direct checkmate since the king is cornered/smothered by now.
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






    bool ChessTeam::KingIsTrapped() 
    {

        int* points = getElement(kCol, kRow)->getTrapSet(kCol, kRow);
        int counter = 0;

        while (points[counter] != ChessPiece::ARRAY_END) {
            try {   // must try/catch if we are to reuse functions from ChessPiece classes
                isValidMove(kCol, kRow, points[counter], points[counter + 1]);
                if (!isCheck(points[counter], points[counter + 1]))
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

        if (isPiece(attack1, attack2) && getTeam(attack1, attack2) != team) {
            if (getPiece(attack1, attack2) == ChessPiece::piece_type::queen
                || getPiece(attack1, attack2) == ChessPiece::piece_type::rook)
                return true;
            else if (getPiece(attack1, attack2) == ChessPiece::piece_type::king &&
                (abs(attack1 - kCol) == 1 || abs(attack2 - kRow) == 1))
                return true;
        }
        else {
            attack1 = -1;
            attack2 = -1;
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

        if (isPiece(attack1, attack2) && getTeam(attack1, attack2) != team) {
            if (getPiece(attack1, attack2) == ChessPiece::piece_type::queen ||
                getPiece(attack1, attack2) == ChessPiece::piece_type::bishop)
                return true;
            else if (getPiece(attack1, attack2) == ChessPiece::piece_type::king &&
                abs(attack1 - kCol) == 1 && abs(attack2 - kRow) == 1)
                return true;
        }
        else {
            attack1 = -1;
            attack2 = -1;
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
            singleKnight(kCol, kRow, -2, 1, attack1, attack2) ||
            singleKnight(kCol, kRow, 2, -1, attack1, attack2) || 
            singleKnight(kCol, kRow, -2, -1, attack1, attack2))
            return true;

        return false;
    }






    bool ChessTeam::singleKnight(int kCol, int kRow, int colSign, int rowSign, int& attack1, int& attack2) const
    {
        attack1 = kCol + colSign;
        attack2 = kRow + rowSign;

        if (isPiece(attack1, attack2) && getTeam(attack1, attack2) != team
            && getPiece(attack1, attack2) == ChessPiece::piece_type::knight)
            return true;
        else {
            attack1 = -1;
            attack2 = -1;
        }

        return false;
    }





    // if threatened by pawn
    bool ChessTeam::checkCorners(int kCol, int kRow, int& attack1, int& attack2) const
    {
        int left = kCol - 1;
        int right = kCol + 1;

        attack2 = (team == ChessPiece::team_type::white) ? (kRow + 1) : (kRow - 1);

        if (isPiece(right, attack2) && getTeam(right, attack2) != team
            && getPiece(right, attack2) == ChessPiece::piece_type::pawn) {
            attack1 = right;
            return true;
        }
        if (isPiece(left, attack2) && getTeam(left, attack2) != team
            && getPiece(left, attack2) == ChessPiece::piece_type::pawn) {
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
        int* path = grid.getElement(attack1, attack2)->validMove(kCol, kRow);
        int k = 0;
        int col;
        int row;

        while (path[k] != -1) {

            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (isPiece(i, j) && getTeam(i, j) == team && i != kCol && j != kRow) {
                        try {
                            isValidMove(i, j, path[k], path[k + 1]);
                            return true;    // will execute only if we find a legal move 
                        }
                        catch (const chess_except::InvalidMoveExcep& e) {

                        }
                    }
                }
            }
            k += 2;
        }

        delete[] path;
        return false;
    }






    bool ChessTeam::findCapture(int attack1, int attack2)
    {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (isPiece(i, j) && getTeam(i, j) == team && i != kCol && j != kRow) {
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