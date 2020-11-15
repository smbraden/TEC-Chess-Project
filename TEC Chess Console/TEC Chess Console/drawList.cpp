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
		/* for (int i = 0; i < spritePieceObjPtrs.size(); i++) {
			renderWindowPointer->draw(*spritePieceObjPtrs[i]);
		} */
		for (int i = 0; i < spritePieceObjPtrs.size(); i++) {
			spritePieceObjPtrs[i]->update(*renderWindowPointer);
			renderWindowPointer->draw(*spritePieceObjPtrs[i]);
		}
		for (int i = 0; i < textObjPtrs.size(); i++) {
			renderWindowPointer->draw(*textObjPtrs[i]);
		}
	}

} // jtest namespace end of scope


/*

To demo, add the following codde before the graphics event loop, while (window.isOpen())

////////////////////////////////////////////////////////////////////////////////////////
//------------Draggable object example (Deletable, here for demonstration)------------//
chess_ui::draggable draggable_box;
draggable_box.initialize();
draggable_box.set_width_height(32,32);
draggable_box.set_color(255, 0, 255, 255);
draggable_box.set_x_pos(50);
draggable_box.set_y_pos(100);
drawlist.addShape(*draggable_box.getShape());
// If deleted, remove the "draggable_box.update(window);" 
// from the graphics event loop. Searching this quote will find it.
////////////////////////////////////////////////////////////////////////////////////////


Also inclide this update to the object at the end of every go of the loop

// Update the draggable box demo
draggable_box.update(window);


*/







