//
// Created by danielpiflaks on 23/12/17.
//

#include <cstdio>
#include "JoinGameCommand.h"
#include "GameManager.h"

JoinGameCommand::JoinGameCommand(Server *server) : server(server) {};

void JoinGameCommand::execute(vector<string> args) {
    //First arg is client socket.
    int clientSocket;
    //Convert string to int.
    sscanf(args[0].c_str(), "%d", &clientSocket);

    string wantedGameJoin = args[1];

    //Get game manager.
    GameManager *gameManager = GameManager::getGameManager();
    if (gameManager->checkIfGameExist(wantedGameJoin)) {
        server->send(clientSocket, "Valid Game");
        server->send(clientSocket, "2");
        gameManager->createGame(clientSocket, wantedGameJoin, server);
    } else {
        server->send(clientSocket, "Not valid game");
    }
}