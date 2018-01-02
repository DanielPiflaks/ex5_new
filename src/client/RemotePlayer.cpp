/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include "RemotePlayer.h"

RemotePlayer::~RemotePlayer() {
}

map<BoardCoordinates, vector<BoardCoordinates> > RemotePlayer::playOneTurn() {
    //Print who it's turn to play.
    display->printPlayerTurn(symbol);
    //Get map of all possible moves.
    map<BoardCoordinates, vector<BoardCoordinates> > possibleMoves = gameLogic->getPossibleGameMoves(playerMoves,
                                                                                                     symbol);
    map<BoardCoordinates, vector<BoardCoordinates> > playerMove;
    vector<BoardCoordinates> flippedSymbols;
    vector<BoardCoordinates> allMoves;

    //For board coordinate, get its possible move and insert in to all moves vector.
    for (map<BoardCoordinates, vector<BoardCoordinates> >::iterator moves = possibleMoves.begin();
         moves != possibleMoves.end(); ++moves) {
        for (int i = 0; i < moves->second.size(); i++) {
            if (find(allMoves.begin(), allMoves.end(), moves->second[i]) == allMoves.end()) {
                allMoves.push_back(moves->second[i]);
            }
        }
    }

    //Get player choice.
    display->printMessage("Waiting for other player's moves");
    BoardCoordinates playerChoice = client->receiveMove();

    //Check if there are no possible moves and notify player about it.
    if (allMoves.empty()) {
        display->printMessage("Opponent has no moves. Play returns to you.");
        //Return empty vector.
        return playerMove;
    }

    if (board->isOnBoard(playerChoice.getRow(), playerChoice.getColumn())) {
        //Print data massage about opponent last move.
        display->printOtherPlayerMove(symbol, playerChoice);
    } else {
        display->printMessage("Player has no possible moves");
    }

    //Get flipped symbols vector.
    flippedSymbols = gameLogic->flipSymbols(possibleMoves,
                                            playerChoice, symbol);
    //Return them.
    playerMove.insert(pair<BoardCoordinates, vector<BoardCoordinates> >(playerChoice, flippedSymbols));
    return playerMove;
}

void RemotePlayer::endGameFunction() {
    //Sent to server message for ending game.
    client->send("End");
    //Disconnect and connect to server to ask for new request.
    client->disconnectServer();
    client->connectToServer();
    //Send to server to close wanted game.
    client->send("close " + gameName);
    client->disconnectServer();
}