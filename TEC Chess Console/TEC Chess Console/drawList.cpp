/*/-------------------------------------------------------------------------------------//
	Filename:           drawList.h
	Contributor:        Jacob Halaweh
	Date:               9/26/2020
	Reference:
	Description:		Tests run on graphical integration. Placed in seperate file to be modular.
//-------------------------------------------------------------------------------------/*/

#include "drawList.h"

namespace chess_ui {

	// Initializes the drawList.
	drawList::drawList() {
		shapeObjPtrs = {};
		spriteObjPtrs = {};
		textObjPtrs = {};
		spritePieceObjPtrs = {};
		renderWindowPointer = nullptr;
	}

	// Sets the target render window for this draw list.
	void drawList::setRenderWindow(sf::RenderWindow &window) {
		renderWindowPointer = &window;
	}

	void drawList::addSpritePiece(chess_ui::PieceSprite& pieceObj) {
		spritePieceObjPtrs.push_back(&pieceObj);
	}

	// Adds a shape to the draw list for rendering.
	void drawList::addShape(sf::Shape& shapeObj) {
		shapeObjPtrs.push_back(&shapeObj);
	}

	// Adds a shape to the draw list for rendering.
	void drawList::addSprite(sf::Sprite& spriteObj) {
		spriteObjPtrs.push_back(&spriteObj);
	}

	// Adds text to the draw list for rendering.
	void drawList::addText(sf::Text& textObj) {
		textObjPtrs.push_back(&textObj);
	}



	// Renders all shapes in the list to the targeted render window.
	// This updates, then renders all draggable PieceSprite
	// If a plain old Spite needs to be rendered, then
	// uncomment the comment out loop below
	void drawList::draw() {

		for (int i = 0; i < shapeObjPtrs.size(); i++) {
			renderWindowPointer->draw(*shapeObjPtrs[i]);
		}
		for (int i = 0; i < spriteObjPtrs.size(); i++) {
			renderWindowPointer->draw(*spriteObjPtrs[i]);
		}
		for (int i = 0; i < spritePieceObjPtrs.size(); i++) {
			spritePieceObjPtrs[i]->update(*renderWindowPointer);
			renderWindowPointer->draw(*spritePieceObjPtrs[i]);
		}
		for (int i = 0; i < textObjPtrs.size(); i++) {
			renderWindowPointer->draw(*textObjPtrs[i]);
		}
	}

} // close namespace









