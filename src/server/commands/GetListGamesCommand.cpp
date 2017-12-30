//
// Created by danielpiflaks on 23/12/17.
//

#include <iostream>
#include <cstdio>
#include "GetListGamesCommand.h"
#include "GameManager.h"


GetListGamesCommand::GetListGamesCommand(Server *server): server(server){};

void GetListGamesCommand::execute(vector<string> args){
    //Get game manager.
    GameManager *gameManager = GameManager::getGameManager();

    string listOfGames = gameManager->getStringAllOpenGames();

    //First arg is client socket.
    int clientSocket;
    //Convert string to int.
    sscanf(args[0].c_str(), "%d", &clientSocket);

    server->send(clientSocket, listOfGames);
}