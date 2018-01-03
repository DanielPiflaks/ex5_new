/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <iostream>
#include <cstdio>
#include "GetListGamesCommand.h"
#include "GameManager.h"

GetListGamesCommand::GetListGamesCommand() {};

void GetListGamesCommand::execute(vector<string> args) {
    //Get game manager.
    GameManager *gameManager = GameManager::getGameManager();

    //Get games on waiting.
    string listOfGames = gameManager->getStringAllOpenGames();

    //First arg is client socket.
    int clientSocket;

    //Convert string to int.
    sscanf(args[0].c_str(), "%d", &clientSocket);

    //Server send to client list of games.
    Server::send(clientSocket, listOfGames);
}