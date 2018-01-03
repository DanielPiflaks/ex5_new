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

    /**
     * Stop function to close sockets.
     */
    void stop();

    /**
     * Receive message from given client socket.
     * @param clientSocket client socket to listen to.
     * @return message from client.
     */
    static string receive(int clientSocket);

    /**
     * Send given string to given client socket.
     * @param clientSocket to send message to.
     * @param param string to send.
     */
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
