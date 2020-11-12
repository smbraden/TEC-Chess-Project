#include "ChessPieceSprite.h"


namespace chess_ui {


	PieceSprite::PieceSprite()
	{
		filenames = "";
		TexturePtr = nullptr;	// let pieces share the same Texture
	}






	PieceSprite::PieceSprite(const std::string& file, int x_pos, int y_pos)
	{
		addTexture(file);

		setTexture(*TexturePtr);
		setPosition(x_pos, y_pos);
		scale(sf::Vector2f(.5f, .45f)); // absolute scale factor	
	}





	void PieceSprite::addTexture(const std::string& file)
	{
		sf::Texture* newTexture = new sf::Texture;
		if (newTexture->loadFromFile(file)) {
			filenames = file;
			TexturePtr = newTexture;
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