/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include "HumanPlayerSender.h"

HumanPlayerSender::~HumanPlayerSender() {
}

map<BoardCoordinates, vector<BoardCoordinates> > HumanPlayerSender::playOneTurn() {
    map<BoardCoordinates, vector<BoardCoordinates> > mapOfMoves = HumanPlayer::playOneTurn();
    //Send wanted move.
    client->sendMove(mapOfMoves.begin()->first);
    return mapOfMoves;
}

void HumanPlayerSender::endGameFunction() {
    //Sent to server message for ending game.
    client->send("End");
    //Disconnect and connect to server to ask for new request.
    client->disconnectServer();
    client->connectToServer();
    //Send to server to close wanted game.
    client->send("close " + gameName);
    client->disconnectServer();
}