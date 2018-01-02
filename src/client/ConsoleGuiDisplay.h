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

    /**
     * Print board.
     * @param board current board.
     */
    virtual void printBoard(Board *board) const;

    /**
     * Print other player last played move.
     * @param playerSymbol other player symbol.
     * @param move other player last played move.
     */
    virtual void printOtherPlayerMove(char playerSymbol, BoardCoordinates move) const;

    /**
     * Print message.
     * @param message relevant message.
     */
    virtual void printMessage(string message) const;

    /**
     * Print who's turn is it.
     * @param playerSymbol player symbol of current player turn.
     */
    virtual void printPlayerTurn(char playerSymbol) const;

    /**
     * Print list of possible current player moves.
     * @param possibleMoves vector of player possible moves.
     */
    virtual void printPossibleMoves(vector<BoardCoordinates> possibleMoves) const;

    /**
     * Print player score in certain format.
     * @param playerSymbol symbol of relevant player.
     * @param playerScore score of relevant player.
     */
    virtual void printScore(char playerSymbol, int playerScore) const;

    /**
     * Print winner in certain format.
     * @param playerSymbol symbol of player who won.
     */
    virtual void printWinner(char playerSymbol) const;

};


#endif //EX5_CONSOLEGUIDISPLAY_H
