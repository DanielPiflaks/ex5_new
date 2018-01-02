/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#ifndef EX5_GUIDISPLAY_H
#define EX5_GUIDISPLAY_H

#include "GuiDisplay.h"
#include "Board.h"

class GuiDisplay {
public:

    virtual void printBoard(Board *board) const = 0;

    virtual void printOtherPlayerMove(char playerSymbol, BoardCoordinates move) const = 0;

    virtual void printMessage(string message) const = 0;

    virtual void printPlayerTurn(char playerSymbol) const = 0;

    virtual void printPossibleMoves(vector<BoardCoordinates> possibleMoves) const = 0;

    virtual void printScore(char playerSymbol, int playerScore) const = 0;

    virtual void printWinner(char playerSymbol) const = 0;

};


#endif //EX5_GUIDISPLAY_H
