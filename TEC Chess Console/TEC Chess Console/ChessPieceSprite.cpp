#include "ChessPieceSprite.h"


namespace chess_ui {


	PieceSprite::PieceSprite()
	{
		// textVect = std::vector<sf::Texture*>();
		textVect = std::vector<sf::Texture*>();
		filenames = std::vector<std::string>();
		Sprite = sf::Sprite();
		TexturePtr = nullptr;	// let pieces share the same Texture
	}






	PieceSprite::PieceSprite(const std::string& file, int x_pos, int y_pos)
	{
		addTexture(file);

		Sprite.setTexture(*TexturePtr);
		Sprite.setPosition(sf::Vector2f(x_pos, y_pos));
		Sprite.scale(sf::Vector2f(.5f, .45f)); // absolute scale factor	
	}





	/*
	sf::Sprite PieceSprite::getSprite()
	{
		return Sprite;
	}
	*/



	
	sf::Sprite* PieceSprite::getSprite()
	{
		return &Sprite;
	}
	





	sf::Vector2f PieceSprite::getPosition() const
	{
		return Sprite.getPosition();
	}






	void PieceSprite::setPosition(int x_pos, int y_pos)
	{
		Sprite.setPosition(sf::Vector2f(x_pos, y_pos));
	}






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
			if (!newTexture->loadFromFile(file)) { /*error*/ }
			filenames.push_back(file);
			textVect.push_back(newTexture);
			TexturePtr = newTexture;
		}
	}
}