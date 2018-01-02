/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#ifndef EX5_CONSOLEGUIDISPLAY_H
#define EX5_CONSOLEGUIDISPLAY_H

#include "GuiDisplay.h"

class ConsoleGuiDisplay : public GuiDisplay {

    virtual void printBoard(Board *board) const;

    virtual void printOtherPlayerMove(char playerSymbol, BoardCoordinates move) const;

    virtual void printMessage(string message) const;

    virtual void printPlayerTurn(char playerSymbol) const;

    virtual void printPossibleMoves(vector<BoardCoordinates> possibleMoves) const;

    virtual void printScore(char playerSymbol, int playerScore) const;

    virtual void printWinner(char playerSymbol) const;

};


#endif //EX5_CONSOLEGUIDISPLAY_H
