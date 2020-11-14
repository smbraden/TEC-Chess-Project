 /*/-------------------------------------------------------------------------------------//
	Filename:           board_main.cpp
	Contributors:       Sonja Braden, Jacob Halaweh
	Date:               11/9/2020
	Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
						https://docs.microsoft.com/en-us/windows/win32/LearnWin32/learn-to-program-for-windows
	Description:		A client for testing the chess board class and integrating graphics
//-------------------------------------------------------------------------------------/*/

#include "board_main.h"
#include <string.h>

int main() {

	// chess::ChessBoard testBoard;	// test the build with the back-end object

	//----------------Graphics Intializations----------------//

	// Creating window and objects.
	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "TEC Chess UI");
	window.setFramerateLimit(60);
	
	// Creating background
	sf::Texture background_texture;
	if (!background_texture.loadFromFile(background_filename)) { /*error*/ }
	sf::RectangleShape background_sprite(sf::Vector2f(WINDOW_W, WINDOW_H));
	background_sprite.setTexture(&background_texture);
	background_sprite.setPosition(sf::Vector2f(0, 0));
	background_sprite.setTextureRect(sf::IntRect(0, 0, WINDOW_W, WINDOW_H));

	// Creating board
	sf::Texture board_texture;
	if (!board_texture.loadFromFile(board_filename)) { /*error*/ }
	sf::RectangleShape board(sf::Vector2f(BOARD_W, BOARD_H));
	board.setTexture(&board_texture);
	board.setPosition(sf::Vector2f((WINDOW_W - BOARD_W) / 2, (WINDOW_H - BOARD_H) / 2));

	// Creating mouse follower
	sf::Texture mouse_follower_texture;
	if (!mouse_follower_texture.loadFromFile(mouse_follower_filename)) { /*error*/ }
	sf::CircleShape mouse_follower(30.f);
	mouse_follower.setTexture(&mouse_follower_texture);
	mouse_follower.setTextureRect(sf::IntRect(10, 10, 100, 100));

	// Create text
	sf::Font font;
	if (!font.loadFromFile(font1_filename))	{ /* error */ }
	sf::Text text;
	text.setFont(font); // font is a sf::Font
	std::string msg;
	msg = "Hello world.\n";
	text.setString(msg);
	text.setCharacterSize(24); // in pixels, not points!
	text.setFillColor(sf::Color::Black);
	
	//--------------Init Chess Piece Sprites--------------//

	initPieceSprites(spritePieces);

	//------------Add Entities to the drawList------------//
	drawlist.setRenderWindow(window);
	drawlist.addShape(background_sprite);
	drawlist.addShape(board);
	drawlist.addShape(mouse_follower);
	// drawlist.addText(text);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUM_TEAM_PIECES; j++) {
			sf::Sprite* temp = spritePieces[i][j];
			drawlist.addSprite(*temp);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////
	//------------Draggable object example (Deletable, here for demonstration)------------//
	chess_ui::draggable draggable_box;
	draggable_box.initialize();
	draggable_box.set_width_height(32,32);
	draggable_box.set_color(255, 0, 255, 255);
	draggable_box.set_x_pos(50);
	draggable_box.set_y_pos(100);
	drawlist.addShape(*draggable_box.getShape());
	// If deleted, remove the "draggable_box.update(window);" from the graphics event loop. Searching this quote will find it.
	////////////////////////////////////////////////////////////////////////////////////////


	//----------------Graphics Event Loop----------------//

	while (window.isOpen())		// Graphics Event loop
	{
		sf::Event event;
		sf::Vector2f mpos;
		sf::Vector2i localPosition;
		// int x_click;
		// int y_click;
		// int x_released;
		// int y_released;
		
		sf::Sprite* clicked = nullptr;

		while (window.pollEvent(event))
		{
			// Testing mouse functionality.
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			sf::Vector2f mpos;
			mpos.x = localPosition.x - 30;
			mpos.y = localPosition.y - 30;
			mouse_follower.setPosition(mpos);
			
			switch (event.type) {
			/*
			case sf::Event::MouseButtonPressed:
				
				if ((clicked = getClickedPiece(event.mouseButton.x, event.mouseButton.y)) != nullptr) {
					localPosition = sf::Mouse::getPosition(window);
					clicked->setPosition(localPosition.x, localPosition.y);
				}	
				break;

			case sf::Event::MouseButtonReleased:

				if (clicked != nullptr) {
					clicked->setPosition(event.mouseButton.x, event.mouseButton.y);
					clicked = nullptr;
				}
				break;
				*/
			case sf::Event::Closed:
				
				window.close();
			}


			// Pressing escape closes the window
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}

		}

		// Update the draggable box demo
		draggable_box.update(window);

		// Drawing window and objects.
		window.clear();
		drawlist.draw();
		window.display();

	}		//------------End Event Loop------------//

	destroyPieceSprites(spritePieces);

	return 0;
}






// Dimensions		spritePieces[2][NUM_TEAM_PIECES]
void initPieceSprites(chess_ui::PieceSprite* spritePieces[][NUM_TEAM_PIECES])
{
	int x = 280;
	int Wy = 880;
	int By = 180;
	for (int i = 0; i < 5; i++) {	// leftiest wRook through wKing
		spritePieces[0][i] = new chess_ui::PieceSprite(PieceFilenames[0][i], x, Wy);
		spritePieces[1][i] = new chess_ui::PieceSprite(PieceFilenames[1][i], x, By);
		x += 100;
	}
	for (int i = 5; i < 8; i++) {	// rightiest wBishop through wRook
		spritePieces[0][i] = new chess_ui::PieceSprite(PieceFilenames[0][7 - i], x, Wy);
		spritePieces[1][i] = new chess_ui::PieceSprite(PieceFilenames[1][7 - i], x, By);
		x += 100;
	}

	x = 280;
	Wy = 780;
	By = 280;
	for (int i = 8; i < NUM_TEAM_PIECES; i++) {	// all zee wPawns
		spritePieces[0][i] = new chess_ui::PieceSprite(PieceFilenames[0][5], x, Wy);
		spritePieces[1][i] = new chess_ui::PieceSprite(PieceFilenames[1][5], x, By);
		x += 100;
	}
}







void destroyPieceSprites(chess_ui::PieceSprite* spritePieces[][NUM_TEAM_PIECES])
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUM_TEAM_PIECES; j++) {
			delete spritePieces[i][j];
		}
	}
}






sf::Sprite* getClickedPiece(int x_click, int y_click)
{
	for (int i = 0; i < NUM_TEAM_PIECES; i++) {
		for (int j = 0; j < NUM_TEAM_PIECES; j++) {
			if (spritePieces[i][j] != nullptr && spritePieces[i][j]->contains(x_click, y_click)) {
				return spritePieces[i][j];
			}
		}
	}	// completed loop without any bounding boxes detected in the click zone
	return nullptr;
}












/*

//------------------Backend Functions------------------//



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
			
			std::string team = (argBoard.getTurnTeam() == chess::team_type::white) ? "White" : "Black";

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
*/


