/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#ifndef EX4_CLIENT_H
#define EX4_CLIENT_H

using namespace std;

#include <iostream>
#include "BoardCoordinates.h"

class Client {
public:
    /**
     * Client constructor if given file name,extract from file: IP, port.
     * @param fileName given file name.
     */
    explicit Client(const char *fileName);

    /**
     * Client constructor if given IP and port number.
     * @param serverIP server IP.
     * @param serverPort port number.
     */
    Client(char *serverIP, int serverPort);

    ~Client();

    /**
     * Connect to existing socket that compatible to IP and port.
     * After connecting- read the client's player number.
     * @return 1 is client is first, 2 if second.
     */
    void connectToServer();

    /**
     * Closing socket from server.
     */
    void disconnectServer();

    /**
     *If there isn't any possible move(=>given move= (0,0)) then write to socket appropriate massage,
     * else- write the move coordinate.
     * @param move the client latest move (will be (0, 0) if there isn't one).
     */
    void sendMove(BoardCoordinates move);

    /**
    *Read massage from socket about other player latest move.
    * If massage state that there isn't move- return neutral coordinate (0,0).
     * Else, convert the massage into coordinate.
     * @return neutral coordinate or suitable one, depending on the massage.
    */
    BoardCoordinates receiveMove();

    /**
     * Open file, read from it IP address and port.
     * @param fileName the name of file that we will read IP and port from.
     */
    void setIpAndPortFromFile(const char *fileName);

    /**
     * Getter
     * @return  serverIP.
     */
    const string &getServerIP() const;

    /**
     * Getter
     * @return server port.
     */
    int getServerPort() const;

    /**
     * Set message and send it to server.
     * @param message relevant message to send.
     */
    void send(string message);

    /**
     * Receive message from server.
     * @return relevant message.
     */
    string receive();

    /**
     * Print client menu of options, receive his input for chosen option
     * and keep asking if given option input is invalid.
     * If client ask to open new game or join one then stop asking for
     * input and receive from server this client player turn (1 or 2).
     * @return client selected game.
     */
    string receiveOptionFromClient();

private:
    string serverIP;
    int serverPort;
    int clientSocket;

    string gameName;
};


#endif //EX4_CLIENT_H