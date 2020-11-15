/*/-------------------------------------------------------------------------------------//
	Filename:           drawList.h
	Contributor:        Jacob Halaweh
	Date:               11/13/2020
	Reference:
	Description:		Tests run on graphical integration. Placed in seperate file to be modular.
//-------------------------------------------------------------------------------------/*/

#ifndef DRAWLIST_H
#define DRAWLIST_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "PieceSprite.h"


namespace chess_ui {

	class drawList {

	public:
		drawList();
		void setRenderWindow(sf::RenderWindow &window);
		void addSpritePiece(chess_ui::PieceSprite& pieceObj);
		void addSprite(sf::Sprite& shapeObj);
		void addShape(sf::Shape& shapeObj);
		void addText(sf::Text& textObj);
		void draw();

	private:
		std::vector<sf::Shape*> shapeObjPtrs;
		std::vector<chess_ui::PieceSprite*> spritePieceObjPtrs;
		std::vector<sf::Sprite*> spriteObjPtrs;
		std::vector<sf::Text*> textObjPtrs;
		sf::RenderWindow* renderWindowPointer;
		
	};


} // drawList namespace end of scope


#endif
