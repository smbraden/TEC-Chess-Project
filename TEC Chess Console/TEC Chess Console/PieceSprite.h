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


namespace chess_ui {

	class PieceSprite : public sf::Sprite
	{
	
	public:
		
		PieceSprite();
		PieceSprite(sf::Texture* text, float in_x, float in_y);
		
		/*
			For an implementation where each PieceSprite instantiates
			its own personal Texture Object, use this parameterized 
			constructor instead of the one above. (several other modifications)

			PieceSprite(const std::string& file, float in_x, float in_y);

		*/
				
		class TextureUndefinedError {};

		// elements of draggable functionality
		bool contains(int in_x, int in_y);
		void update(sf::RenderWindow& a);
		void set_x_pos(float in_x);
		void set_y_pos(float in_y);
		float get_x_pos();
		float get_y_pos();
		
		
	private:

		sf::Texture* TexturePtr;
		
		/*
			For an implementation where each PieceSprite instantiates
			its own personal Texture Object, uncomment these declarations,
			and remove the one above.

			// std::string filename;
			// sf::Texture TexturePtr;

		*/

		// elements of draggable functionality
		sf::FloatRect boundingBox;
		float x_pos = 0;
		float y_pos = 0;
		float mouse_offset_x = 0;
		float mouse_offset_y = 0;
		bool dragging = false;
		bool flag_first_click = true;
				
	};
}

#endif

