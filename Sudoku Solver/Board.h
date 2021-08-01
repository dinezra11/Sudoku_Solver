#ifndef _BOARD_H
#define _BOARD_H

#define DEFAULTSIZE 9

#include <iostream>
#include <conio.h>							// for _getch() method.
using namespace std;

class Board {
private:
	char** cell;							// Matrix of the board's cells
	int size;								// Board's size = SIZExSIZE
	int blockSize;							// Size of "block" -> the square root of the size

	void printRowsBorder(ostream&) const;	// #private method to forbid the use of it outside the class!#

public:
	Board();
	Board(int);
	~Board();

	void resetBoard();
	bool verifyMove(int, int, char);
	bool solve(int, int);

	friend istream& operator>>(istream&, Board&);
	friend ostream& operator<<(ostream&, const Board&);
};

#endif