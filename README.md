# TEC-Chess-Project: Symmetry-Implementation
 
This branch is for investigating an implementation where the symmetry of Black vs White moves is managed by BlackTeam and WhiteTeam Classes, derived from the ChessTeam base class.

In this branch, dynamic allocation/deallocation of the ChessPieces is managed by a new Grid class, implemented via an array of pointers to the pieces. The design is more convenient, as Grid manages all dynamic operations that the other classes (ChessBoard, ChessPiece, ChessTeam) need not be concerned about.  

In master, this grid data structure is managed by ChessBoard, as are the Black and White symmetries, which are simply embedded in the move() function among all its helpers. By splitting the Black and White symmetries among two classes, we eliminate the need to add the conditional "if black, then do this, else (if white), do that" to each of move()'s helper functions that require it.

We still have some black/white symmetry that must be managed internally by the Pawn class, however, and this remains unchanged. The goal is to tease out the black/white symetry currently managed by the ChessBoard class, and transfer these responsiblitie to the ChessTeam's.

Note: the addition the Grid class to this branch could also be applied to the current implementation in Master, as this is an idependent feature.
