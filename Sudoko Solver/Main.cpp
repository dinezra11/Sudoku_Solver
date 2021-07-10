/* Author: Din Ezra, dinezra11@gmail.com
			### Sudoku Solver! ###
	This program solves sudoku's boards automatically, using the backtracking algorithm implementation.
	Works with boards of the following possible sizes: 4x4, 9x9, 16x16, 25x25 
	**************************************************************************************************************************************
	** Board class method:		Board(N);			Constructor, create a new empty sudoku in the size of NxN (default: N=9)			**
	**							bool solve();		Solve the sudoku. Return TRUE if success, and FALSE if there is no valid solution	**
	**************************************************************************************************************************************
*/

#include <iostream>
#include "Board.h"

int main() {
	Board sudoku(9);
	cin >> sudoku;

	if (sudoku.solve(0, 0)) {
		cout << endl << "Solution: ";
		cout << sudoku << endl;
	}
	else
		cout << endl << "This sudoku doesn't have a solution!" << endl;

	return 0;
}