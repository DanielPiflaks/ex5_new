/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include "ConsoleGuiDisplay.h"

void ConsoleGuiDisplay::printBoard(Board *board) const {
    cout << "Current board:" << endl;
    //Print columns.
    for (int j = 0; j <= board->getNumCols(); j++) {
        if (j == 0) {
            cout << " | ";
        } else {
            cout << j << " | ";
        }
    }
    cout << endl;

    //Print rows.
    for (int i = 1; i <= board->getNumRows(); i++) {
        for (int k = 0; k < (board->getNumCols() * 4) + 2; ++k) {
            cout << "-";
        }
        cout << endl;
        cout << i << "|";
        for (int j = 1; j <= board->getNumCols(); j++) {
            cout << " " << board->getSymbolByPlace(i, j) << " |";
        }
        cout << endl;
    }
    for (int k = 0; k < (board->getNumCols() * 4) + 2; ++k) {
        cout << "-";
    }
    cout << endl;
}

void ConsoleGuiDisplay::printOtherPlayerMove(char playerSymbol, BoardCoordinates move) const {
    cout << endl;
    cout << playerSymbol << " Played" << move << endl;
    cout << endl;
}

void ConsoleGuiDisplay::printMessage(string message) const {
    cout << message << endl;
}

void ConsoleGuiDisplay::printPlayerTurn(char playerSymbol) const {
    cout << playerSymbol << ": It's your move" << endl;
}

void ConsoleGuiDisplay::printPossibleMoves(vector<BoardCoordinates> possibleMoves) const {
    cout << "Your possible moves: ";
    //Print each possible move.
    for (int i = 0; i < possibleMoves.size(); i++) {
        cout << possibleMoves[i];
    }
    cout << endl;
    cout << endl;
}

void ConsoleGuiDisplay::printScore(char playerSymbol, int playerScore) const {
    cout << "Player " << playerSymbol << " score is: " << playerScore << endl;
}

void ConsoleGuiDisplay::printWinner(char playerSymbol) const {
    cout << "Player " << playerSymbol << " wins!" << endl;
}

void ConsoleGuiDisplay::printMainMenu() const {
    //Print menu for user.
    cout << "choose your opponent:" << endl;
    cout << "1. a human local player" << endl << "2. an AI player" << endl;
    cout << "3. a remote player" << endl;
}

void ConsoleGuiDisplay::printClientMenu() const {
    //Print menu of options to client.
    cout << "please choose one of the following options:" << endl;
    cout << "1. start new game" << endl;
    cout << "2. get list of optional games to play" << endl;
    cout << "3. join exiting game" << endl;
}