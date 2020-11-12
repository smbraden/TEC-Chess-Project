/*/-------------------------------------------------------------------------------------//
   Filename:           ChessPieceSprite.h
   Contributors:       Sonja Braden
   Date:               11/11/2020
   Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
   Description:			Adding a texture object to a derived sf::Sprite class, 
						Also automating some of the initializations common to 
						all Chess piece sprites
//-------------------------------------------------------------------------------------/*/
#ifndef CHESS_PIECE_SPRITE_H
#define CHESS_PIECE_SPRITE_H

#include <SFML/Graphics.hpp>
// #include <iostream>		// for overloaded string operator== if static vector used
// #include <vector>		// for static vector of pointers to Unique texture objects

namespace chess_ui {

	class PieceSprite : public sf::Sprite
	{
	
	public:
		
		PieceSprite();
		PieceSprite(const std::string& file, int x_pos, int y_pos);
		void addTexture(const std::string& file);
		bool contains(int x_pos, int y_pos);
		class TextureUndefinedError {};

	private:

		std::string filename;
		sf::Texture spriteTexture;
		sf::FloatRect boundingBox;
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