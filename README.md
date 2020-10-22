# TEC-Chess-Project
 
Recently merged with Symmetry-Implementation-Piece-Protected
 
The merged branch was for investigating an implementation where the symmetry of Black vs White moves is managed by BlackTeam and WhiteTeam Classes, derived from the ChessTeam base class. There are several aspects of this implementation that are more maintainable/modular. However, the design might be less efficient. Each of the Black and White Team objects has copies of their common base class members. Ideally, we could make the non-virtual base class members static in order to reduce this to one copy; however, we have exstive use of the "this" pointer, so this may not be an option.



In the Symmetry Implementation, dynamic allocation/deallocation of the ChessPieces is managed by a new Grid class, implemented via an array of pointers to the pieces. The design is more convenient, as Grid manages all dynamic operations that the other classes (ChessBoard, ChessPiece, ChessTeam) need not be concerned about.  

In master, this grid data structure is managed by ChessBoard, as are the Black and White symmetries, which are simply embedded in the move() function among all the move() helpers. By splitting the Black and White symmetries among two classes, we eliminate the need to add the conditional "if black, then do this, else (if white), do that" to each of move()'s helper functions that require it.

We still have some black/white symmetry that must be managed internally by the Pawn class, however, and this remains unchanged. The goal is to tease out the black/white symetry currently managed by the ChessBoard class, and transfer these responsiblitie to the ChessTeam's.



Note: the addition the Grid class to this branch could also be applied to the current implementation in Master, as this is an idependent feature.

Note: A further simplified implementation would involve only the board differentiating black and white teams. The teams would use exactly the same set of move() functions, but their perception/orientation of the Grid would differ. This would take advantage of all the Pieces, Board, and Teams' symmetry, resulting in the least amount of total code.   
