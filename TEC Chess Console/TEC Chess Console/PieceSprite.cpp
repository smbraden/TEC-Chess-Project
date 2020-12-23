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
#include <iostream>		//  for debugging


namespace chess_ui {

	
	// Init Texture with a pinter to another texture
	PieceSprite::PieceSprite(sf::Texture* text, float in_x, float in_y)
	{
		TexturePtr = text;
		setTexture(*TexturePtr); 
		scale(sf::Vector2f(.5f, .45f)); // absolute scale factor	
		
		setPosition(in_x, in_y);
	}



	
	// Init Texture using a filename from projet Images
	PieceSprite::PieceSprite()
	{
		if (!(TexturePtr->loadFromFile("Images/WhitePawn.png"))) {  } // error
		setTexture(*TexturePtr);
		scale(sf::Vector2f(.5f, .45f)); // absolute scale factor	
		
	}






	bool PieceSprite::contains_mouse(sf::RenderWindow& window)
	{
		auto mouse_pos = sf::Mouse::getPosition(window);
		auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
		
		//  getGlobalBounds() returns the bounding box of the entity in the global coordinate system, 
		// i.e. after all of its transformations (position, rotation, scale) have been applied
		boundingBox = getGlobalBounds();
		
		// some adjustments for a more precise bounding box
		boundingBox.left += 40;
		boundingBox.top += 20;
		boundingBox.width /= 3;
		boundingBox.height = (boundingBox.height * 2) / 3;
		
		return boundingBox.contains(translated_pos);
	}






	//-----------------Draggable-----------------//
	
	void PieceSprite::update(sf::RenderWindow& window) {

		float x_pos = getPosition().x;
		float y_pos = getPosition().y;
		
		// Get true mouse position, taking window repositioning into account. 
		// Does not account for window rescaling or skew.
		int mouse_x = sf::Mouse::getPosition().x - window.getPosition().x;
		int mouse_y = sf::Mouse::getPosition().y - window.getPosition().y;
				
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && contains_mouse(window)) {

			// For debugging
			// std::cout << "Top:   " << boundingBox.top << "	Left: " << boundingBox.left << std::endl;
			// std::cout << "Width: " << boundingBox.width << "	Height: " << boundingBox.height << std::endl;

			if (flag_first_click == true) {
				dragging = true;
				mouse_offset_x = mouse_x - getPosition().x;
				mouse_offset_y = mouse_y - getPosition().y;

				flag_first_click = false;
			}
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			 dragging = false;
			 flag_first_click = true;
		}
		else {
			flag_first_click = false;
		}

		if (dragging == true) {

			sf::Vector2i position = sf::Mouse::getPosition();
			
			x_pos = position.x - window.getPosition().x - mouse_offset_x;
			y_pos = position.y - window.getPosition().y - mouse_offset_y;

		}
		sf::Vector2f position_2f;

		position_2f.x = x_pos;
		position_2f.y = y_pos;

		setPosition(position_2f);
		
	}
	
}	// closes namespace




