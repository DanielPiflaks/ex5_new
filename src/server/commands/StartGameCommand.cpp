/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <cstdio>
#include "StartGameCommand.h"
#include "GameManager.h"

StartGameCommand::StartGameCommand() {};

void StartGameCommand::execute(vector<string> args) {
    //Get game manager.
    GameManager *gameManager = GameManager::getGameManager();
    //First arg is client socket.
    int clientSocket;
    //Convert string to int.
    sscanf(args[0].c_str(), "%d", &clientSocket);
    if (!gameManager->checkIfGameExist(args[1])) {
        Server::send(clientSocket, "Valid");
        Server::send(clientSocket, "1");

        //Add game to game manager map.
        gameManager->addGame(clientSocket, args[1]);
    } else {
        Server::send(clientSocket, "Name already taken");
    }
}
