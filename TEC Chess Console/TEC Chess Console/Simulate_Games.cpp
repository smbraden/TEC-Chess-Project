/*/-------------------------------------------------------------------------------------//
   Filename:           Simulate_Games.cpp
   Contributor:        Sonja Braden
   Date:               11/3/2020
   Reference:
   Description:			A client for testing the specifications of the ChessBoard class
						using a file of real chess games and their outcomes
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include <ctype.h>		// for tolower()
#include <fstream>		// for ifstream
#include "ChessBoard.h"

using namespace std;
using namespace chess;


char testMove(ChessBoard& argBoard, int x1, int y1, int x2, int y2);
void printHeader(int gameNum);
bool ws_comments(ifstream& inputFile);
bool gameResult(ifstream& inputFile, ChessBoard& argBoard, int& gameNum, char& result, char& expected_result);
bool oneMove(ifstream& inputFile, ChessBoard& argBoard, char& result);
void playGames(const string filename, ChessBoard& argBoard);

inline int char2col(char ch);
inline int int2row(int arg);

const char DRAW = 'd';
const char CONTINUE = 'c';
const char BLACK_WIN = 'b';
const char WHITE_WIN = 'w';
const int MAX_BUFFER_SIZE = 63;






int main() {

	ChessBoard testBoard;
	
	cout << endl << "Welcome to the Chess Game Simulator. Let's test some games..." << endl << endl;

	playGames("testGames_List.txt", testBoard);

	return 0;
}







char testMove(ChessBoard& argBoard, int x1, int y1, int x2, int y2)
{
	try {

		argBoard.move(x1, y1, x2, y2);
		cout << endl;
		argBoard.printBoard();
		cout << endl;
		return CONTINUE;
	}
	catch (const chess_except::InvalidMoveExcep& e) {
		cout << e.getMsg() << endl << endl;
		return CONTINUE;
	}
	catch (const chess_except::DrawSignal& e) {

		cout << "//-----------------------------------------//" << endl;
		cout << "    " << e.getMsg() << endl;
		cout << "//-----------------------------------------//" << endl << endl;
		argBoard.printBoard();	// final print() will not execute in the play() while loop
		cout << endl;
		return DRAW;
	}
	catch (const chess_except::WinSignal& e) {
		cout << "//-----------------------------------------//" << endl;
		cout << "    " << e.getMsg() << endl;
		cout << "//-----------------------------------------//" << endl << endl;
		argBoard.printBoard();	// final print() will not execute in the play() while loop
		cout << endl;
		// maybe should add a ChessBoard feature that gets the underlying type for the client...
		return static_cast<std::underlying_type<ChessPiece::team_type>::type>(argBoard.getWinner());
	}
}






// Purpose:		skips white space and comments in teh buffer object
bool ws_comments(ifstream& inputFile)
{
	inputFile >> ws;
	char ch;

	if (inputFile.peek() == '%') {			// if comment, skip this line
		inputFile.get();
		if (inputFile.peek() == '{') {		// multi-line comment
			inputFile.get();
			while (true) {
				while ((ch = inputFile.get()) != '}' && ch != EOF) {}
				if (inputFile.get() == '%' || inputFile.get() == EOF)
					break;
			}
		}
		else {								// single-line comment
			while (inputFile.get() != '\n') {}
		}

		return true;
	}
	return false;
}






// Purpose:		Detects the game result character '#' and sets the result parameter to the 
//				Game's expected result
bool gameResult(ifstream& inputFile, ChessBoard& argBoard, int& gameNum, char& result, char& expected_result) {

	inputFile >> ws;

	if (inputFile.peek() == '#') {		// pound sign signals expected game result
		inputFile >> expected_result >> expected_result;
		if (expected_result == result)
			cout << "PASS" << endl << endl;
		else
			cout << "FAIL" << endl << endl;

		// Prepare for another game by clearing the board, printing the header
		inputFile >> ws;
		if (inputFile.peek() != EOF) {
			gameNum++;
			printHeader(gameNum);			// print header for the next game
			result = CONTINUE;
			argBoard.reset();
		}

		return true;
	}
	return false;
}






// Purpose:		Execute one move and store the test result in the reference parameter, result
// Return:		returns false if a file formatting irregularity is encountered,
//				Otherwise, returns true if the game is successfully completed
bool oneMove(ifstream& inputFile, ChessBoard& argBoard, char& result)
{
	inputFile >> ws;
	
	char x1 = 'a';
	int y1 = 2;
	char x2 = 'a';
	int y2 = 3;

	if (!(inputFile >> x1 && inputFile >> y1 && inputFile >> x2 && inputFile >> y2))
		return false;

	string team = (argBoard.getTurnTeam() == ChessPiece::team_type::white) ? "White" : "Black";

	cout << "Press [Enter] to continue...";
	cin.get();
	// system("PAUSE");	// lazy pause
	cout << endl;

	cout << team << " move. Current position:	" << x1 << y1 << endl;
	cout << team << " move. New position:	" << x2 << y2 << endl << endl;

	result = testMove(argBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2));

	return true;
}







// Purpose:		Play all games in the referenced file
void playGames(const string filename, ChessBoard& argBoard)
{
	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile) {
		cout << "Problem opening the file, or the file doesn't exist." << endl;
	}

	char expected_result = 'n';
	char result = 'n';
	int gameNum = 1;
	char ch;

	printHeader(gameNum);	// print first game header
	do {

		if (ws_comments(inputFile)) {}
		else if (gameResult(inputFile, argBoard, gameNum, result, expected_result)) {}
		else if (!oneMove(inputFile, argBoard, result))
			break;
		
	} while (inputFile.peek() != EOF);
		
	
	inputFile.clear();
	inputFile.close();

	argBoard.reset();
}






void printHeader(int gameNum)
{

	cout << "//-----------------------------------------//" << endl;
	cout << "               Begin Game " << gameNum << endl;
	cout << "//-----------------------------------------//" << endl;
	cout << endl;

}






inline int char2col(char ch)
{
	return (tolower(ch) - 97);
}






inline int int2row(int arg)
{
	return (arg - 1);
}


