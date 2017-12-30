//
// Created by danielpiflaks on 29/12/17.
//

#include <cstring>
#include "GameManager.h"

GameManager *GameManager::gameManager = 0;

GameManager *GameManager::getGameManager() {
    if (gameManager == 0) {
        gameManager = new GameManager;
    }
    return gameManager;
}


void GameManager::addGame(int clientSocket, string gameName) {
    gamesToJoin[clientSocket] = gameName;
}

string GameManager::getStringAllOpenGames() {
    const char separator[3] = ", ";
    string allGames;
    bool firstIter = true;
    for (map<int, string>::iterator game = gamesToJoin.begin();
         game != gamesToJoin.end(); ++game) {
        if (!firstIter) {
            allGames.append(separator);
        } else {
            firstIter = false;
        }
        allGames.append(game->second);
    }
    return allGames;
}

bool GameManager::checkIfGameExist(string game) {
    for (map<int, string>::iterator existingGame = gamesToJoin.begin();
         existingGame != gamesToJoin.end(); ++existingGame) {
        if (existingGame->second.compare(game) == 0) {
            return true;
        }
    }
    return false;
}

void GameManager::createGame(int clientSocketToJoin, string game, Server *server) {
    ParametersForGame parametersForGame;
    parametersForGame.secondPlayerSocket = clientSocketToJoin;
    parametersForGame.server = server;

    for (map<int, string>::iterator existingGame = gamesToJoin.begin();
         existingGame != gamesToJoin.end(); ++existingGame) {
        if (existingGame->second.compare(game) == 0) {
            parametersForGame.firstPlayerSocket = existingGame->first;
            break;
        }
    }

    pthread_t threadRunGame;
    pthread_create(&threadRunGame, NULL, GameManager::runGame, (void *) &parametersForGame);
}

void *GameManager::runGame(void *gameParameters) {
    const string endGameMessage = "End";

    ParametersForGame *params = (struct ParametersForGame *) gameParameters;
    int firstPlayer = params->firstPlayerSocket;
    int secondPlayer = params->secondPlayerSocket;
    Server *server = params->server;

    string message;
    while (true) {
        //Read from 1st socket.
        message = server->receive(firstPlayer);

        if (message.compare(endGameMessage) == 0) {
            //If massage from socket is about game ending then stop the loop.
            break;
        }

        //Write to 2nd socket.
        server->send(secondPlayer, message);

        message = server->receive(secondPlayer);

        if (message.compare(endGameMessage) == 0) {
            //If massage from socket is about game ending then stop the loop.
            break;
        }

        //Write to 1st socket.
        server->send(firstPlayer, message);
    }
}
