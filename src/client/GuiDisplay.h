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

    /**
    * Print board.
    * @param board current board.
    */
    virtual void printBoard(Board *board) const = 0;

    /**
     * Print other player last played move.
     * @param playerSymbol other player symbol.
     * @param move other player last played move.
     */
    virtual void printOtherPlayerMove(char playerSymbol, BoardCoordinates move) const = 0;

    /**
     * Print message.
     * @param message relevant message.
     */
    virtual void printMessage(string message) const = 0;

    /**
     * Print who's turn is it.
     * @param playerSymbol player symbol of current player turn.
     */
    virtual void printPlayerTurn(char playerSymbol) const = 0;

    /**
     * Print list of possible current player moves.
     * @param possibleMoves vector of player possible moves.
     */
    virtual void printPossibleMoves(vector<BoardCoordinates> possibleMoves) const = 0;

    /**
     * Print player score in certain format.
     * @param playerSymbol symbol of relevant player.
     * @param playerScore score of relevant player.
     */
    virtual void printScore(char playerSymbol, int playerScore) const = 0;

    /**
     * Print winner in certain format.
     * @param playerSymbol symbol of player who won.
     */
    virtual void printWinner(char playerSymbol) const = 0;

    /**
     * Printing main menu for user.
     */
    virtual void printMainMenu() const = 0;

    /**
     * If player choice was to play with remote player, print relevant menu.
     */
    virtual void printClientMenu() const = 0;

};


#endif //EX5_GUIDISPLAY_H
