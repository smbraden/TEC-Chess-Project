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
	window.setView(sf::View(sf::FloatRect((BACKGROUND_W - WINDOW_W) / 2, 
		(BACKGROUND_H - WINDOW_H) / 2, WINDOW_W, WINDOW_H)));
		
	// Creating background
	sf::Texture background_texture;
	if (!background_texture.loadFromFile(background_filename)) { /*error*/ }
	sf::RectangleShape background_shape(sf::Vector2f(BACKGROUND_W, BACKGROUND_H));
	background_shape.setTexture(&background_texture);
	background_shape.setPosition(sf::Vector2f(0, 0));
	
	// Creating board
	sf::Texture board_texture;
	if (!board_texture.loadFromFile(board_filename)) { /*error*/ }
	sf::RectangleShape board(sf::Vector2f(BOARD_W, BOARD_H));
	board.setTexture(&board_texture);
	board.setFillColor(sf::Color(224, 215, 205));	// darken the board a bit
	board.setPosition(BOARD_POS);

	// Creating mouse follower 
	// sf::Texture mouse_follower_texture;
	// if (!mouse_follower_texture.loadFromFile(mouse_follower_filename)) { /*error*/ }
	// sf::CircleShape mouse_follower(30.f);
	// mouse_follower.setTexture(&mouse_follower_texture);
	// mouse_follower.setTextureRect(sf::IntRect(10, 10, 100, 100));
	
	// Create text
	// sf::Font font;
	// if (!font.loadFromFile(font1_filename))	{ /* error */ }
	// sf::Text text;
	// text.setFont(font); // font is a sf::Font
	// std::string msg;
	// msg = "Hello world.\n";
	// text.setString(msg);
	// text.setCharacterSize(24); // in pixels, not points!
	// text.setFillColor(sf::Color::Black);
	
	//------------Add Entities to the drawList------------//
	drawlist.setRenderWindow(window);
	drawlist.addShape(background_shape);
	drawlist.addShape(board);
	// drawlist.addShape(mouse_follower);
	// drawlist.addText(text);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUM_TEAM_PIECES; j++) {
			
			chess_ui::PieceSprite* temp = pieces_set.getPiecePtr(i, j);
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
			/*
			// Testing mouse functionality.
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			sf::Vector2f mouse_pos;
			mouse_pos = sf::Vector2f(localPosition.x, localPosition.y) - sf::Vector2f(30, 30);
			mouse_follower.setPosition(mouse_pos);		// set the mouse follower position
			*/

			switch (event.type) {
			
			case sf::Event::Closed :
				window.close();
			case sf::Event::Resized :
			{
				resize_adjust_view(event, window);			
			}
				
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





//------------------Frontend main() Functions------------------//


void resize_adjust_view(const sf::Event& event, sf::RenderWindow& window)
{
	// when the window is expanded beyond initial dimensions
	if (event.size.height >= WINDOW_H && event.size.width >= WINDOW_W) {

		// keep the view centered on the board
		window.setView(sf::View(sf::Vector2f(BACKGROUND_W / 2, BACKGROUND_H / 2),
			sf::Vector2f(event.size.width, event.size.height)));
	} 	// when the window is still larger than the board
	else if ((event.size.height < WINDOW_H || event.size.width < WINDOW_W) &&
		(event.size.height > BOARD_H && event.size.width > BOARD_W)) {

		// keep the view centered on the board
		window.setView(sf::View(sf::Vector2f(BACKGROUND_W / 2, BACKGROUND_H / 2),
			sf::Vector2f(event.size.width, event.size.height)));

	} // when the window is only WIDER than the board, but not taller
	else if (event.size.height < BOARD_H && event.size.width >= BOARD_W) {

		window.setView(sf::View(sf::FloatRect((BACKGROUND_W - event.size.width) / 2, BOARD_POS.y,
			event.size.width, event.size.height)));

	} // when the window is only TALLER than the board, but not wider
	else if (event.size.width < BOARD_W && event.size.height >= BOARD_H) {

		window.setView(sf::View(sf::FloatRect(BOARD_POS.x, (BACKGROUND_H - event.size.height) / 2,
			event.size.width, event.size.height)));

	} // when the window is smaller than the board in both dimensions
	else {
		window.setView(sf::View(sf::FloatRect(BOARD_POS.x, BOARD_POS.y,
			event.size.width, event.size.height)));
	}
}





/*

//------------------Backend main() Functions------------------//



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

