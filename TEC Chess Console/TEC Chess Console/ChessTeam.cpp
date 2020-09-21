/*/-------------------------------------------------------------------------------------//
    Filename:           ChessTeam.cpp
    Contributor:        Sonja Braden
    Date:               9/21/2020
    Reference:

    Description:        Implementation  of the ChessTeam class, for creating a white 
                        or black opponent objects. All the chess pieces on a team are managed
                        by the ChessTeam object
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include "ChessTeam.h"

using namespace std;

namespace chess {

    ChessTeam::ChessTeam(team_type inType)
    {
        if (inType == black) {
            // set the piece positions for a black team
        }
        else {
            // set the piece positions for a white team
        }
    }


}  // closes namespace
