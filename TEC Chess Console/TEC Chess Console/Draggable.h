/*/-------------------------------------------------------------------------------------//
	Filename:           Draggable.h
	Contributor:        Jacob Halaweh
	Date:               11/13/2020
	Reference:
	Description:		An example of how to implement draggable objects with SFML
//-------------------------------------------------------------------------------------/*/
#ifndef DRAGGABLE_H
#define DRAGGABLE_H

// #include <vector>
#include <SFML/Graphics.hpp>


namespace chess_ui {

	class draggable {

	public:
		void initialize();
		void set_width_height(int a, int b);
		void set_color(int r, int g, int b, int alpha);
		void update(sf::RenderWindow& a);
		void set_x_pos(int x);
		void set_y_pos(int y);
		float get_x_pos();
		float get_y_pos();
		int get_width();
		int get_height();
		sf::RectangleShape* getShape();
		void draw_draggable(sf::RenderWindow& a);

	private:
		sf::RectangleShape shape;
		int width = 0, height = 0;
		float origin_x = 0, origin_y = 0, x_pos = 0, y_pos = 0, mouse_offset_x = 0, mouse_offset_y = 0;
		bool dragging = false, flag_first_click = true;
		sf::Color color = sf::Color(222, 222, 255, 255);

	};

}	// closes namespace

#endif

