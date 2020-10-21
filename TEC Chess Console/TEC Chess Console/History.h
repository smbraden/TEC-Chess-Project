/*/-------------------------------------------------------------------------------------//
	Filename:           History.h
	Contributor:        Sonja Braden
	Date:               10/19/2020
	Reference:			https://en.wikipedia.org/wiki/Threefold_repetition
	Description:        Class for tracking the history of a game in order to determine
						3-fold repetition, and later for analysis/AI development
						
						The history is implemented as a linked list of chess piece records;
						a chess piece record is a struct that comprises the data members
						of any ChessPiece (eg, row, col, opiece, enPassant, castle)

						Define: 3-fold repetion:
						This rule states that if the same position is repeated three times
						and no progress is made, you can claim a draw.
						Two positions are by definition "the same" if the same types of pieces
						occupy the same squares, the same player has the move, the remaining
						castling rights are the same and the possibility to capture en passant 
						is the same. The repeated positions need not occur in succession.

//-------------------------------------------------------------------------------------/*/


#include "DerivedPieces.h"
#include "LinkedBag.h"
#include "Grid.h"

using namespace cs_bag;

namespace chess {

	class History
	{
	
	public:

		History();
		bool newPage(const ChessPiece::team_type turn, const Grid& argGrid);	// returns true if addition results in 3-fold repetition
		bool getDrawStatus() const;
		int getFrequencyOf(const Grid& argGrid) const;

	private:

		struct PieceRecord {
			int col;
			int row;
			bool enPassant;
			bool castle;
			ChessPiece::piece_type piece;
			ChessPiece::team_type team;
			ChessPiece::team_type turn;

			// piece(ChessPiece::piece_type::nulType)
			PieceRecord() : col(0), row(0), enPassant(false), castle(false),
				piece(ChessPiece::piece_type::nullType), team(ChessPiece::team_type::nullType),
				turn(ChessPiece::team_type::white) {}

			bool operator==(const PieceRecord& r) const {
				return (col == r.col && row == r.row && enPassant == r.enPassant &&
					castle == r.castle && piece == r.piece && team == r.team && turn == r.turn);
			}

			bool operator!=(const PieceRecord& r) const {
				return (col != r.col || row != r.row || enPassant != r.enPassant ||
					castle != r.castle || piece != r.piece || team != r.team || turn != r.turn);
			}
		};

		typedef std::vector<PieceRecord> GameState;	// single snapshot of the board	

		//---------------Chief members--------------//
		bool draw;
		LinkedBag<GameState> GameHistory;			// history of all snapshots

		void toRecord(const ChessPiece* arg, PieceRecord& newRecord) const;
		bool addGameState(const GameState& state);
		// void addRecord(PieceRecord& arg, GameState& state) const;

	};
}


