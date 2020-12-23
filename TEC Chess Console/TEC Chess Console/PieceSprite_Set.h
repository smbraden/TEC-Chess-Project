/*/-------------------------------------------------------------------------------------//
	Filename:           PieceSprite_Set.h
	Contributor:        Sonja Braden
	Date:               11/14/2020
	Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
	Description:		Manages dynamic allocation of PieceSprites, and manages
						PieceSprite Textures in order to prevent multiple instantiations of
						equivalent Textures

						PieceFilenames is a 2 x 6 array of filenames of the images to be used
						for the chess piece sprites. For proper initializations, ensure that
						the array is organized as follows:
						
						indicese [0][i] are the White Team
						indicese [1][i] are the Black Team
						
						for i = 0 through 5, the types of pieces should be in this order:
						Rook, Knight, Bishop, Queen, King, Pawn

						The object is intitialized with a pre-exsiting set of files, but
						the parameterized constructor can be called with reference to an
						array containing a different set of filenames. 
						This allows for creation of a set of Pieces with custom styles.
//-------------------------------------------------------------------------------------/*/

#ifndef PIECE_SPRITE_SET_H
#define PIECE_SPRITE_SET_H

#include <SFML/Graphics.hpp>
#include "PieceSprite.h"
#include <string>

namespace chess_ui {

	
	class PieceSprite_Set	{

	public:

		const static int NUM_TEAM_TEXTURES = 6;
		const static int NUM_TEAM_PIECES = 16;

		PieceSprite_Set();
		PieceSprite_Set(const sf::Vector2f& reference, int spacing);
		PieceSprite_Set(const std::string arg[2][NUM_TEAM_TEXTURES], const sf::Vector2f& reference, int spacing);
		~PieceSprite_Set();
		PieceSprite* getPiecePtr(int i, int j);

	private:

		// sf::Texture Textures[2][NUM_TEAM_TEXTURES];	// non-dynamic implementation
		sf::Texture* TexturePtrs[2][NUM_TEAM_TEXTURES];
		chess_ui::PieceSprite* spritePieces[2][NUM_TEAM_PIECES];

		std::string PieceFilenames[2][NUM_TEAM_TEXTURES] = {
		{ "Images/WhiteRook.png", "Images/WhiteKnight.png", "Images/WhiteBishop.png",
		  "Images/WhiteQueen.png","Images/WhiteKing.png", "Images/WhitePawn.png" },
		{ "Images/BlackRook.png", "Images/BlackKnight.png", "Images/BlackBishop.png",
		  "Images/BlackQueen.png", "Images/BlackKing.png", "Images/BlackPawn.png" } };

		void initPieceSprites(const sf::Vector2f& reference, int spacing);
		void initTextures();
		void addSpriteTexture(sf::Texture* txtPtr, int team_index, int piece_index, int x, int y);

	};

}


#endif
