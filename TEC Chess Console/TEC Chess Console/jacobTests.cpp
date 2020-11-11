/*/-------------------------------------------------------------------------------------//
	Filename:           jacobTests.h
	Contributor:        Jacob Halaweh
	Date:               9/26/2020
	Reference:
	Description:		Tests run on graphical integration. Placed in seperate file to be modular.
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include "jacobTests.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

namespace jtest {

	// Initializes the drawList.
	drawList::drawList() {
		// Initialize
	}

	// Sets the target render window for this draw list.
	void drawList::setRenderWindow(sf::RenderWindow &window) {
		renderWindowPointer = &window;
		
	}

	// Adds a shape to the draw list for rendering.
	void drawList::addShape(sf::Shape& shapeObj) {
		shapeObjPtrs.push_back(&shapeObj);
	}

	// Adds a shape to the draw list for rendering.
	void drawList::addSprite(sf::Sprite& spriteObj) {
		spriteObjPtrs.push_back(&spriteObj);
	}


	// Renders all shapes in the list to the targeted render window.
	void drawList::draw() {

		for (int i = 0; i < shapeObjPtrs.size(); i++) {
			renderWindowPointer->draw(*shapeObjPtrs[i]);
		}
		for (int i = 0; i < spriteObjPtrs.size(); i++) {
			renderWindowPointer->draw(*spriteObjPtrs[i]);
		}
	}

} // jtest namespace end of scope








