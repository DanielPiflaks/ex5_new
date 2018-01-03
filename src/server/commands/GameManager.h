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
    /**
     * Get game manager.
     * @return pointer for game manager.
     */
    static GameManager *getGameManager();

    /**
     * Add game to map.
     * @param clientSocket socket that waits for given game.
     * @param gameName game name.
     */
    void addGame(int clientSocket, string gameName);

    /**
     * @return all games in one string format.
     */
    string getStringAllOpenGames();

    /**
     * Checks if game exists in map.
     * @param game game to check.
     * @return true if game in map, false otherwise.
     */
    bool checkIfGameExist(string game);

    /**
     * Creates game.
     * @param clientSocketToJoin wanted client to join game.
     * @param game game to join.
     */
    void createGame(int clientSocketToJoin, string game);

    /**
     * Closes game.
     * @param game game wanted to close.
     */
    void closeGame(string game);

    /**
     * run game.
     * @param gameParameters first client socket, second client socket
     * @return null
     */
    static void *runGame(void *gameParameters);

private:
    /**
     * Constructor
     */
    GameManager() {};

    /**
     * Copy constructor.
     * @param copy wanted game manager to copy.
     */
    GameManager(const GameManager &copy);

    /**
     * Destructor.
     */
    ~GameManager() {};

    static GameManager *gameManager;
    map<int, string> gamesToJoin;
    static pthread_mutex_t lock1;
    static pthread_mutex_t lock2;
    static pthread_mutex_t lock3;
    static pthread_mutex_t lock4;
    static pthread_mutex_t lock5;
};


#endif //EX5_GAMEMANAGER_H
