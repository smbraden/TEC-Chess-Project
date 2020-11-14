/*/-------------------------------------------------------------------------------------//
   Filename:           ChessPieceSprite.h
   Contributors:       Sonja Braden, Jacob Halaweh
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
		PieceSprite(const std::string& file, int in_x, int in_pos);
		void addTexture(const std::string& file);
		bool contains(int in_x, int in_y);

		class TextureUndefinedError {};

		// elements of draggable functionality
		void update(sf::RenderWindow& a);
		void set_x_pos(int in_x);
		void set_y_pos(int in_y);
		float get_x_pos();
		float get_y_pos();
		
		

	private:

		std::string filename;
		sf::Texture spriteTexture;
		sf::FloatRect boundingBox;

		// elements of draggable functionality
		int width = 0;
		int height = 0;
		float x_pos = 0;
		float y_pos = 0;
		float mouse_offset_x = 0;
		float mouse_offset_y = 0;
		bool dragging = false;
		bool flag_first_click = true;
		
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