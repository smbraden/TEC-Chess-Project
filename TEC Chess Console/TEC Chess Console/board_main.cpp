/*/-------------------------------------------------------------------------------------//
	Filename:           board_main.cpp
	Contributors:       Sonja Braden, Jacob Halaweh
	Date:               11/9/2020
	Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
						https://docs.microsoft.com/en-us/windows/win32/LearnWin32/learn-to-program-for-windows
	Description:		A client for testing the chess board class and integrating graphics
//-------------------------------------------------------------------------------------/*/

#include "board_main.h"

int main() {

	// test the build with the back-end object, add dependencies first
	// chess::ChessBoard testBoard;	

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
	board.setFillColor(sf::Color(224, 215, 205));	// darken the board a bit
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
	
	//------------Add Entities to the drawList------------//
	drawlist.setRenderWindow(window);
	drawlist.addShape(background_sprite);
	drawlist.addShape(board);
	drawlist.addShape(mouse_follower);
	// drawlist.addText(text);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUM_TEAM_PIECES; j++) {
			
			chess_ui::PieceSprite* temp = pieces.getPiecePtr(i, j);
			drawlist.addSpritePiece(*temp);
		}
	}




	//----------------Graphics Event Loop----------------//

	while (window.isOpen())		// Graphics Event loop
	{
		sf::Event event;
		sf::Vector2f mpos;
		sf::Vector2i localPosition;
		
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
			
			case sf::Event::Closed:
				window.close();
			
						/*
			case X:

			case Y:		
						*/
			}


			// Pressing escape closes the window
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}
		
		// Drawing window and objects.
		window.clear();
		drawlist.draw();
		window.display();

	}		//------------End Event Loop------------//

	return 0;
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

//------------------End Backend Functions------------------//











/*

These functionalities have been moved to PieceSprite_Set:


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


*/