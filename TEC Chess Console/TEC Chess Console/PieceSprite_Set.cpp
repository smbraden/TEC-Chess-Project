/*/-------------------------------------------------------------------------------------//
	Filename:           PieceSprite_Set.h
	Contributor:        Sonja Braden
	Date:               11/14/2020
	Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
	Description:		Manages dynamic allocation of PieceSprites, and manages
						PieceSprite Textures in order to prevent multiple instantiations of 
						equivalent Textures
//-------------------------------------------------------------------------------------/*/


#include "PieceSprite_Set.h"

namespace chess_ui {

	PieceSprite_Set::PieceSprite_Set()
	{
		initTextures();
		initPieceSprites();
	}






	PieceSprite_Set::PieceSprite_Set(const std::string arg[2][NUM_TEAM_TEXTURES])
	{
		// duplicate the filenames this objects filename list
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < NUM_TEAM_TEXTURES; j++) {
				PieceFilenames[i][j] = arg[i][j];
			}
		}

		initTextures();		// Init the set of corresponding textures
		initPieceSprites();	// Init the Sprites from the new texture collection
	}






	PieceSprite_Set::~PieceSprite_Set()
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < NUM_TEAM_PIECES; j++) {
				if (spritePieces[i][j] != nullptr) {
					delete spritePieces[i][j];
				}
			}
		}
		
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < NUM_TEAM_TEXTURES; j++) {
				if (TexturePtrs[i][j] != nullptr) {
					delete TexturePtrs[i][j];
				}
			}
		}
	}






	PieceSprite* PieceSprite_Set::getPiecePtr(int i, int j)
	{
		return spritePieces[i][j];
	}




	
	void PieceSprite_Set::initTextures()
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < NUM_TEAM_PIECES; j++) {
				TexturePtrs[i][j] = new sf::Texture;
				TexturePtrs[i][j]->loadFromFile(PieceFilenames[i][j]);	// dynamic implementation
			}
		}
	}





	
	void PieceSprite_Set::initPieceSprites()
	{
		int white_index = 0;
		int black_index = 1;


		int x = 280;
		int Wy = 880;
		int By = 180;
		for (int i = 0; i < 5; i++) {	// leftiest wRook through wKing

			addSpriteTexture(TexturePtrs[0][i], 0, i, x, Wy);
			//addSpriteTexture(TexturePtrs[1][i], 1, i, x, By);		// to instead use Black Piece textures at index [1][i]
			addSpriteTexture(TexturePtrs[0][i], 1, i, x, By);		// to use darkened White Piece textures
			spritePieces[1][i]->setColor(sf::Color(150, 150, 150));

			x += 100;
		}
		for (int i = 5; i < 8; i++) {	// rightiest wBishop through wRook

			addSpriteTexture(TexturePtrs[0][7 - i], 0, i, x, Wy);
			//addSpriteTexture(TexturePtrs[1][7 - i], 1, i, x, By);	// to instead use Black Piece textures at index [1][7 - i]
			addSpriteTexture(TexturePtrs[0][7 - i], 1, i, x, By);	// to use darkened White Piece textures
			spritePieces[1][i]->setColor(sf::Color(150, 150, 150));

			x += 100;
		}

		x = 280;
		Wy = 780;
		By = 280;
		for (int i = 8; i < NUM_TEAM_PIECES; i++) {	// all zee wPawns
			addSpriteTexture(TexturePtrs[0][5], 0, i, x, Wy);
			// addSpriteTexture(TexturePtrs[1][5], 1, i, x, By);	// to instead use Black Piece textures at index [1][5]
			addSpriteTexture(TexturePtrs[0][5], 1, i, x, By);		// to use darkened White Piece textures
			spritePieces[1][i]->setColor(sf::Color(150, 150, 150));

			x += 100;
		}

	}

	/*
	
	Some setColor() combos to try for black
	Use the white piece texture if setting the color in software

	Tan:
	(166, 137, 111)
	(179, 153, 130)
	(169, 139, 112)

	Greys:
	(128, 128, 128)
	(175, 175, 175)
	(192, 192, 192)

	So far, best overall contrast is (150, 150, 150) grey on a slightly darkened chess board

	*/




	void PieceSprite_Set::addSpriteTexture(sf::Texture* txtPtr, int team_index, int piece_index, int x, int y)
	{
		spritePieces[team_index][piece_index] = new chess_ui::PieceSprite(txtPtr, x, y);
	}


}	// closes namespace



