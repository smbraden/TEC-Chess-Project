/*/-------------------------------------------------------------------------------------//
   Filename:           boardTestHeader.h
   Contributors:       Sonja Braden
   Date:               11/11/2020
   Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
						https://github.com/googlefonts/Inconsolata/blob/master/fonts/ttf/Inconsolata-Medium.ttf
   Description:			
//-------------------------------------------------------------------------------------/*/
#ifndef BOARD_TEST_HEADER_H
#define BOARD_TEST_HEADER_H

#include "Chess-Backend/ChessBoard.h"
#include <ctype.h>				// for tolower()

#include "drawList.h"			// <-- redundant here #include <SFML/Graphics.hpp>
#include "ChessPieceSprite.h"	// <-- redundant here #include <SFML/Graphics.hpp>


//------------------------Constants------------------------//

const int WINDOW_W = 1400;
const int WINDOW_H = 1200;
const int BOARD_W = 900;
const int BOARD_H = 900;
const int NUM_PIECE_TEXTURES = 12;
const int NUM_TEAM_TEXTURES = 6;
const int NUM_PIECES = 32;
const int NUM_TEAM_PIECES = 16;


const std::string background_filename = "Images/marble2.jpg";
const std::string board_filename = "Images/Chess_Board_Lavender_Light.jpg";
const std::string mouse_follower_filename = "Images/marble3.jpg";
const std::string font1_filename = "Images/Inconsolata-Medium.ttf"; 

const std::string PieceFilenames[2][NUM_TEAM_TEXTURES] = {
	{ "Images/WhiteRook.png", "Images/WhiteKnight.png", "Images/WhiteBishop.png",
	  "Images/WhiteQueen.png","Images/WhiteKing.png", "Images/WhitePawn.png" },
	{ "Images/BlackRook.png", "Images/BlackKnight.png", "Images/BlackBishop.png",
	  "Images/BlackQueen.png", "Images/BlackKing.png", "Images/BlackPawn.png" } };

chess_ui::drawList drawlist;

chess_ui::PieceSprite* spritePieces[2][NUM_TEAM_PIECES];

//--------------------Backend Functions--------------------//
/*
bool testMove(chess::ChessBoard& argBoard, int x1, int y1, int x2, int y2, bool& flag);
void play(chess::ChessBoard& argBoard, char& option, char& x1, int& y1, char& x2, int& y2);
inline int char2col(char ch);
inline int int2row(int arg);
*/
//--------------------Frontend Functions--------------------//


void initPieceSprites(chess_ui::PieceSprite * spritePieces[][NUM_TEAM_PIECES]);
void destroyPieceSprites(chess_ui::PieceSprite * spritePieces[][NUM_TEAM_PIECES]);
sf::Sprite* getClickedPiece(int x_click, int y_click);



#endif // BOARD_TEST_HEADER_H