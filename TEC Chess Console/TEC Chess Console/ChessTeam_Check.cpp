/*/-------------------------------------------------------------------------------------//
    Filename:           ChessTeam_Check.h
    Contributor:        Sonja Braden
    Date:               11/1/2020
    Description:        This file includes the implementations of ChessTeam members
                        that facilitate the identitfaction of Check,
                        and identification of arbitrary positions are in danger
//-------------------------------------------------------------------------------------/*/



#include "ChessTeam.h"

namespace chess{

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


} // closes namespace