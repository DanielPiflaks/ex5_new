/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex4
******************************************/

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

using namespace std;

struct ClientConnectionParam {
    int serverSocket;
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
};

class Server {
public:
    enum StartGameAgain {
        StartGame, EndGame
    };

    /**
     * Constructor.
     * @param fileName file name with port parameter.
     */
    explicit Server(const char *fileName);

    /**
     * Getter
     * @return port number.
     */
    int getPort() const;

    /**
     * Constructor.
     * @param port port number.
     */
    explicit Server(int port);

    /**
     * Start function to open sockets for both players.
     */
    ClientConnectionParam start();

    static int connectToClient(ClientConnectionParam *parameters);

    /**
     * Stop function to close sockets.
     */
    void stop();

    void setPort(int port);

    void setServerSocket(int serverSocket);

    void setClientSocket1(int clientSocket1);

    void setClientSocket2(int clientSocket2);

    void setListOfGames(const vector<string> &listOfGames);

    static void *waitForClients(void *clientConnectionParam);

    /**
     * Send message for first player that second player
     * connected to begin the game.
     */
    void notifyFirstPlayerStart();

    /**
     * receive message from socket1 and send it to socket2,
     * then receive message from socket2 and send to to socket1
     * and again the same loop.
     */
    StartGameAgain sendAndReceiveMoves();

    int getServerSocket() const;

    int getClientSocket1() const;

    int getClientSocket2() const;

    const vector<string> &getListOfGames() const;

private:
    int port;
    int serverSocket;

    int clientSocket1;
    int clientSocket2;

    vector<string> listOfGames;

    /**
     * Set port from input parameter file.
     * @param fileName file name of parameter for port.
     */
    void setPortFromFile(const char *fileName);
};


#endif //EX4_SERVER_H
