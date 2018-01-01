/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include "GameManager.h"

GameManager *GameManager::gameManager = 0;
pthread_mutex_t GameManager::lock;

GameManager *GameManager::getGameManager() {
    if (gameManager == 0) {
        pthread_mutex_lock(&lock);
        if (gameManager == 0) {
            gameManager = new GameManager();
        }
        pthread_mutex_unlock(&lock);
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
    if (allGames.empty()){
        allGames = "There are no games";
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

void GameManager::createGame(int clientSocketToJoin, string game) {
    ParametersForGame parametersForGame;
    parametersForGame.secondPlayerSocket = clientSocketToJoin;

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

    //Notify first player to start.
    Server::send(firstPlayer, "1");

    string message;
    while (true) {
        //Read from 1st socket.
        message = Server::receive(firstPlayer);

        if (message.compare(endGameMessage) == 0) {
            //If massage from socket is about game ending then stop the loop.
            break;
        }

        //Write to 2nd socket.
        Server::send(secondPlayer, message);

        message = Server::receive(secondPlayer);

        if (message.compare(endGameMessage) == 0) {
            //If massage from socket is about game ending then stop the loop.
            break;
        }

        //Write to 1st socket.
        Server::send(firstPlayer, message);
    }
}

void GameManager::closeGame(string game) {
    for (map<int, string>::iterator existingGame = gamesToJoin.begin();
         existingGame != gamesToJoin.end(); ++existingGame) {
        if (existingGame->second.compare(game) == 0) {
            gamesToJoin.erase(existingGame);
            break;
        }
    }
}
