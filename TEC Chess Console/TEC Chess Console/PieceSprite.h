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
				
		class TextureUndefinedError {};

		// elements of draggable functionality
		void update(sf::RenderWindow& a);
		
	private:

		static const int DEFAULT_PIECE_WIDTH = 50;
		static const int  DEFAULT_PIECE_HEIGHT = 50;
		sf::Texture* TexturePtr;
		
		// elements of draggable functionality
		sf::FloatRect boundingBox = getGlobalBounds();
		float mouse_offset_x = 0;
		float mouse_offset_y = 0;
		bool dragging = false;
		bool flag_first_click = true;

		bool contains_mouse(sf::RenderWindow& window);

	};
}

#endif

