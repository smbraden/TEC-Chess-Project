/*/-------------------------------------------------------------------------------------//
	Filename:           GUIBoard.h
	Contributor:        Sonja Braden
	Date:               11/14/2020
	Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
	Description:		
//-------------------------------------------------------------------------------------/*/


#include "GUIBoard.h"


namespace chess_ui {



	GUIBoard::GUIBoard()
	{
		left_bound = 0;
		right_bound = 800;
		top_bound = 0;
		bottom_bound = 800;

		initTextures();
		initPieceSprites(sf::Vector2f(0, 0), 100); // (2140, 1020)
		initBoardSquares(sf::Vector2f(0, 0), 100);
	}






	GUIBoard::GUIBoard(const sf::Vector2f& reference, int spacing)
	{
		left_bound = reference.x;
		right_bound = left_bound + spacing * 8;
		top_bound = reference.y;
		bottom_bound = right_bound + spacing * 8;

		initTextures();
		initPieceSprites(reference, spacing);
		initBoardSquares(reference, spacing);
	}






	GUIBoard::GUIBoard(const std::string arg[2][NUM_TEAM_TEXTURES],
		const sf::Vector2f& reference, int spacing)
	{
		left_bound = reference.x;
		right_bound = left_bound + spacing * 8;
		top_bound = reference.y;
		bottom_bound = right_bound + spacing * 8;

		// duplicate the filenames this objects filename list
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < NUM_TEAM_TEXTURES; j++) {
				PieceFilenames[i][j] = arg[i][j];
			}
		}

		initTextures();		// Init the set of corresponding textures
		initPieceSprites(reference, spacing);
		initBoardSquares(reference, spacing);
	}






	GUIBoard::~GUIBoard()
	{
		// delete the dynamically allocated set of Sprite Pieces
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < NUM_TEAM_PIECES; j++) {
				if (spritePieces[i][j] != nullptr) {
					delete spritePieces[i][j];
				}
			}
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < NUM_TEAM_TEXTURES; j++) {
				if (TexturePtrs[i][j] != nullptr) {
					delete TexturePtrs[i][j];
				}
			}
		}

		
		// delete the dynamically allocated vectors representing board squares
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (spritePieces[i][j] != nullptr) {
					delete BoardSquares[i][j];
				}
			}
		}
		
	}






	void GUIBoard::update(sf::RenderWindow& renderWindow)
	{
		bool result = false;
		sf::Vector2i curr_dragging;
		sf::Vector2f origin;
		sf::Vector2i snap_pos;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (spritePieces[i][j] != nullptr) {
					result = spritePieces[i][j]->update(renderWindow);
					curr_dragging = sf::Vector2i(i, j);
					origin = spritePieces[i][j]->getOrigin();
				}
			}
		}
		
		if (result) {
			snap_pos = getSnapPosition(origin, curr_dragging);
			if (spritePieces[snap_pos.x][snap_pos.y] != nullptr) {	// if occupied, snap back to prev position
				spritePieces[curr_dragging.x][curr_dragging.y]->setPosition
			}
		}
	}





	sf::Vector2i GUIBoard::getSnapPosition(const sf::Vector2f& pixel_coor, const sf::Vector2i& cur_snap_pos)
	{
		sf::Vector2i temp = cur_snap_pos;

		// if outside of board bounds return current snap position
		if (pixel_coor.x < left_bound || pixel_coor.y < right_bound ||
			pixel_coor.x > right_bound || pixel_coor.y > left_bound) {
			return temp;
		}

	}






	sf::Vector2i GUIBoard::getPixelPosition(const sf::Vector2f& snap_pos)
	{
		return sf::Vector2i();
	}





	void GUIBoard::initTextures()
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < NUM_TEAM_TEXTURES; j++) {
				TexturePtrs[i][j] = new sf::Texture;
				TexturePtrs[i][j]->loadFromFile(PieceFilenames[i][j]);	// dynamic implementation
			}
		}
	}





	/*
		Pre:	reference is the upper left position of the first board square,
				spacing is the distance between spaces.
				The upper left space is a8 (black rook)

		Post:	The set of piece sprites has textures loaded and pieces positioned
	*/
	void GUIBoard::initPieceSprites(const sf::Vector2f& reference, int spacing)
	{
		int x = reference.x;
		int Wy = reference.y + spacing * 7;
		int By = reference.y;

		for (int i = 0; i < 5; i++) {	// leftiest Rooks through Kings

			addSpriteTexture(TexturePtrs[0][i], 0, i, x, Wy);
			//addSpriteTexture(TexturePtrs[1][i], 1, i, x, By);		// to instead use Black Piece textures at index [1][i]
			addSpriteTexture(TexturePtrs[0][i], 1, i, x, By);		// to use darkened White Piece textures
			spritePieces[1][i]->setColor(sf::Color(150, 150, 150));

			x += spacing;
		}
		for (int i = 5; i < 8; i++) {	// rightiest Bishop through Rook

			addSpriteTexture(TexturePtrs[0][7 - i], 0, i, x, Wy);
			//addSpriteTexture(TexturePtrs[1][7 - i], 1, i, x, By);	// to instead use Black Piece textures at index [1][7 - i]
			addSpriteTexture(TexturePtrs[0][7 - i], 1, i, x, By);	// to use darkened White Piece textures
			spritePieces[1][i]->setColor(sf::Color(150, 150, 150));

			x += spacing;
		}

		x = reference.x;
		Wy = reference.y + spacing * 6;
		By = reference.y + spacing;

		for (int i = 8; i < NUM_TEAM_PIECES; i++) {	// all zee wPawns
			addSpriteTexture(TexturePtrs[0][5], 0, i, x, Wy);
			// addSpriteTexture(TexturePtrs[1][5], 1, i, x, By);	// to instead use Black Piece textures at index [1][5]
			addSpriteTexture(TexturePtrs[0][5], 1, i, x, By);		// to use darkened White Piece textures
			spritePieces[1][i]->setColor(sf::Color(150, 150, 150));

			x += spacing;
		}
	}




	void GUIBoard::initBoardSquares(const sf::Vector2f& reference, int spacing)
	{
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				BoardSquares[i][j] = nullptr;
			}
		}


		int x = reference.x;
		int Wy = reference.y + spacing * 7;
		int By = reference.y;

		for (int i = 0; i < BOARD_SIZE; i++) { // major pieces

			BoardSquares[0][i] = new Vector2i_sprite(x, Wy, spritePieces[0][i]);		// white
			BoardSquares[7][i] = new Vector2i_sprite(x, By, spritePieces[1][i]);		// black
			
			x += spacing;
		}

		x = reference.x;
		Wy = reference.y + spacing * 6;
		By = reference.y + spacing;

		for (int i = 0; i < BOARD_SIZE; i++) {	// all zee wPawns
			
			BoardSquares[1][i] = new Vector2i_sprite(x, Wy, spritePieces[0][8 + i]);	// white
			BoardSquares[6][i] = new Vector2i_sprite(x, By, spritePieces[1][8 + i]);	// black
			
			x += spacing;
		}
	}




	void GUIBoard::addSpriteTexture(sf::Texture* txtPtr, 
									int team_index, int piece_index, int x, int y)
	{
		spritePieces[team_index][piece_index] = new PieceSprite(txtPtr, x, y);
	}



}	// closes namespace













	/*

	Some setColor() combos to try for black
	Use the white piece texture if setting the color in software

	Tan:
	(166, 137, 111)
	(179, 153, 130)
	(169, 139, 112)

	Greys:
	(128, 128, 128)
	(175, 175, 175)
	(192, 192, 192)

	So far, best overall contrast is (150, 150, 150) grey on a slightly darkened chess board

	*/