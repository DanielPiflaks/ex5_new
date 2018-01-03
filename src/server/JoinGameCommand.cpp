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

    //Second arg is wanted game name.
    string wantedGameJoin = args[1];

    //Get game manager.
    GameManager *gameManager = GameManager::getGameManager();
    //Check if game name to join exist.
    if (gameManager->checkIfGameExist(wantedGameJoin)) {
        //Server send to client validation and player number.
        Server::send(clientSocket, "Valid");
        Server::send(clientSocket, "2");
        //Create game.
        gameManager->createGame(clientSocket, wantedGameJoin);
    } else {
        //If game name isn't exist send to client invalidation.
        Server::send(clientSocket, "Not valid game");
    }
}