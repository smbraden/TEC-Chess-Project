#ifndef CHESS_PIECE_SPRITE_H
#define CHESS_PIECE_SPRITE_H


#include <SFML/Graphics.hpp>
// #include <iostream>		// for overloaded string operator==
// #include <vector>		// for static vector of pointers to Unique texture objects

namespace chess_ui {

	class PieceSprite : public sf::Sprite
	{
	
	public:
		
		PieceSprite();
		PieceSprite(const std::string& file, int x_pos, int y_pos);
		void addTexture(const std::string& file);
		class TextureUndefinedError {};

	private:

		std::string filenames;
		sf::Texture* TexturePtr;
	};
}

#endif





/*

	class PieceSprite : public sf::Sprite
	{

	public:

		PieceSprite();
		PieceSprite(const std::string& file, int x_pos, int y_pos);
		void addTexture(const std::string& file);
		class TextureUndefinedError {};

	private:
		
		// one set of unique textures for all Pieces b/c Textures are resource intensive
		static std::vector<sf::Texture*> textVect;
		static  std::vector<std::string> filenames;

		std::string filenames;
		sf::Texture* TexturePtr;
	};

*/




/*

// Struct with filenames and texture obj pointers,
// rather than 2 parallel vectors
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