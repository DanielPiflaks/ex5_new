/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <cstdio>
#include "StartGameCommand.h"
#include "GameManager.h"

StartGameCommand::StartGameCommand(){};

void StartGameCommand::execute(vector<string> args) {
    //First arg is client socket.
    int clientSocket;
    //Convert string to int.
    sscanf(args[0].c_str(), "%d", &clientSocket);
    Server::send(clientSocket, "1");

    //Get game manager.
    GameManager *gameManager = GameManager::getGameManager();
    //Add game to game manager map.
    gameManager->addGame(clientSocket, args[1]);
}
