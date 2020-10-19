/*/-------------------------------------------------------------------------------------//
	Filename:           History.cpp
	Contributor:        Sonja Braden
	Date:               10/19/2020
	Reference:
	Description:        Class for tracking the history of a game in order to determine
						3-fold repetition, and later for analysis/AI development
//-------------------------------------------------------------------------------------/*/

#include "History.h"
#include "DerivedPieces.h"

namespace chess {
	
	
	History::History()
	{
		draw = false;
	}






	bool History::newPage(const Grid& argGrid)
	{
		GameState newState;

		for (int i = 0; i < ChessPiece::BOARD_SIZE; i++) {
			for (int j = 0; j < ChessPiece::BOARD_SIZE; j++) {

				PieceRecord newRecord = toRecord(argGrid.getElement(j, i));
				addRecord(newRecord, newState);		// add the new record to the GameState
			}
		}

		return addGameState(newState);
	}






	// This is problematic, working on a solution
	PieceRecord History::toRecord(const ChessPiece* arg)
	{
		PieceRecord newRecord;
		
		// newRecord.col = argGrid.getElement(i, j)->getCol();
		// newRecord.row = argGrid.getElement(i, j)->getRow();
		arg->getPosition(newRecord.col, newRecord.row);
		newRecord.piece = arg->getPieceType();
		newRecord.team = arg->getTeamType();
				
		if (newRecord.piece == ChessPiece::piece_type::king)
			newRecord.castle = ((King*)arg)->getCastleStatus();
		if (newRecord.piece == ChessPiece::piece_type::rook)
			newRecord.castle = ((Rook*)arg)->getCastleStatus();
		if (newRecord.piece == ChessPiece::piece_type::pawn)
			newRecord.enPassant = ((Pawn*)arg)->getEnPassant();

		return newRecord;
	}






	void History::addRecord(const PieceRecord& arg, GameState& state)
	{
		state.add(arg);
	}






	bool History::addGameState(const GameState& state)
	{
		GameHistory.add(state);
		int reps = GameHistory.getFrequencyOf(state);

		if (reps >= 3) {
			return (draw = true);
		}

		return false;
	}






	bool History::getDrawStatus() const
	{
		return draw;
	}
}
