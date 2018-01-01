/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <cstdio>
#include "JoinGameCommand.h"
#include "GameManager.h"

JoinGameCommand::JoinGameCommand() {};

void JoinGameCommand::execute(vector<string> args) {
    //First arg is client socket.
    int clientSocket;
    //Convert string to int.
    sscanf(args[0].c_str(), "%d", &clientSocket);

    string wantedGameJoin = args[1];

    //Get game manager.
    GameManager *gameManager = GameManager::getGameManager();
    if (gameManager->checkIfGameExist(wantedGameJoin)) {
        Server::send(clientSocket, "Valid");
        Server::send(clientSocket, "2");
        gameManager->createGame(clientSocket, wantedGameJoin);
    } else{
        Server::send(clientSocket, "Not valid game");
    }
}