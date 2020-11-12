# TEC-Chess-Project
 
This repo is for developing the Engineering Club's Chess Engine and user interface.

The Integrate-Graphics and Graphics branches are for developing the Chess Board visual design and front-end usability.

Graphics are created with the abstraction library, [Simple Fast Media Library (SFML)](https://www.sfml-dev.org/index.php).

Some GUI features that remain to be completed include:

1. Design/Implement a mechanism for mapping pixel positions to board coordinates
2. Implement PieceSprite movement with mouse. Options:
	* Click to click (leaning towards this one)	
	* Grab and drag
3. Treat the Black team piece to contrast against the board more. Some options:
	* Lighten the Black Team to dark gray-ish
	* Light-colored outline around Black pieces
4. Resizable window with board entity that does not resize with respect to the screen

![Chess Board UI Screenshot](Project_Info/TEC_Chess_UI_ScreenShot.png)