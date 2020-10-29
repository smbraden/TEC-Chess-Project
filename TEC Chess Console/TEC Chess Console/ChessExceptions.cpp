
#include "ChessExceptions.h"


/*
// Base exception class
InvalidMoveExcep::InvalidMoveExcep(const std::string& message) :
	logic_error(message)
{
}
*/




// Base exception class
InvalidMoveExcep::InvalidMoveExcep(const std::string& message)
{
}






// The throwing piece can add sepcifics to the error string
PieceMoveError::PieceMoveError(const std::string& message) :
	InvalidMoveExcep("Piece Move Error: " + message)
{
}





SelfCapturError::SelfCapturError() :
	InvalidMoveExcep("Self Capture Error: You cannot 'capture' your own pieces...")
{
}





NoTurnPassError::NoTurnPassError() :
	InvalidMoveExcep("Turn Pass Error: No moving to the same square, no passing turns...")
{
}






TurnMoveError::TurnMoveError() :
	InvalidMoveExcep("Turn Move Error: Not your turn, or you're moving the other player's piece...")
{
}






BoundsError::BoundsError() :
	InvalidMoveExcep("Bounds Error: Cannot move to or from a position off the board...")
{
}






EmptySquareError::EmptySquareError() :
	InvalidMoveExcep("Empty Square Error: Cannot move an empty square...")
{
}






IndirectPathError::IndirectPathError() :
	InvalidMoveExcep("Indirect Path Error: Only Knights can jump over other pieces...")
{
}






CheckError::CheckError() :
	InvalidMoveExcep("Check Error: Your King is still in check...")
{
}


