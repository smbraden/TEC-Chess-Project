/*/-------------------------------------------------------------------------------------//
    Filename:           ChessTeam.cpp
    Contributor:        Sonja Braden
    Date:               9/21/2020
    Reference:

    Description:        Implementation  of the ChessTeam class, for creating a white 
                        or black opponent objects. All the chess pieces on a team are managed
                        by the ChessTeam object
//-------------------------------------------------------------------------------------/*/

#include "ChessTeam.h"

using namespace std;

namespace chess {

    ChessTeam::ChessTeam(team_type inType = black)
    {
        color = inType;
        placePieces();
    }

    void ChessTeam::setColor(team_type inType)
    {
        color = inType;
    }

    team_type ChessTeam::getColor() const
    {
        return color;
    }

    void ChessTeam::placePieces()
    {
        
        // set the piece positions for white team
        if (color == white) {
            Pawn P1(0, 1);
            Pawn P2(1, 1);
            Pawn P3(2, 1);
            Pawn P4(3, 1);
            Pawn P5(4, 1);
            Pawn P6(5, 1);
            Pawn P7(6, 1);
            Pawn P8(7, 1);

            Castle C1(0, 0);
            Castle C2(7, 0);

            Knight N1(1, 0);
            Knight N2(6, 0);

            Rook R1(2, 0);
            Rook R2(5, 0);

            Queen Q(3, 0);

            King K(4, 0);

        }
        else {  // set the piece positions for black team
            
            Pawn P1(0, 6);
            Pawn P2(1, 6);
            Pawn P3(2, 6);
            Pawn P4(3, 6);
            Pawn P5(4, 6);
            Pawn P6(5, 6);
            Pawn P7(6, 6);
            Pawn P8(7, 6);

            Castle C1(0, 7);
            Castle C2(7, 7);

            Knight N1(1, 7);
            Knight N2(6, 7);

            Rook R1(2, 7);
            Rook R2(5, 7);

            Queen Q(3, 7);

            King K(4, 7);

        }

        team.add(P1);
        team.add(P2);
        team.add(P3);
        team.add(P4);
        team.add(P5);
        team.add(P6);
        team.add(P7);
        team.add(P8);

        team.add(C1);
        team.add(C2);

        team.add(N1);
        team.add(N2);

        team.add(R1);
        team.add(R2);

        team.add(Q);
        team.add(K);

    }




}  // closes namespace

