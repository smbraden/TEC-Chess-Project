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
		
			ChessPiece(char inCol = 'a', int inRow = 1);
			class PieceMoveError {};
			void getPosition(char& inCol, int& inRow) const;	
			virtual void setPosition(char inCol, int inRow);
		
		private:

			char col;
			int row;

	};



} // closes namespace

#endif