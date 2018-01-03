/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include "GameManager.h"

GameManager *GameManager::gameManager = 0;
pthread_mutex_t GameManager::lock1;
pthread_mutex_t GameManager::lock2;
pthread_mutex_t GameManager::lock3;
pthread_mutex_t GameManager::lock4;
pthread_mutex_t GameManager::lock5;

GameManager *GameManager::getGameManager() {
    //Check that game manager isn't initialized yet.
    if (gameManager == 0) {
        //Lock thread so game manager won't initialize twice.
        pthread_mutex_lock(&lock1);
        //Check that after first thread created game manager second thread won't create it.
        if (gameManager == 0) {
            //Create game manager.
            gameManager = new GameManager();
        }
        //Unlock thread from game manager.
        pthread_mutex_unlock(&lock1);
    }
    return gameManager;
}


void GameManager::addGame(int clientSocket, string gameName) {
    //Lock thread so 2 threads won't access to map together.
    pthread_mutex_lock(&lock2);
    //Add game to map.
    gamesToJoin[clientSocket] = gameName;
    //Unlock thread.
    pthread_mutex_unlock(&lock2);
}

string GameManager::getStringAllOpenGames() {
    const char separator[3] = ", ";
    string allGames;
    bool firstIter = true;
    //Get all games into all games string.
    for (map<int, string>::iterator game = gamesToJoin.begin();
         game != gamesToJoin.end(); ++game) {
        if (!firstIter) {
            pthread_mutex_lock(&lock3);
            allGames.append(separator);
            pthread_mutex_unlock(&lock3);
        } else {
            firstIter = false;
        }
        pthread_mutex_lock(&lock3);
        allGames.append(game->second);
        pthread_mutex_unlock(&lock3);
    }
    //Check if there are no games.
    if (allGames.empty()) {
        pthread_mutex_lock(&lock3);
        allGames = "There are no games";
        pthread_mutex_unlock(&lock3);
    }
    //Return list of all games.
    return allGames;
}

bool GameManager::checkIfGameExist(string game) {
    //Check if input game exist.
    for (map<int, string>::iterator existingGame = gamesToJoin.begin();
         existingGame != gamesToJoin.end(); ++existingGame) {
        pthread_mutex_lock(&lock5);
        if (existingGame->second.compare(game) == 0) {
            pthread_mutex_unlock(&lock5);
            return true;
        }
    }
    return false;
}

void GameManager::createGame(int clientSocketToJoin, string game) {
    //Create new parameters for game struct.
    ParametersForGame *parametersForGame = new ParametersForGame;
    //Set second player socket.
    parametersForGame->secondPlayerSocket = clientSocketToJoin;

    //Get wanted game and wanted socket for game.
    for (map<int, string>::iterator existingGame = gamesToJoin.begin();
         existingGame != gamesToJoin.end(); ++existingGame) {
        if (existingGame->second.compare(game) == 0) {
            //Set first player from map.
            parametersForGame->firstPlayerSocket = existingGame->first;
            break;
        }
    }
    //Close game so other players won't get into this game.
    closeGame(game);

    pthread_t threadRunGame;
    //Create thread to run game.
    pthread_create(&threadRunGame, NULL, GameManager::runGame, (void *) parametersForGame);
}

void *GameManager::runGame(void *gameParameters) {
    const string endGameMessage = "End";
    const string clientDisconnectedMessage = "Client disconnected";
    //Get struct.
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
            delete params;
            break;
        } else if (message.compare(clientDisconnectedMessage) == 0) {
            //Send to second player that his opponent is disconnected.
            Server::send(secondPlayer, "Opponent Disconnected");
            delete params;
            //Close second player socket.
            close(secondPlayer);
            break;
        }

        //Write to 2nd socket.
        Server::send(secondPlayer, message);
        //Get from second player.
        message = Server::receive(secondPlayer);

        if (message.compare(endGameMessage) == 0) {
            //If massage from socket is about game ending then stop the loop.
            delete params;
            break;
        } else if (message.compare(clientDisconnectedMessage) == 0) {
            //Send to first player that his opponent is disconnected.
            Server::send(firstPlayer, "Opponent Disconnected");
            delete params;
            //Close first player socket.
            close(firstPlayer);
            break;
        }

        //Write to 1st socket.
        Server::send(firstPlayer, message);
    }
}

void GameManager::closeGame(string game) {
    //Find game to close and close it.
    for (map<int, string>::iterator existingGame = gamesToJoin.begin();
         existingGame != gamesToJoin.end(); ++existingGame) {
        if (existingGame->second.compare(game) == 0) {
            pthread_mutex_lock(&lock4);
            gamesToJoin.erase(existingGame);
            pthread_mutex_unlock(&lock4);
            break;
        }
    }
}
