/*/-------------------------------------------------------------------------------------//
	Filename:           ChessTeam.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/

#ifndef CHESSTEAM_H
#define CHESSTEAM_H


#include  "ChessPiece.h"	// team_type is enumerated here
#include  "ArrayBag.h"


namespace chess {

	class ChessTeam {

		public:

			// constructor
			ChessTeam(team_type);
		
		private:
			ArrayBag<ChessPiece> team;
	};



} // closes namespace

#endif