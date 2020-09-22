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

	enum team_type { white, black };
	
	class ChessPiece {

		public:
		
			//ChessPiece();
			ChessPiece(int inCol = 0, int inRow = 0, char color = 'w');
			class PieceMoveError {};
			void getPosition(int& inCol, int& inRow) const;
			char getPieceType() const;
			char getTeamType() const;
			virtual void setPosition(int inCol, int inRow);
		
		protected:

			int col;
			int row;
			char piece_type;
			char team_type;

	};



} // closes namespace

#endif