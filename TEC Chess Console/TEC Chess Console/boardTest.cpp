 /*/-------------------------------------------------------------------------------------//
	Filename:           boardTest.cpp
	Contributors:       Sonja Braden, Jacob Halaweh
	Date:               11/9/2020
	Reference:
	Description:		A client for testing the chess board class and integrating graphics
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include <ctype.h>		// for tolower()
#include "ChessBoard.h"
#include <SFML/Graphics.hpp>
#include "jacobTests.h"

using namespace std;
using namespace chess;


bool testMove(ChessBoard& argBoard, int x1, int y1, int x2, int y2, bool& flag);
void play(ChessBoard& argBoard, char& option, char& x1, int& y1, char& x2, int& y2);
inline int char2col(char ch);
inline int int2row(int arg);



int main() {

	char x1 = 'a';
	int y1 = 1;
	char x2 = 'a';
	int y2 = 1; 
	char option = 'c';

	ChessBoard testBoard;
	testBoard.printBoard();
	cout << endl << endl;

	cout << "Welcome to the TEC Chess Test Console!" << endl;
	cout << "To enter moves, use the format 'ColRow': a7, b3, etc" << endl;
	cout << "Don't hit 'enter' without any input. This is a quick n dirty test that will break." << endl;
	cout << "Enter 'q' to exit at the continue/quit prompt after each round" << endl;
	cout << "Play? Hit quit/continue now (q/c): ";
	cin >> option;
	cout << endl;

	if (option == 'q')
		return 0;
	else {
		play(testBoard, option, x1, y1, x2, y2);
	}

	//-----------------------Graphics-----------------------//

	jtest::drawList drawlist;

	// Creating window and objects.
	sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML works!");
	window.setFramerateLimit(60);

	// Shape objects
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::CircleShape shape2(30.f);
	shape2.setFillColor(sf::Color::Blue);
	sf::RectangleShape shape3;
	sf::Vector2f sizing;
	sizing.x = 30;
	sizing.y = 30;
	sf::Vector2f pos;
	pos.x = 300;
	pos.y = 300;
	shape3.setSize(sizing);
	shape3.setFillColor(sf::Color::Blue);
	shape3.setPosition(pos);


	// Sprite object test
	sf::Texture wqTex;
	if (!wqTex.loadFromFile("Images/WhiteQueen.png"))
	{
		// error...
	}
	sf::Sprite sprite;
	sprite.setTexture(wqTex);
	sf::Vector2f wqpos;
	wqpos.x = 500;
	wqpos.y = 300;
	sprite.setPosition(wqpos);

	// Utilizing the drawList class so future shape draws are automated.
	drawlist.setRenderWindow(window);
	drawlist.addShape(shape);
	drawlist.addShape(shape2);
	drawlist.addShape(shape3);
	drawlist.addSprite(sprite);

	// Graphics while loop begins.           <----------------- Normal terminal stuff wont work past here because graphics is running. Game must be contained in this While-Loop!
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Testing mouse functionality.
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			sf::Vector2f mpos;
			mpos.x = localPosition.x - 30;
			mpos.y = localPosition.y - 30;
			shape2.setPosition(mpos);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Drawing window and objects.
		window.clear();
		drawlist.draw();
		window.display();
	}


	return 0;
}







bool testMove(ChessBoard& argBoard, int x1, int y1, int x2, int y2, bool& flag)
{
	try {

		argBoard.move(x1, y1, x2, y2);
		cout << endl;
		argBoard.printBoard();
		cout << endl;
		return true;
	}
	catch (const chess_except::InvalidMoveExcep& e) {
		cout << e.getMsg() << endl << endl;
	}
	catch (const chess_except::DrawSignal& e) {
		cout << e.getMsg() << endl << endl;
		flag = true;
		return true;
	}
	catch (const chess_except::WinSignal& e) {
		cout << e.getMsg() << endl << endl;
		flag = true;
		return true;
	}

	return false;
}







void play(ChessBoard& argBoard, char& option, char& x1, int& y1, char& x2, int& y2)
{
	bool endFlag = false;

	do {

		do {
			
			string team = (argBoard.getTurnTeam() == team_type::white) ? "White" : "Black";

			cout << team << " move. Current position:	";
			cin >> x1 >> y1;
			cout << team << " move. New position:	";
			cin >> x2 >> y2;
			cout << endl;
			
		} while (!testMove(argBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2), endFlag));

		if (endFlag)
			break;

		// Continue prompt
		cout << "quit or continue (q/c):	";
		cin >> option;
		cout << endl;
		if (option == 'q')
			break;

	} while (tolower(option) != 'q' && !endFlag);

	argBoard.printBoard();	// the final print will not execute (win or draw signaled by exception)
}






inline int char2col(char ch)
{
	return (tolower(ch) - 97);
}






inline int int2row(int arg)
{
	return (arg - 1);
}



