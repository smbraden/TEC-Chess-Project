#ifndef CHESS_PIECE_SPRITE_H
#define CHESS_PIECE_SPRITE_H

#include <vector>
#include <iostream>		// for overloaded string operator==
#include "LinkedBag.h"
#include <SFML/Graphics.hpp>


namespace chess_ui {

	class PieceSprite
	{
	
	public:

		PieceSprite();
		PieceSprite(const std::string& file, int x_pos, int y_pos);
		// sf::Sprite getSprite();
		sf::Sprite* getSprite();
		sf::Vector2f getPosition() const;
		void setPosition(int x_pos, int y_pos);

	private:

		// one texture vector for all Pieces, Textures are resource intensive
		// static std::vector<sf::Texture*> textVect;
		static std::vector<sf::Texture*> textVect;
		static  std::vector<std::string> filenames;

		sf::Sprite Sprite;
		sf::Texture* TexturePtr;

		void addTexture(const std::string& file);
	};
}

#endif





/*

// one texture vector for all Pieces, Textures are resource intensive
static std::vector<Texture_ID> textID_Vect;

struct Texture_ID {
	std::string filename;
	sf::Texture Txt;

	Texture_ID(std::string file) {
		filename = file;
		Txt = sf::Texture();
		if (!Txt.loadFromFile(filename)) {  } // error
	}

	bool operator==(const Texture_ID& right) const {
		return filename == right.filename;
	}
};

*/