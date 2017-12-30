//
// Created by danielpiflaks on 23/12/17.
//

#include <cstdio>
#include "StartGameCommand.h"
#include "GameManager.h"

StartGameCommand::StartGameCommand(Server *server) : server(server) {};

void StartGameCommand::execute(vector<string> args) {
    //First arg is client socket.
    int clientSocket;
    //Convert string to int.
    sscanf(args[0].c_str(), "%d", &clientSocket);
    server->send(clientSocket, "1");

    //Get game manager.
    GameManager *gameManager = GameManager::getGameManager();
    //Add game to game manager map.
    gameManager->addGame(clientSocket, args[1]);
}
