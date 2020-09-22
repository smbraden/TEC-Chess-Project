/*/-------------------------------------------------------------------------------------//
    Filename:           ChessBoard.cpp
    Contributor:        Sonja Braden
    Date:               9/21/2020
    Reference:          

    Description:        Implementation  of the ChessBoard class, for creating objects
                        with properties of a chess board, including enforcement of
                        the rules of chess.
//-------------------------------------------------------------------------------------/*/

#include "ChessBoard.h"

using namespace std;

namespace chess {
    
    ChessBoard::ChessBoard()
    {
        White.setColor(white);
        Black.setColor(black);
    }
    
    int ChessBoard::moveWhite(int position1, int position2, int move1, int move2)
    {
        return 0;
    }

    int ChessBoard::moveBlack(int position1, int position2, int move1, int move2)
    {
        return 0;
    }

    void ChessBoard::printBoard()
    {
    }

    int ChessBoard::remove(int position1, int position2)
    {
        return 0;
    }

}  // closes namespace


