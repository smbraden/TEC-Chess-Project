/*/-------------------------------------------------------------------------------------//
	Filename:           ChessPiece.h
	Contributor:        Sonja Braden
	Date:               9/21/2020
	Reference:
	Description:		
//-------------------------------------------------------------------------------------/*/

#ifndef CHESSPIECE_H
#define CHESSPIECE_H


namespace chess {


	class ChessPiece {

		public:

			enum team_type { white = 'w', black = 'b' };
			enum piece_type { none = '0', pawn = 'P', castle = 'C', knight = 'N', 
								rook = 'R', queen = 'Q', king = 'K' };
		
			ChessPiece(int inCol = 0, int inRow = 0, team_type color = white);
			class PieceMoveError {};
			void getPosition(int& inCol, int& inRow) const;
			char getPieceType() const;
			char getTeamType() const;
			virtual void setPosition(int inCol, int inRow);
		
		protected:

			int col;
			int row;
			piece_type piece;
			team_type team;

	};



} // closes namespace

#endif