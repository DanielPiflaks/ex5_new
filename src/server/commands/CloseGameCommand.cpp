/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <cstdio>
#include "CloseGameCommand.h"
#include "GameManager.h"

CloseGameCommand::CloseGameCommand() {};

void CloseGameCommand::execute(vector<string> args) {
    //First arg is client socket.
    int clientSocket;
    //Convert string to int.
    sscanf(args[0].c_str(), "%d", &clientSocket);

    string gameToClose = args[1];

    //Get game manager.
    GameManager *gameManager = GameManager::getGameManager();
    if (gameManager->checkIfGameExist(gameToClose)) {
        Server::send(clientSocket, "Valid Game");
        gameManager->closeGame(gameToClose);
    } else {
        Server::send(clientSocket, "Not valid game");
    }

}