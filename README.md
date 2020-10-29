# TEC-Chess-Project
 
Recently merged with Symmetry-Implementation-Piece-Protected
 
The merged branch was for investigating an implementation where the symmetry of Black vs White moves is managed by BlackTeam and WhiteTeam Classes, derived from the ChessTeam base class. There are several aspects of this implementation that are more maintainable/modular. However, the design might be slightly less space-efficient, as each of the Black and White Team objects now has a copy of their common base class members.

In the Symmetry Implementation, dynamic allocation/deallocation of the ChessPieces is managed by a new Grid class, implemented via an array of pointers to the pieces. The design is more convenient, as Grid manages all dynamic operations that the other classes (ChessBoard, ChessPiece, ChessTeam) need not be concerned about.  

In the previous design, this grid data structure was managed by ChessBoard, as were the Black and White symmetries. The Black/White symmetry was formerly embedded in the move() function among all the move() helpers (of which there are many). By splitting the Black and White symmetries among two classes, we eliminate the need to add the conditional "if black, then do this, else (if white), do that" to each of move()'s helper functions that require it.

Note: the addition the Grid class to this branch could also be applied to the old implementation, as this is an idependent feature.

Note: A further simplified implementation would involve only the board differentiating black and white teams. The teams would use exactly the same set of move() functions, but their perception/orientation of the Grid would differ. This would take advantage of all the Pieces, Board, and Teams' symmetry, resulting in the least amount of total code.   
