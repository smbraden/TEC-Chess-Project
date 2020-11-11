 /*/-------------------------------------------------------------------------------------//
	Filename:           boardTest.cpp
	Contributors:       Sonja Braden, Jacob Halaweh
	Date:               11/9/2020
	Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
						https://docs.microsoft.com/en-us/windows/win32/LearnWin32/learn-to-program-for-windows
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




const int WINDOW_W = 1400;
const int WINDOW_H = 1200;
const int BOARD_W = 800;
const int BOARD_H = 800;
const char background_filename[] = "Assets/marble2.jpg";
const char board_filename[] = "Assets/Chess_Board.jpg";



int main() {

	// Instantiate ChessBoard object
	ChessBoard testBoard;


	//----------------Graphics Intializations----------------//

	jtest::drawList drawlist;

	// Creating window and objects.
	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "TEC Chess UI");
	window.setFramerateLimit(60);

	// Load the background texture, set the shape, and position it
	sf::Texture background_texture;
	if (!background_texture.loadFromFile(background_filename)) { /*error*/ }
	sf::RectangleShape background_sprite(sf::Vector2f(WINDOW_W, WINDOW_H));
	background_sprite.setTexture(&background_texture);
	background_sprite.setPosition(sf::Vector2f(0, 0));
	background_sprite.setTextureRect(sf::IntRect(0, 0, WINDOW_W, WINDOW_H));


	// Load the board texture, set the shape, and position it
	sf::Texture board_texture;
	if (!board_texture.loadFromFile(board_filename)) { /*error*/ }
	sf::RectangleShape board(sf::Vector2f(BOARD_W, BOARD_H));
	board.setTexture(&board_texture);
	board.setPosition(sf::Vector2f((WINDOW_W - BOARD_W) / 2, (WINDOW_H - BOARD_H) / 2));

	// Shape 2
	sf::CircleShape shape2(30.f);
	shape2.setFillColor(sf::Color::Blue);


	// Create wQueen Sprite object pieces
	sf::Sprite queen_sprite;
	sf::Texture wqTex;
	wqTex.setSmooth(true);
	if (!wqTex.loadFromFile("Assets/WhiteQueen.png")) {	/*error*/ }
	queen_sprite.setTexture(wqTex);
	queen_sprite.setPosition(sf::Vector2f(540, 700));
	

	// Utilizing the drawList class so future shape draws are automated.
	drawlist.setRenderWindow(window);
	drawlist.addShape(background_sprite);
	drawlist.addShape(board);
	drawlist.addSprite(queen_sprite);
	drawlist.addShape(shape2);

	//----------------Graphics Event Loop----------------//

	while (window.isOpen())		// Graphics Event loop
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Right) {
					// event.mouseButton.x;
					// event.mouseButton.y;
				}
			case sf::Event::Closed:
				window.close();
			}



			// Testing mouse functionality.
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			sf::Vector2f mpos;
			mpos.x = localPosition.x - 30;
			mpos.y = localPosition.y - 30;
			shape2.setPosition(mpos);

		}

		// Drawing window and objects.
		window.clear();
		drawlist.draw();
		window.display();

	}		//------------End Event Loop------------//

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



