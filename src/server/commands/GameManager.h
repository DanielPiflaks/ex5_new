/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

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
};

class GameManager {

public:
    static GameManager *getGameManager();

    void addGame(int clientSocket, string gameName);

    string getStringAllOpenGames();

    bool checkIfGameExist(string game);

    void createGame(int clientSocketToJoin, string game);

    void closeGame(string game);

    static void *runGame(void *gameParameters);

private:
    GameManager() {}; // Private c'tor
    GameManager(const GameManager &copy); // Private copy c'tor
    ~GameManager() {};

    static GameManager *gameManager;
    map<int, string> gamesToJoin;
    static pthread_mutex_t lock;
};


#endif //EX5_GAMEMANAGER_H
