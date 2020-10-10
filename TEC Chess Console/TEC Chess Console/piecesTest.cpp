/*/-------------------------------------------------------------------------------------//
	Filename:           piecesTest.cpp
	Contributors:       Sonja Braden
	Date:               9/22/2020
	Reference:
	Description:		Testing the derived chess piece classes
//-------------------------------------------------------------------------------------/*/


#include <iostream>
#include "DerivedPieces.h"
#include <SFML/Graphics.hpp>
#include "jacobTests.h"
using namespace std;
using namespace chess;


const int SIZE = 8;


void WpawnTest(ChessPiece& pawn);
void BpawnTest(ChessPiece& pawn);
void castleTest(ChessPiece& castle);
void knightTest(ChessPiece& knight);
void rookTest(ChessPiece& rook);
void queenTest(ChessPiece& queen);
void kingTest(ChessPiece& king);

// Test
int main() {
	
	ChessPiece a;
	Pawn pW(0, 1);
	Pawn pB(4, 5, ChessPiece::black);
	Castle cB(6, 6, ChessPiece::black);
	Knight n;
	Rook r;
	Queen Q;
	King K;

	ChessPiece Arr[SIZE] = { a, pW, pB, cB, n, r, Q, K };

	for (int i = 0; i < SIZE; i++) {
			
		cout << Arr[i].getPieceType() << "  " << Arr[i].getTeamType() << endl;
	}
	cout << endl << endl;


	WpawnTest(pW);
	BpawnTest(pB);
	castleTest(cB);
	knightTest(n);
	rookTest(r);
	queenTest(Q);
	kingTest(K);



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






void WpawnTest(ChessPiece& pawn)
{

	int row;
	int col;

	cout << "Testing white Pawn move exceptions: expecting 2 exceptions..." << endl;

	pawn.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;

	try {
		pawn.setPosition(0, 3);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Forward 2 on first move. This move should NOT throw an exception." << endl;
	}

	try {
		pawn.setPosition(0, 4);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		pawn.setPosition(1, 4);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	try {
		pawn.setPosition(0, 3);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	try {
		pawn.setPosition(0, 5);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid Pawn move. This move should NOT throw an exception." << endl;
	}

	pawn.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;

}






void BpawnTest(ChessPiece& pawn)
{
	int col;
	int row;
	
	cout << endl;
	cout << "Testing black Pawn move exceptions: expecting 2 exceptions..." << endl;

	pawn.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;

	try {
		pawn.setPosition(4, 3);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Forward 2 on first move. This move should NOT throw an exception." << endl;
	}

	try {
		pawn.setPosition(4, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		pawn.setPosition(5, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	try {
		pawn.setPosition(4, 1);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		pawn.setPosition(4, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid Pawn move. This move SHOULD throw an exception." << endl;
	}

	pawn.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;


}







void castleTest(ChessPiece& castle)
{

	int col;
	int row;

	cout << endl;
	cout << "Testing Castle move exceptions: expecting 1 exceptions..." << endl;

	castle.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;

	try {
		castle.setPosition(5, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid Castle move. This move SHOULD throw an exception." << endl;
	}

	try {
		castle.setPosition(6, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Move along a column. This move should NOT throw an exception." << endl;
	}

	try {
		castle.setPosition(6, 4);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Move along a row. This move should NOT throw an exception." << endl;
	}

	castle.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;

}







void knightTest(ChessPiece& knight)
{
	int col;
	int row;

	cout << endl;
	cout << "Testing Knight move exceptions: expecting 1 exceptions..." << endl;

	knight.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;	// (1, 0)

	try {
		knight.setPosition(0, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Valid Knight move. This move should NOT throw an exception." << endl;
	}

	try {
		knight.setPosition(2, 3);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Valid Knight move. This move should NOT throw an exception." << endl;
	}

	try {
		knight.setPosition(1, 1);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Valid Knight move. This move should NOT throw an exception." << endl;
	}

	try {
		knight.setPosition(3, 3);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid Knight move. This move SHOULD throw an exception." << endl;
	}

	knight.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;

}






void rookTest(ChessPiece& rook)
{
	int col;
	int row;

	cout << endl;
	cout << "Testing Rook move exceptions: expecting 2 exceptions..." << endl;

	rook.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;	// (2, 0)

	try {
		rook.setPosition(2, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid Rook move. This move SHOULD throw an exception." << endl;
	}

	try {
		rook.setPosition(4, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		rook.setPosition(1, 5);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "This move should NOT throw an exception." << endl;
	}

	try {
		rook.setPosition(6, 4);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid Rook move. This move SHOULD throw an exception." << endl;
	}

	rook.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;


}







void queenTest(ChessPiece& queen)
{
	int col;
	int row;

	cout << endl;
	cout << "Testing Queen move exceptions: expecting 1 exceptions..." << endl;

	queen.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl;	// (3 , 0)

	try {
		queen.setPosition(6, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid Queen move. This move SHOULD throw an exception." << endl;
	}

	try {
		queen.setPosition(5, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Move on a diagonal. This move should NOT throw an exception." << endl;
	}

	try {
		queen.setPosition(0, 2);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Move along a row. This move should NOT throw an exception." << endl;
	}

	try {
		queen.setPosition(0, 1);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Move along a col. This move should NOT throw an exception." << endl;
	}

	queen.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;

}






void kingTest(ChessPiece& king)
{
	int col;
	int row;

	cout << endl;
	cout << "Testing King move exceptions: expecting 1 exceptions..." << endl;

	king.getPosition(col, row);
	cout << "Initial position: ( " << col << ", " << row << " )" << endl; // (4, 0)

	try {
		king.setPosition(6, 0);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Invalid King move. This move SHOULD throw an exception." << endl;
	}

	try {
		king.setPosition(5, 1);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Move on diagonal. This move should NOT throw an exception." << endl;
	}

	try {
		king.setPosition(4, 1);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Move along a row. This move should NOT throw an exception." << endl;
	}

	try {
		king.setPosition(3, 1);
	}
	catch (ChessPiece::PieceMoveError e) {
		cout << "Move along a col. This move should NOT throw an exception." << endl;
	}

	king.getPosition(col, row);
	cout << "Final position: ( " << col << ", " << row << " )" << endl;


}


/*

0  w
P  w
P  b
C  b
N  w
R  w
Q  w
K  w


Testing white Pawn move exceptions: expecting 2 exceptions...
Initial position: ( 0, 1 )
Invalid Pawn move. This move SHOULD throw an exception.
Invalid Pawn move. This move SHOULD throw an exception.
Final position: ( 0, 5 )

Testing black Pawn move exceptions: expecting 2 exceptions...
Initial position: ( 4, 5 )
Invalid Pawn move. This move SHOULD throw an exception.
Invalid Pawn move. This move SHOULD throw an exception.
Final position: ( 4, 1 )

Testing Castle move exceptions: expecting 1 exceptions...
Initial position: ( 6, 6 )
Invalid Castle move. This move SHOULD throw an exception.
Final position: ( 6, 4 )

Testing Knight move exceptions: expecting 1 exceptions...
Initial position: ( 1, 0 )
Invalid Knight move. This move SHOULD throw an exception.
Final position: ( 1, 1 )

Testing Rook move exceptions: expecting 2 exceptions...
Initial position: ( 2, 0 )
Invalid Rook move. This move SHOULD throw an exception.
Invalid Rook move. This move SHOULD throw an exception.
Final position: ( 1, 5 )

Testing Queen move exceptions: expecting 1 exceptions...
Initial position: ( 3, 0 )
Invalid Queen move. This move SHOULD throw an exception.
Final position: ( 0, 1 )

Testing King move exceptions: expecting 1 exceptions...
Initial position: ( 4, 0 )
Invalid King move. This move SHOULD throw an exception.
Final position: ( 3, 1 )
*/