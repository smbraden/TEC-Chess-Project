/*/-------------------------------------------------------------------------------------//
   Filename:           boardTest.cpp
   Contributor:        Sonja Braden
   Date:               11/2/2020
   Reference:
   Description:			A client for testing potential games with the ChessBoard class
//-------------------------------------------------------------------------------------/*/

#include <iostream>
#include <ctype.h>		// for tolower()
#include <fstream>		// for ifstream
#include "ChessBoard.h"

using namespace std;
using namespace chess;


bool testMove(ChessBoard& argBoard, int x1, int y1, int x2, int y2, bool& flag);
int play(const string filename, ChessBoard& argBoard);
inline int char2col(char ch);
inline int int2row(int arg);



int main() {

	ChessBoard testBoard;
	
	cout << endl << "Welcome to the Chess Game Simulator. Let's test some games..." << endl << endl;
	
	const string filename = "testGame.txt";
	
	int result = play(filename, testBoard);
	
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







int play(const string filename, ChessBoard& argBoard)
{
	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile) {
		cout << "Problem opening the file, or the file doesn't exist." << endl;
		return EXIT_FAILURE;
	}

	bool endFlag = false;
	char x1 = 'a';
	int y1 = 2;
	char x2 = 'a';
	int y2 = 3;

	while (!endFlag && inputFile >> x1 && inputFile >> y1 && inputFile >> x2 && inputFile >> y2) {

		string team = (argBoard.getTurnTeam() == ChessPiece::team_type::white) ? "White" : "Black";

		cout << team << " move. Current position:	" << x1 << y1 << endl;
		cout << team << " move. New position:	" << x2 << y2 << endl;
		cout << endl;

		testMove(argBoard, char2col(x1), int2row(y1), char2col(x2), int2row(y2), endFlag);

		system("PAUSE");	// lazy pause
		cout << endl;
	}

	inputFile.clear();
	inputFile.close();

	argBoard.printBoard();	// the final print will not execute (win or draw signaled by exception)

	return EXIT_SUCCESS;
}






inline int char2col(char ch)
{
	return (tolower(ch) - 97);
}






inline int int2row(int arg)
{
	return (arg - 1);
}



