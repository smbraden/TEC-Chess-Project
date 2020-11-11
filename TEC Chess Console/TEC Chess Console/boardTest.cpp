 /*/-------------------------------------------------------------------------------------//
	Filename:           boardTest.cpp
	Contributors:       Sonja Braden, Jacob Halaweh
	Date:               11/9/2020
	Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
						https://docs.microsoft.com/en-us/windows/win32/LearnWin32/learn-to-program-for-windows
	Description:		A client for testing the chess board class and integrating graphics
//-------------------------------------------------------------------------------------/*/

#include <ctype.h>		// for tolower()
#include "ChessBoard.h"
#include <SFML/Graphics.hpp>
#include "drawList.h"
#include "ChessPieceSprite.h"

//--------------------Backend--------------------//
/*
bool testMove(chess::ChessBoard& argBoard, int x1, int y1, int x2, int y2, bool& flag);
void play(chess::ChessBoard& argBoard, char& option, char& x1, int& y1, char& x2, int& y2);
inline int char2col(char ch);
inline int int2row(int arg);
*/
//--------------------Frontend--------------------//

// void initTextures(sf::Texture* array[], const std::string filenames[]);
// void destroyTextures(sf::Texture* array[]);
void initPieceSprites(chess_ui::PieceSprite* spritePieces[][NUM_TEAM_PIECES]);
void destroyPieceSprites(chess_ui::PieceSprite* spritePieces[][NUM_TEAM_PIECES]);

// void setFirstRankSprite(sf::Sprite* spritePieces[], sf::Texture* array[], chess::team_type team);
// void setSecondRankSprite(sf::Sprite& sp, sf::Texture& tex);

//--------------------Constants--------------------//

const int WINDOW_W = 1400;
const int WINDOW_H = 1200;
const int BOARD_W = 900;
const int BOARD_H = 900;
const int NUM_PIECE_TEXTURES = 12;
const int NUM_TEAM_TEXTURES = 6;
const int NUM_PIECES = 32;
const int NUM_TEAM_PIECES = 16;


const std::string background_filename = "Assets/marble2.jpg";
const std::string board_filename = "Assets/Chess_Board.jpg";
const std::string mouse_follower_filename = "Assets/marble3.jpg";

const std::string PieceFilenames[2][NUM_TEAM_TEXTURES] = {
	{ "Assets/WhiteRook.png", "Assets/WhiteKnight.png", "Assets/WhiteBishop.png",
	  "Assets/WhiteQueen.png","Assets/WhiteKing.png", "Assets/WhitePawn.png" },
	{ "Assets/BlackRook.png", "Assets/BlackKnight.png", "Assets/BlackBishop.png",
	  "Assets/BlackQueen.png", "Assets/BlackKing.png", "Assets/BlackPawn.png" } };

chess_ui::drawList drawlist;



int main() {

	chess_ui::PieceSprite* spritePieces[2][NUM_TEAM_PIECES];
	
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

	//--------------Init Chess Piece Sprites--------------//

	initPieceSprites(spritePieces[2][NUM_TEAM_PIECES]);

	//------------Add Entities to the drawList------------//
	drawlist.setRenderWindow(window);
	drawlist.addShape(background_sprite);
	drawlist.addShape(board);
	drawlist.addShape(mouse_follower);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUM_TEAM_PIECES; j++) {
			sf::Sprite temp = spritePieces[i][j]->getSprite();
			drawlist.addSprite(temp);
		}
	}
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
				destroyPieceSprites(spritePieces[2][NUM_TEAM_PIECES]);
				window.close();
			}

			// Testing mouse functionality.
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			sf::Vector2f mpos;
			mpos.x = localPosition.x - 30;
			mpos.y = localPosition.y - 30;
			mouse_follower.setPosition(mpos);

		}

		// Drawing window and objects.
		window.clear();
		drawlist.draw();
		window.display();

	}		//------------End Event Loop------------//

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
		spritePieces[0][i] = new chess_ui::PieceSprite(PieceFilenames[0][i - 5], x, Wy);
		spritePieces[1][i] = new chess_ui::PieceSprite(PieceFilenames[1][i - 5], x, By);
		x += 100;
	}

	int x = 280;
	int Wy = 780;
	int By = 280;
	for (int i = 8; i < NUM_TEAM_PIECES; i++) {	// all zee wPawns
		spritePieces[0][i] = new chess_ui::PieceSprite(PieceFilenames[0][5], x, Wy);
		spritePieces[0][i] = new chess_ui::PieceSprite(PieceFilenames[0][5], x, By);
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






/*
void initTextures(sf::Texture* array[], const std::string filenames[])
{
	for (int i = 0; i < NUM_PIECE_TEXTURES; i++) {
		array[i] = new sf::Texture;
		if (!array[i]->loadFromFile(filenames[i])) { } // error
	}
}






void destroyTextures(sf::Texture* array[])
{
	for (int i = 0; i < NUM_PIECE_TEXTURES; i++)
		delete array[i];
}
*/






/*
int x = 280;
int Wy = 880;
int By = 180;
for (int i = 0; i < 5; i++) {	// leftiest wRook through wKing
	spritePieces[0][i] = chess_ui::PieceSprite(PieceFilenames[0][i], x, Wy);
	spritePieces[1][i] = chess_ui::PieceSprite(PieceFilenames[1][i], x, By);
	x += 100;
}
for (int i = 5; i < 8; i++) {	// rightiest wBishop through wRook
	spritePieces[0][i] = chess_ui::PieceSprite(PieceFilenames[0][i - 5], x, Wy);
	spritePieces[1][i] = chess_ui::PieceSprite(PieceFilenames[1][i - 5], x, By);
	x += 100;
}

int x = 280;
int Wy = 780;
int By = 280;
for (int i = 8; i < NUM_TEAM_PIECES; i++) {	// all zee wPawns
	spritePieces[0][i] = chess_ui::PieceSprite(PieceFilenames[0][5], x, Wy);
	spritePieces[0][i] = chess_ui::PieceSprite(PieceFilenames[0][5], x, By);
	x += 100;
}
*/










/*
void setFirstRankSprite(sf::Sprite* spritePieces[], sf::Texture* Textures[], chess::team_type team) {
	
	static int x, y;
	if (team == chess::team_type::white) {
		x = 280;
		y = 880;

		spritePieces[0]->setTexture(*Textures[0]);
		spritePieces[0]->setPosition(sf::Vector2f(x, y));
		spritePieces[0]->scale(sf::Vector2f(.5f, .45f)); // absolute scale factor
		drawlist.addSprite(*spritePieces[0]);
	}
	else {
		x = 280;
		y = 180;
	}

	

	x += 100;
}






void setSecondRankSprite(sf::Sprite& sp, sf::Texture& tex) {

	static int x = 280;
	static int y = 780;

	sp.setTexture(tex);
	sp.setPosition(sf::Vector2f(x, y));
	sp.scale(sf::Vector2f(.5f, .5f)); // absolute scale factor	

	drawlist.addSprite(sp);

	x += 100;
}
*/


/*

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






/*
sf::Texture wrTex;
sf::Sprite wRook1_sprite;
setFirstRankSprite(wRook1_sprite, wrTex);

sf::Texture wnTex;
sf::Sprite wKnight1_sprite;
setFirstRankSprite(wKnight1_sprite, wnTex, "Assets/WhiteKnight.png");

sf::Texture wbTex;
sf::Sprite wBishop1_sprite;
setFirstRankSprite(wBishop1_sprite, wbTex, "Assets/WhiteBishop.png");

sf::Texture wqTex;
sf::Sprite wQueen_sprite;
setFirstRankSprite(wQueen_sprite, wqTex, "Assets/WhiteQueen.png");

sf::Texture wkTex;
sf::Sprite wKing_sprite;
setFirstRankSprite(wKing_sprite, wkTex, "Assets/WhiteKing.png");

sf::Sprite wBishop2_sprite;
setFirstRankSprite(wBishop2_sprite, wbTex, "Assets/WhiteBishop.png");

sf::Sprite wKnight2_sprite;
setFirstRankSprite(wKnight2_sprite, wnTex, "Assets/WhiteKnight.png");

sf::Sprite wRook2_sprite;
setFirstRankSprite(wRook2_sprite, wrTex, "Assets/WhiteRook.png");

sf::Texture wpTex;
wpTex.setSmooth(true);
if (!wpTex.loadFromFile("Assets/WhitePawn.png")) {	} // error
sf::Sprite(wPawn1_sprite);
sf::Sprite wPawn2_sprite;
sf::Sprite wPawn3_sprite;
sf::Sprite wPawn4_sprite;
sf::Sprite wPawn5_sprite;
sf::Sprite wPawn6_sprite;
sf::Sprite wPawn7_sprite;
sf::Sprite wPawn8_sprite;
setSecondRankSprite(wPawn1_sprite, wpTex);
setSecondRankSprite(wPawn2_sprite, wpTex);
setSecondRankSprite(wPawn3_sprite, wpTex);
setSecondRankSprite(wPawn4_sprite, wpTex);
setSecondRankSprite(wPawn5_sprite, wpTex);
setSecondRankSprite(wPawn6_sprite, wpTex);
setSecondRankSprite(wPawn7_sprite, wpTex);
setSecondRankSprite(wPawn8_sprite, wpTex);
*/