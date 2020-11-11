#ifndef CHESS_PIECE_SPRITE_H
#define CHESS_PIECE_SPRITE_H

#include <vector>

#include <SFML/Graphics.hpp>
#include "drawList.h"
#include "LinkedBag.h"

namespace chess_ui {

	class PieceSprite
	{
		
	private:

		struct Texture_ID {
			std::string filename;
			sf::Texture Txt;

			Texture_ID(std::string file) {
				filename = file;
				if (!Txt.loadFromFile(filename)) { /*error*/ }
			}

			bool operator==(const Texture_ID& right) const {
				filename == right.filename;
			}
		};

		sf::Sprite Sprite;
		sf::Texture* TexturePtr;
		static std::vector<Texture_ID> textID_Vect; // one texture vector for all Pieces
		// Textures are resource intensive

		void addTexture(std::string file);

	public:

		PieceSprite();
		PieceSprite(std::string file, int x_pos, int y_pos);
		sf::Sprite getSprite();
		sf::Vector2f getPosition() const;
		void setPosition(int x_pos, int y_pos);
	};
}

#endif




// static cs_bag::LinkedBag<Texture_ID> textBag; // one texture vector for all Pieces
// std::vector<sf::Texture*> textVect;
// std::vector<sf::Texture*> textVect;