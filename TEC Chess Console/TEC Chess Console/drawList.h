/*/-------------------------------------------------------------------------------------//
	Filename:           drawList.h
	Contributor:        Jacob Halaweh
	Date:               9/26/2020
	Reference:
	Description:		Tests run on graphical integration. Placed in seperate file to be modular.
//-------------------------------------------------------------------------------------/*/

#ifndef JACOBTESTS_H
#define JACOBTESTS_H

#include <vector>
#include <SFML/Graphics.hpp>


namespace chess_ui {

	class drawList {

	public:
		drawList();
		void setRenderWindow(sf::RenderWindow &window);
		void addShape(sf::Shape& shapeObj);
		void addSprite(sf::Sprite& shapeObj);
		void draw();

	private:
		std::vector<sf::Shape*> shapeObjPtrs;
		std::vector<sf::Sprite*> spriteObjPtrs;
		sf::RenderWindow* renderWindowPointer;
		
	};


} // drawList namespace end of scope


#endif
