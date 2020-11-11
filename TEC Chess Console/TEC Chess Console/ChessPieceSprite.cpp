#include "ChessPieceSprite.h"


namespace chess_ui {


	PieceSprite::PieceSprite()
	{
		Sprite = sf::Sprite();
		TexturePtr = nullptr;	// let pieces share the same Texture
	}






	PieceSprite::PieceSprite(std::string file, int x_pos, int y_pos)
	{
		addTexture(file);

		Sprite.setTexture(*TexturePtr);
		Sprite.setPosition(sf::Vector2f(x_pos, y_pos));
		Sprite.scale(sf::Vector2f(.5f, .45f)); // absolute scale factor	
	}






	sf::Sprite PieceSprite::getSprite()
	{
		return Sprite;
	}






	sf::Vector2f PieceSprite::getPosition() const
	{
		return Sprite.getPosition();
	}






	void PieceSprite::setPosition(int x_pos, int y_pos)
	{
		Sprite.setPosition(sf::Vector2f(x_pos, y_pos));
	}






	void PieceSprite::addTexture(std::string file)
	{
		bool flag = true;
		Texture_ID tempTextID(file);
		for (int i = 0; i < textID_Vect.size(); i++) {
			if (textID_Vect[i] == tempTextID) {
				TexturePtr = &(textID_Vect[i].Txt);
				break;
				flag = false;
			}
		}
		if (flag) {
			textID_Vect.push_back(Texture_ID(file));
			TexturePtr = &((textID_Vect.back()).Txt);
		}
	}


}