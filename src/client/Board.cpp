/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/
#include "Board.h"

Board::Board(int numRows, int numCols) : numRows(numRows), numCols(numCols) {
    boardMatrix = new char *[numRows];
    for (int i = 0; i < numRows; ++i) {
        boardMatrix[i] = new char[numCols];
    }

    for (int j = 0; j < numRows; j++) {
        for (int i = 0; i < numCols; i++) {
            boardMatrix[j][i] = ' ';
        }
    }
}

Board::Board(const Board &oldBoard) {
    //Create new matrix.
    boardMatrix = new char *[oldBoard.getNumCols()];
    //Set number of rows and columns to new board.
    numRows = oldBoard.numRows;
    numCols = oldBoard.numCols;
    //Allocate rows.
    for (int i = 0; i < oldBoard.getNumRows(); ++i) {
        boardMatrix[i] = new char[oldBoard.getNumCols()];
    }
    //Copy all chars from first board to second board.
    for (int j = 0; j < oldBoard.numRows; j++) {
        for (int i = 0; i < oldBoard.numCols; i++) {
            putSymbolOnBoard(j + 1, i + 1, oldBoard.getSymbolByPlace(j + 1, i + 1));
        }
    }
}

void Board::freeBoardMatrix() {
    for (int i = 0; i < numCols; ++i) {
        delete[] boardMatrix[i];
    }
    delete[] boardMatrix;
}

void Board::putSymbolOnBoard(int row, int column, char symbol) {

    /*if ((row < 0) || (row > numRows)) {
        cout << "Invalid row number." << endl;
        if ((column < 0) || (column > numCols)) {
            cout << "Invalid column number." << endl;
        }
    } else {
        if ((column < 0) || (column > numCols)) {
            cout << "Invalid column number." << endl;
        } else {
            boardMatrix[row - 1][column - 1] = symbol;
        }
    }*/
    boardMatrix[row - 1][column - 1] = symbol;
}

Board::~Board() {
    freeBoardMatrix();
}

int Board::getNumRows() const {
    return numRows;
}

int Board::getNumCols() const {
    return numCols;
}

char Board::getSymbolByPlace(int row, int column) const {
    if (!isOnBoard(row, column)) {
        throw "Invalid place!";
    }
    return boardMatrix[row - 1][column - 1];
}

bool Board::isOnBoard(int row, int column) const {
    return ((row > 0) && (row <= numRows) && (column > 0) && (column <= numCols));
}

bool Board::operator==(const Board &board) const {
    //Check that size of boards is equal.
    if ((numRows == board.getNumRows() && (numCols == board.getNumCols()))) {
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                //Check that all symbols of board are equal.
                if (getSymbolByPlace(i + 1, j + 1) != (board.getSymbolByPlace(i + 1, j + 1))) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}



