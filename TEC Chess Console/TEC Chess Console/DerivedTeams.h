/*/-------------------------------------------------------------------------------------//
	Filename:           DerivedTeams.h
	Contributor:        Sonja Braden
	Date:               10/16/2020
	Reference:
	Description:
//-------------------------------------------------------------------------------------/*/


#ifndef DERIVEDTEAMS_H
#define DERIVEDTEAMS_H

#include "ChessTeam.h"
#include "History.h"

namespace chess {
	
	class WhiteTeam : public ChessTeam
	{
	public:

		WhiteTeam();
		WhiteTeam(Grid* g, bool m);

	private:

		// Symmetry-dependent Pawn-related functions//
		virtual bool isCapture(int pos1, int pos2, int move1, int move2) const;
		virtual bool isEnPassant(int pos1, int pos2, int move1, int move2) const;
		virtual void pawnPromote(int pos1, int pos2, int move1, int move2);

		// Symmetry-dependent King-related functions//
		virtual bool Castle(int pos1, int pos2, int move1, int move2);

		// Symmetry-dependent Check & Checkmate helper functions//
		virtual bool checkCorners(int kCol, int kRow) const;
		
		int* PawnMovesSet(int pos1, int pos2) const;

	};






	class BlackTeam : public ChessTeam
	{
	public:

		BlackTeam();
		BlackTeam(Grid* g, bool m);

	private:

		// Symmetry-dependent Pawn-related functions//
		virtual bool isCapture(int pos1, int pos2, int move1, int move2) const;
		virtual bool isEnPassant(int pos1, int pos2, int move1, int move2) const;
		virtual void pawnPromote(int pos1, int pos2, int move1, int move2);

		// Symmetry-dependent King-related functions//
		virtual bool Castle(int pos1, int pos2, int move1, int move2);

		// Symmetry-dependent Check & Checkmate helper functions//
		virtual bool checkCorners(int kCol, int kRow) const;
		
		int* PawnMovesSet(int pos1, int pos2) const;
		
	};



}	// closes namespace
#endif