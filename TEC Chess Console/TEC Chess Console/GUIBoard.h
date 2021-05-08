/*/-------------------------------------------------------------------------------------//
	Filename:           GUIBoard.h
	Contributor:        Sonja Braden
	Date:               11/14/2020
	Reference:			https://www.sfml-dev.org/tutorials/2.5/start-vc.php
	Description:		Manages dynamic allocation of PieceSprites, and manages
						PieceSprite Textures in order to prevent multiple instantiations of
						equivalent Textures

						PieceFilenames is a 2 x 6 array of filenames of the images to be used
						for the chess piece sprites. For proper initializations, ensure that
						the array is organized as follows:

						indicese [0][i] are the White Team
						indicese [1][i] are the Black Team

						for i = 0 through 5, the types of pieces should be in this order:
						Rook, Knight, Bishop, Queen, King, Pawn

						The object is intitialized with a pre-exsiting set of files, but
						the parameterized constructor can be called with reference to an
						array containing a different set of filenames.
						This allows for creation of a set of Pieces with custom styles.
//-------------------------------------------------------------------------------------/*/

#ifndef GUI_BOARD_H
#define GUI_BOARD_H

#include <SFML/Graphics.hpp>
#include "PieceSprite.h"
#include <string>

namespace chess_ui {


	class GUIBoard {

	public:
		const static int BOARD_SIZE = 8;
		const static int NUM_TEAM_TEXTURES = 6;
		const static int NUM_TEAM_PIECES = 16;

		GUIBoard();
		GUIBoard(const sf::Vector2f& reference, int spacing);      
		GUIBoard(const std::string arg[2][NUM_TEAM_TEXTURES], const sf::Vector2f& reference, int spacing);
		~GUIBoard();
		void update(sf::RenderWindow& renderWindowPointer);

	private:

		// For cooresponding board positions with a set of pixel coordinates and a PieceSprite
		class Vector2i_sprite : public sf::Vector2i  {

		public:
			Vector2i_sprite() : sf::Vector2i() {occupant = nullptr;	}
			Vector2i_sprite(int x, int y) : sf::Vector2i(x, y) {occupant = nullptr;	}
			Vector2i_sprite(int x, int y, PieceSprite* p) : sf::Vector2i(x, y) {occupant = p;}

			void setPieceSprite(PieceSprite* p) { occupant = p; }
			PieceSprite* getPieceSprite() const { return occupant; }

		private:
			PieceSprite* occupant = nullptr;
			int board_x = 0;		// horizontal board position (squares not pixels)
			int board_y = 0;		// vertical board position (squares not pixels)
		};

		// sf::Texture Textures[2][NUM_TEAM_TEXTURES];	// non-dynamic implementation
		sf::Texture* TexturePtrs[2][NUM_TEAM_TEXTURES];
		chess_ui::PieceSprite* spritePieces[2][NUM_TEAM_PIECES];
		Vector2i_sprite* BoardSquares[BOARD_SIZE][BOARD_SIZE];
		int left_bound;
		int right_bound;
		int top_bound;
		int bottom_bound;

		std::string PieceFilenames[2][NUM_TEAM_TEXTURES] = {
		{ "Images/WhiteRook.png", "Images/WhiteKnight.png", "Images/WhiteBishop.png",
		  "Images/WhiteQueen.png","Images/WhiteKing.png", "Images/WhitePawn.png" },
		{ "Images/BlackRook.png", "Images/BlackKnight.png", "Images/BlackBishop.png",
		  "Images/BlackQueen.png", "Images/BlackKing.png", "Images/BlackPawn.png" } };

		void initTextures();
		void initPieceSprites(const sf::Vector2f& reference, int spacing);
		void initBoardSquares(const sf::Vector2f& reference, int spacing);
		void addSpriteTexture(sf::Texture* txtPtr, int team_index, int piece_index, int x, int y);
		sf::Vector2i getSnapPosition(const sf::Vector2f& snap_pos, const sf::Vector2i& prev_pos);
		sf::Vector2i getPixelPosition(const sf::Vector2f& snap_pos);
	};
}


#endif
  