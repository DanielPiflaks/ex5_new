//
// Created by danielpiflaks on 29/12/17.
//

#ifndef EX5_GAMEMANAGER_H
#define EX5_GAMEMANAGER_H

#include <sys/param.h>
#include <iostream>
#include <map>
#include "../Server.h"

using namespace std;

struct ParametersForGame {
    int firstPlayerSocket;
    int secondPlayerSocket;
    Server *server;
};

class GameManager {

public:
    static GameManager *getGameManager();

    void addGame(int clientSocket, string gameName);

    string getStringAllOpenGames();

    bool checkIfGameExist(string game);

    void createGame(int clientSocketToJoin, string game, Server *server);

    static void *runGame(void *gameParameters);

private:
    GameManager() {}; // Private c'tor
    GameManager(const GameManager &copy); // Private copy c'tor
    ~GameManager() {};

    static GameManager *gameManager;
    map<int, string> gamesToJoin;
};


#endif //EX5_GAMEMANAGER_H
