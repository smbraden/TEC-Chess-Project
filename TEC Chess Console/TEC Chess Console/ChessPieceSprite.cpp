/*/-------------------------------------------------------------------------------------//
   Filename:           ChessPieceSprite.cpp
   Contributors:       Sonja Braden
   Date:               11/11/2020
   Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
   Description:			Adding a texture object to a derived sf::Sprite class,
						Also automating some of the initializations common to
						all Chess piece sprites
//-------------------------------------------------------------------------------------/*/

#include "ChessPieceSprite.h"

namespace chess_ui {


	PieceSprite::PieceSprite()
	{
		filename = "";
		spriteTexture = sf::Texture();
	}






	PieceSprite::PieceSprite(const std::string& file, int x_pos, int y_pos)
	{
		addTexture(file);

		setTexture(spriteTexture);
		setPosition(x_pos, y_pos);
		scale(sf::Vector2f(.5f, .45f)); // absolute scale factor	
	}





	void PieceSprite::addTexture(const std::string& file)
	{
		if (spriteTexture.loadFromFile(file)) {
			filename = file;
		}
		else {
			throw TextureUndefinedError();
		}
	}

}	// closes namespace






/*
void PieceSprite::addTexture(const std::string& file)
{
	bool flag = true;
	for (int i = 0; i < textVect.size(); i++) {
		if (filenames[i] == file) {
			TexturePtr = textVect[i];
			flag = false;
			break;
		}
	}

	if (flag) {

		sf::Texture* newTexture = new sf::Texture;
		if (!newTexture->loadFromFile(file)) { } // error
		filenames.push_back(file);
		textVect.push_back(newTexture);
		TexturePtr = newTexture;
	}
}
*/