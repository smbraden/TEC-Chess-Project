/*/-------------------------------------------------------------------------------------//
	Filename:           History.cpp
	Contributor:        Sonja Braden
	Date:               10/19/2020
	Reference:			https://en.wikipedia.org/wiki/Threefold_repetition
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






	bool History::newPage(const team_type turn, const Grid& argGrid)
	{
		GameState newState;
		PieceRecord newRecord;

		for (int i = 0; i < ChessPiece::BOARD_SIZE; i++) {
			for (int j = 0; j < ChessPiece::BOARD_SIZE; j++) {
				if (argGrid.isPiece(j, i)) {
					toRecord(argGrid.getElement(j, i), newRecord);
					newState.push_back(newRecord);		// add the new record to the GameState
					// addRecord(newRecord, newState);	// equivalent to above
				}
			}
		}

		return addGameState(newState);
	}






	// Translates a ChessPiece to a PieceRecord
	void History::toRecord(const ChessPiece* arg, PieceRecord& newRecord) const
	{
		arg->getPosition(newRecord.col, newRecord.row);
		newRecord.piece = arg->getPieceType();
		newRecord.team = arg->getTeamType();
				
		if (newRecord.piece == piece_type::king)
			newRecord.castle = ((King*)arg)->getCastleStatus();
		if (newRecord.piece == piece_type::rook)
			newRecord.castle = ((Rook*)arg)->getCastleStatus();
		if (newRecord.piece == piece_type::pawn)
			newRecord.enPassant = ((Pawn*)arg)->getEnPassant();
	}





	/*
	void History::addRecord(PieceRecord& arg, GameState& state) const
	{
		state.push_back(arg);
	}
	*/





	bool History::addGameState(const GameState& state)
	{
		GameHistory.add(state);
		int reps = GameHistory.getFrequencyOf(state);

		if (reps >= 3) {
			draw = true;
			return true;
		}
		return false;
	}






	bool History::getDrawStatus() const
	{
		return draw;
	}






	int History::getFrequencyOf(const Grid& argGrid) const
	{
		GameState newState;
		PieceRecord newRecord;
		for (int i = 0; i < ChessPiece::BOARD_SIZE; i++) {
			for (int j = 0; j < ChessPiece::BOARD_SIZE; j++) {
				if (argGrid.isPiece(j, i)) {
					toRecord(argGrid.getElement(j, i), newRecord);
					newState.push_back(newRecord);		// add the new record to the GameState
					// addRecord(newRecord, newState);	// equivalent to above
				}
			}
		}
		return GameHistory.getFrequencyOf(newState);
	}
}
