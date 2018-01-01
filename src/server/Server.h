/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

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
     * Constructor.
     * @param port port number.
     */
    explicit Server(int port);

    /**
     * Start function to open sockets for both players.
     */
    void start();

    //static int connectToClient(ClientConnectionParam *parameters);

    /**
     * Stop function to close sockets.
     */
    void stop();

    /**
     * Send message for first player that second player
     * connected to begin the game.
     */
    void notifyFirstPlayerStart(int clientSocket);

    /**
     * receive message from socket1 and send it to socket2,
     * then receive message from socket2 and send to to socket1
     * and again the same loop.
     */
    StartGameAgain sendAndReceiveMoves();

    static string receive(int clientSocket);

    static void send(int clientSocket, string param);
private:
    ClientConnectionParam connectionParam;
    int port;
    int serverSocket;

    pthread_t serverThreadId;

    /**
     * Set port from input parameter file.
     * @param fileName file name of parameter for port.
     */
    void setPortFromFile(const char *fileName);
};


#endif //EX4_SERVER_H
