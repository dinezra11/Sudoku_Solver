#include "Board.h"

Board::Board()
{
	// Default Constructor
	size = DEFAULTSIZE;
	blockSize = (int)sqrt(size);

	cell = new char* [size];
	for (int i = 0; i < size; i++)
		cell[i] = new char[size];

	resetBoard();
}

Board::Board(int size)
{
	// Constructor with sudoku's size parameter
	if (size == 4 || size == 9 || size == 16 || size == 25)
		this->size = size;
	else
		this->size = DEFAULTSIZE;

	this->blockSize = (int)sqrt(this->size);

	this->cell = new char* [this->size];
	for (int i = 0; i < this->size; i++)
		this->cell[i] = new char[this->size];

	resetBoard();
}

Board::~Board()
{
	// Destructor - Release all dynamic memory allocated!
	for (int i = 0; i < size; i++)
		delete[] cell[i];

	delete[] cell;
}

void Board::resetBoard()
{
	// Reset the board - fill all of the cells with spaces.
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cell[i][j] = ' ';
}

bool Board::verifyMove(int xCoord, int yCoord, char newNum)
{
	// Check if it is legal to put newNum in the sudoku board on cell[xCoord][yCoord]
	int blockXstart = xCoord / blockSize,
		blockYstart = yCoord / blockSize;

	// Validate the input according to the digit's available range
	if (size <= 9 && (int)(newNum - '0') > size)
		return false;
	if (size > 9 && (int)newNum - 'A' + 10 > size)
		return false;

	// Validate the move according to the sudoku's board
	for (int i = 0; i < size; i++)
		if (cell[xCoord][i] == newNum || cell[i][yCoord] == newNum)
			return false;

	for (int i = blockSize * blockXstart; i < blockSize * (blockXstart + 1); i++)
		for (int j = blockSize * blockYstart; j < blockSize * (blockYstart + 1); j++)
			if (cell[i][j] == newNum)
				return false;

	return true;
}

bool Board::solve(int xCoord, int yCoord)
{
	/* Recursive solution for solving the sudoku! Auto solve and fill up the sudoku's board. [xCoord and yCoord is the first index to solve]
		Return TRUE if success. Return FALSE if there is no solution for this sudoku. */

	if (yCoord >= this->size) {
		yCoord = 0;
		xCoord++;
	}
	if (xCoord >= this->size)
		return true;			// Recursion reached the end of the board - solution found!
	if (this->cell[xCoord][yCoord] != ' ')
		return solve(xCoord, yCoord + 1);		// <- Recursive call!

	for (int i = 1; i <= this->size; i++) {
		if (i <= 9) {
			if (this->verifyMove(xCoord, yCoord, (char)(i + '0'))) {
				this->cell[xCoord][yCoord] = (char)(i + '0');

				if (solve(xCoord, yCoord + 1))		// <- Recursive call!
					return true;
				else
					this->cell[xCoord][yCoord] = ' ';
			}
		}
		else {
			if (this->verifyMove(xCoord, yCoord, (char)(i - 10 + 'A'))) {
				this->cell[xCoord][yCoord] = (char)(i - 10 + 'A');

				if (solve(xCoord, yCoord + 1))		// <- Recursive call!
					return true;
				else
					this->cell[xCoord][yCoord] = ' ';
			}
		}
	}

	return false;
}

istream& operator>>(istream& in, Board& obj)
{
	// Operator>> overload - input the board's cells!
	char input;								// Input from the keyboard
	bool end = false;						// For applying the input (input again if the user decides to)
	bool validInput;						// For validate the input
	int xCoord, yCoord;						// Coordinates for input

	do {
		// Reset board
		obj.resetBoard();

		// Input the cells
		for (xCoord = 0; xCoord < obj.size; xCoord++) {
			for (yCoord = 0; yCoord < obj.size; yCoord++) {
				do {
					system("cls");
					obj.cell[xCoord][yCoord] = '*';
					cout << obj;
					
					cout << "Enter digits (1-9), letters (A-Z) or spaces to fill up the sudoku board." << endl
						<< "\t(A=10, B=11, C=12, etc..)";
					input = _getch();

					if (input == ' ') {
						obj.cell[xCoord][yCoord] = ' ';
						validInput = true;
					}
					else if ((input >= '1' && input <= '9') || (input >= 'A' && input <= 'Z')) {
						if (obj.verifyMove(xCoord, yCoord, input)) {
							obj.cell[xCoord][yCoord] = input;
							validInput = true;
						}
						else
							validInput = false;
					}
					else
						validInput = false;
				} while (!validInput);
			}
		}

		// Ask for applying changes
		system("cls");
		cout << endl << obj;
		do {
			cout << "Apply changes? Y/N " << endl;
			switch (_getch()) {
			case 'Y':
			case 'y': end = true;
				validInput = true;
				break;
			case 'N':
			case 'n': end = false;
				validInput = true;
				break;
				
			default: validInput = false;
			}
		} while (!validInput);
	} while (!end);
	
	return in;
}

ostream& operator<<(ostream& os, const Board& obj)
{
	// Operator<< overload - print the board's content
	int k;				// K = Count the printed cells. Print border when it reaches the blockSize

	os << endl;
	obj.printRowsBorder(os);
	for (int i = 0; i < obj.size; i++) {
		k = 0;
		os << "| ";
		for (int j = 0; j < obj.size; j++) {
			os << obj.cell[i][j] << ' ';
			
			k++;
			if (k == obj.blockSize) {
				os << "| ";
				k = 0;
			}
		}

		os << endl;
		if ((i + 1) % obj.blockSize == 0)
			obj.printRowsBorder(os);
	}

	return os;
}

void Board::printRowsBorder(ostream& os) const
{
	// Print the row's border, depending on the total size of the sudoku.

	if (size == 4)
		os << " ----------- " << endl;
	else if (size == 9)
		os << " ----------------------- " << endl;
	else if (size == 16)
		os << " --------------------------------------- " << endl;
	else if (size == 25)
		os << " ----------------------------------------------------------- " << endl;
}