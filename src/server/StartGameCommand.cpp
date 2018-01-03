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

    //Check if game name to start doesnt exist.
    if (!gameManager->checkIfGameExist(args[1])) {
        //Server send to client validation and player number.
        Server::send(clientSocket, "Valid");
        Server::send(clientSocket, "1");
        //Add game to game manager map.
        gameManager->addGame(clientSocket, args[1]);
    } else {
        //If game name already exist send to client invalidation.
        Server::send(clientSocket, "Name already taken");
    }
}
