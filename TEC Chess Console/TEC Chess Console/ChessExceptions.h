#ifndef INVALID_MOVE_EXCEP_H
#define INVALID_MOVE_EXCEP_H

#include <stdexcept>
#include <string>


namespace chess_except {

	
	class DrawSignal {
	public:
		DrawSignal(const std::string& message = "") : msg("The game is a draw. " + message) {}
		std::string getMsg() const { return msg; }
	protected:
		std::string msg;
	};





	class WinSignal {
	public:
		WinSignal(const std::string& message = "") : msg("Checkmate. The winner is " + message) {}
		std::string getMsg() const { return msg; }
	protected:
		std::string msg;
	};
	





	class InvalidMoveExcep
	{

	public:
		InvalidMoveExcep(const std::string& message = "") : msg(message) {}
		std::string getMsg() const { return msg; }
	protected:
		std::string msg;
	};





	class PieceMoveError : public InvalidMoveExcep
	{

	public:
		PieceMoveError(const std::string& message = "") :
			InvalidMoveExcep("Piece Move Error: " + message) {}

	};	// rules for a specific piece's movement are not obeyed






	class SelfCapturError : public InvalidMoveExcep
	{

	public:
		SelfCapturError(const std::string& message = "Self Capture Error: You cannot 'capture' your own pieces...") :
			InvalidMoveExcep(message) {}

	};	// moving a piece to a position already occupied by that team






	class NoTurnPassError : public InvalidMoveExcep
	{

	public:
		NoTurnPassError(const std::string& message = "Turn Pass Error: No moving to the same square, no passing turns...") :
			InvalidMoveExcep(message) {}

	};	// Equivalent to moving a piece to its current position






	class TurnMoveError : public InvalidMoveExcep
	{

	public:
		TurnMoveError(const std::string& message = "Turn Move Error: Not your turn, or you're moving the other player's piece...") :
			InvalidMoveExcep(message) {}

	};		// when a player attempts to move the opponent's piece






	class BoundsError : public InvalidMoveExcep
	{

	public:
		BoundsError(const std::string& message = "Bounds Error: Cannot move to or from a position off the board...") :
			InvalidMoveExcep(message) {}

	};		// for moves that go out of board bounds






	class EmptySquareError : public InvalidMoveExcep
	{

	public:
		EmptySquareError(const std::string& message = "Empty Square Error: Cannot move an empty square...") :
			InvalidMoveExcep(message) {}

	};	// Attempt to move an empty square






	class IndirectPathError : public InvalidMoveExcep
	{

	public:
		IndirectPathError(const std::string& message = "Indirect Path Error: Only Knights can jump over other pieces...") :
			InvalidMoveExcep(message) {}

	};	// For attempts to jump over other pieces if not knight 






	class CheckError : public InvalidMoveExcep
	{

	public:
		CheckError(const std::string& message = "Check Error: Your King is still in check, or this move places him in check...") :
			InvalidMoveExcep(message) {}

	};		// if King in Check, must escape the check


}	// end namespace chess_except

#endif 


