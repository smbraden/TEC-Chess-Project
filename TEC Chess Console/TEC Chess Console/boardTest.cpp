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

// using namespace std;
// using namespace chess;


bool testMove(chess::ChessBoard& argBoard, int x1, int y1, int x2, int y2, bool& flag);
void play(chess::ChessBoard& argBoard, char& option, char& x1, int& y1, char& x2, int& y2);
inline int char2col(char ch);
inline int int2row(int arg);

const int WINDOW_W = 1400;
const int WINDOW_H = 1200;
const int BOARD_W = 900;
const int BOARD_H = 900;
const char background_filename[] = "Assets/marble2.jpg";
const char board_filename[] = "Assets/Chess_Board.jpg";

jtest::drawList drawlist;

void setSpritePiece(sf::Sprite& sp, sf::Texture& tex, const char filename[]);


int main() {

	// Instantiate ChessBoard object
	chess::ChessBoard testBoard;


	//----------------Graphics Intializations----------------//

	

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


	// Utilizing the drawList class so future shape draws are automated.
	drawlist.setRenderWindow(window);
	drawlist.addShape(background_sprite);
	drawlist.addShape(board);
	drawlist.addShape(shape2);

	sf::Texture wrTex;
	sf::Sprite wRook1_sprite;
	setSpritePiece(wRook1_sprite, wrTex, "Assets/WhiteRook.png");

	sf::Texture wnTex;
	sf::Sprite wKnight1_sprite;
	setSpritePiece(wKnight1_sprite, wnTex, "Assets/WhiteKnight.png");

	sf::Texture wbTex;
	sf::Sprite wBishop1_sprite;
	setSpritePiece(wBishop1_sprite, wbTex, "Assets/WhiteBishop.png");

	sf::Texture wqTex;
	sf::Sprite wQueen_sprite;
	setSpritePiece(wQueen_sprite, wqTex, "Assets/WhiteQueen.png");

	sf::Texture wkTex;
	sf::Sprite wKing_sprite;
	setSpritePiece(wKing_sprite, wkTex, "Assets/WhiteKing.png");

	sf::Sprite wBishop2_sprite;
	setSpritePiece(wBishop2_sprite, wbTex, "Assets/WhiteBishop.png");

	sf::Sprite wKnight2_sprite;
	setSpritePiece(wKnight2_sprite, wnTex, "Assets/WhiteKnight.png");

	sf::Sprite wRook2_sprite;
	setSpritePiece(wRook2_sprite, wrTex, "Assets/WhiteRook.png");
	


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





void setSpritePiece(sf::Sprite& sp, sf::Texture& tex, const char filename[] ) {
	
	static int x = 280;
	static int y = 880;

	// Create wQueen Sprite object pieces
	tex.setSmooth(true);
	if (!tex.loadFromFile(filename)) {	/*error*/ }
	sp.setTexture(tex);
	sp.setPosition(sf::Vector2f(x, y));
	sp.scale(sf::Vector2f(.5f, .45f)); // absolute scale factor	

	drawlist.addSprite(sp);

	x += 100;
}






bool testMove(chess::ChessBoard& argBoard, int x1, int y1, int x2, int y2, bool& flag)
{
	try {

		argBoard.move(x1, y1, x2, y2);
		std::cout << std::endl;
		argBoard.printBoard();
		std::cout << std::endl;
		return true;
	}
	catch (const chess_except::InvalidMoveExcep& e) {
		std::cout << e.getMsg() << "\n\n";
	}
	catch (const chess_except::DrawSignal& e) {
		std::cout << e.getMsg() << "\n\n";
		flag = true;
		return true;
	}
	catch (const chess_except::WinSignal& e) {
		std::cout << e.getMsg() << "\n\n";
		flag = true;
		return true;
	}

	return false;
}







void play(chess::ChessBoard& argBoard, char& option, char& x1, int& y1, char& x2, int& y2)
{
	bool endFlag = false;

	do {

		do {
			
			string team = (argBoard.getTurnTeam() == chess::team_type::white) ? "White" : "Black";

			std::cout << team << " move. Current position:	";
			std::cin >> x1 >> y1;
			std::cout << team << " move. New position:	";
			std::cin >> x2 >> y2;
			std::cout << "\n";
			
		} while (!testMove(argBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2), endFlag));

		if (endFlag)
			break;

		// Continue prompt
		std::cout << "quit or continue (q/c):	";
		std::cin >> option;
		std::cout << "\n";
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







//	wqTex.setSmooth(true);
//	if (!wqTex.loadFromFile("Assets/WhiteQueen.png")) {	/*error*/ }
/*	queen_sprite.setTexture(wqTex);
	queen_sprite.setPosition(sf::Vector2f(580, 880));
	queen_sprite.scale(sf::Vector2f(.5f, .5f)); // absolute scale factor	*/