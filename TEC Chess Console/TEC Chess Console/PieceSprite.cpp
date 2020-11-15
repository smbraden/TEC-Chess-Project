/*/-------------------------------------------------------------------------------------//
   Filename:           ChessPieceSprite.cpp
   Contributors:       Sonja Braden
   Date:               11/11/2020
   Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
   Description:			Adding a texture object and draggable functionality 
						to a derived sf::Sprite class.
						Also automating some of the initializations common to
						all Chess piece sprites.
//-------------------------------------------------------------------------------------/*/

#include "PieceSprite.h"

namespace chess_ui {

	
	// Init Texture with a pinter to another texture
	PieceSprite::PieceSprite(sf::Texture* text, float in_x, float in_y)
	{
		TexturePtr = text;
		setTexture(*TexturePtr); 
		scale(sf::Vector2f(.5f, .45f)); // absolute scale factor	
		boundingBox = getGlobalBounds();
		setPosition(in_x, in_y);

		x_pos = in_x;
		y_pos = in_y;

	}



	
	// Init Texture using a filename from projet Images
	PieceSprite::PieceSprite()
	{
		if (!(TexturePtr->loadFromFile("Images/WhitePawn.png"))) {  } // error
		setTexture(*TexturePtr);
		scale(sf::Vector2f(.5f, .45f)); // absolute scale factor	
		boundingBox = getGlobalBounds();
	
		x_pos = getPosition().x;
		y_pos = getPosition().y;
	}




	/*
	
			For an implementation where each PieceSprite instantiates
			its own personal Texture Object, use these constructors
			instead of the ones above. (with several other modifications)


	// Init Texture with a filename
	PieceSprite::PieceSprite(const std::string& file, float in_x, float in_y)
	{
		if (!(texture.loadFromFile(file))) {  } // error
		setTexture(texture); // *TexturePtr
		scale(sf::Vector2f(.5f, .45f)); // absolute scale factor	
		boundingBox = getGlobalBounds();
		setPosition(in_x, in_y);

		x_pos = in_x;
		y_pos = in_y;
	}




	// Init Texture using a filename from projet Images
	PieceSprite::PieceSprite()
	{
		if (!(text.loadFromFile("Images/WhitePawn.png"))) {  } // error
		setTexture(texture);
		scale(sf::Vector2f(.5f, .45f)); // absolute scale factor
		boundingBox = getGlobalBounds();

		x_pos = getPosition().x;
		y_pos = getPosition().y;
	}


	*/





	bool PieceSprite::contains(int in_x, int in_y)
	{
		return boundingBox.contains(in_x, in_y);
	}





	//-----------------Draggable-----------------//


	
	void PieceSprite::update(sf::RenderWindow& a) {

		int height = boundingBox.height;
		int width = boundingBox.width;

		// Get true mouse position, taking window repositioning into account. 
		// Does not account for window rescaling or skew.
		int mouse_x = sf::Mouse::getPosition().x - a.getPosition().x;
		int mouse_y = sf::Mouse::getPosition().y - a.getPosition().y;


		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (mouse_x > x_pos) && 
			(mouse_x < x_pos + width) && (mouse_y > y_pos) && (mouse_y < y_pos + height)) {

			if (flag_first_click == true) {
				dragging = true;
				mouse_offset_x = mouse_x - getPosition().x;
				mouse_offset_y = mouse_y - getPosition().y;
				flag_first_click = false;
			}
		}
		else {
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				dragging = false;
			}
		}


		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			flag_first_click = true;
		}
		else {
			flag_first_click = false;
		}


		if (dragging == true) {

			sf::Vector2i position = sf::Mouse::getPosition();

			x_pos = position.x - a.getPosition().x - mouse_offset_x;
			y_pos = position.y - a.getPosition().y - mouse_offset_y;

		}
		sf::Vector2f position_2f;

		position_2f.x = x_pos;
		position_2f.y = y_pos;

		setPosition(position_2f);

	}




	void PieceSprite::set_x_pos(float x) {
		x_pos = x;
	}




	void PieceSprite::set_y_pos(float y) {
		y_pos = y;
	}




	float PieceSprite::get_x_pos() {
		return x_pos;
	}




	float PieceSprite::get_y_pos() {
		return y_pos;
	}


}	// closes namespace


