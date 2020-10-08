/*/-------------------------------------------------------------------------------------//
	Filename:           jacobTests.h
	Contributor:        Jacob Halaweh
	Date:               9/26/2020
	Reference:
	Description:		Tests run on grapgical integration. Placed in seperate file to be modular.
//-------------------------------------------------------------------------------------/*/

#ifndef JACOBTESTS_H
#define JACOBTESTS_H


#include "jacobTests.h"
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;


namespace jtest {

	class drawList {

	public:
		drawList();
		void setRenderWindow(sf::RenderWindow &window);
		void addShape(sf::Shape& shapeObj);
		void addSprite(sf::Sprite& shapeObj);
		void draw();

	private:
		vector<sf::Shape*> shapeObjPtrs = {};
		vector<sf::Sprite*> spriteObjPtrs = {};
		sf::RenderWindow* renderWindowPointer;
		
	};


} // jtest namespace end of scope


#endif
