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
#include "BagInterface.h"
#include  "ArrayBag.h"


namespace chess {

	class ChessTeam {

		public:

			// constructor
			ChessTeam(team_type inType = black);
			void setColor(team_type inType);
			team_type getColor() const;
			
		private:
			ArrayBag<ChessPiece> team;
			team_type color;
			void placePieces();
	};



} // closes namespace

#endif