/*/-------------------------------------------------------------------------------------//
	Filename:           Draggable.cpp
	Contributor:        Jacob Halaweh
	Date:               11/13/2020
	Reference:
	Description:		An example of how to implement draggable objects with SFML
//-------------------------------------------------------------------------------------/*/
#include "Draggable.h"

namespace chess_ui {

	void draggable::initialize() {
		shape.setFillColor(color);
	}




	void draggable::set_width_height(int a, int b) {
		width = a;
		height = b;
		shape.setSize(sf::Vector2f(a, b));

		origin_x = 8;	// Rectangle shape seems to need offsetting for proper bounding... not sure why.
		origin_y = 32;	// Rectangle shape seems to need offsetting for proper bounding... not sure why.
		shape.setOrigin(sf::Vector2f(origin_x, origin_y));
	}




	void draggable::set_color(int r, int g, int b, int alpha) {
		color = sf::Color(r, g, b, alpha);
		shape.setFillColor(color);
	}





	void draggable::update(sf::RenderWindow& a) {

		// Get true mouse position, taking window repositioninginto account. Does not account for window rescaling or skew.
		int mouse_x = sf::Mouse::getPosition().x - a.getPosition().x;
		int mouse_y = sf::Mouse::getPosition().y - a.getPosition().y;


		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (mouse_x > x_pos) && (mouse_x < x_pos + width) && (mouse_y > y_pos) && (mouse_y < y_pos + height)) {

			if (flag_first_click == true) {
				dragging = true;
				mouse_offset_x = mouse_x - shape.getPosition().x;
				mouse_offset_y = mouse_y - shape.getPosition().y;
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

		shape.setPosition(position_2f);

	}




	void draggable::set_x_pos(int x) {
		x_pos = x;
	}




	void draggable::set_y_pos(int y) {
		y_pos = y;
	}




	float draggable::get_x_pos() {
		return x_pos;
	}




	float draggable::get_y_pos() {
		return y_pos;
	}




	int draggable::get_width() {
		return shape.getSize().x;
	}




	int draggable::get_height() {
		return shape.getSize().y;
	}




	sf::RectangleShape* draggable::getShape() {
		return &shape;
	}




	void draggable::draw(sf::RenderWindow& a) {

		a.draw(shape);
	}




	void draggable::draw_draggable(sf::RenderWindow& a) {

		a.draw(shape);
	}

}	// closes namespace


