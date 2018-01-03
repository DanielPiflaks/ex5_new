/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "Server.h"
#include "HandelClient.h"
#include "HandelClientsThreads.h"

#define MAX_CONNECTED_CLIENTS 30

Server::Server(const char *fileName) {
    //Set port from parameter file.
    setPortFromFile(fileName);
}

Server::Server(int port) : port(port) {
}

void Server::start() {
    //Create server socket.
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    //Check that server socket opened properly.
    if (serverSocket == -1) {
        throw "Error opening socket";
    }

    //Create server address.
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    //Set parameters for server address.
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons((uint16_t) port);
    //Bind server socket to server address and check that binding worked.
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }

    // Start listening to incoming connections
    if (listen(serverSocket, MAX_CONNECTED_CLIENTS) < 0) {
        throw "Error listening";
    }

    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    memset(&clientAddressLen, 0, sizeof(clientAddressLen));

    //Create connection params to handle clients connection.
    connectionParam.serverSocket = serverSocket;
    connectionParam.clientAddress = clientAddress;
    memset(&connectionParam.clientAddressLen, 0, sizeof(connectionParam.clientAddressLen));
    connectionParam.clientAddressLen = clientAddressLen;
    //Create thread to wait for clients connections.
    pthread_create(&serverThreadId, NULL, &HandelClient::waitForClients, (void *) &connectionParam);
}

void Server::setPortFromFile(const char *fileName) {
    //Set const sub string as expected.
    const string portSubString = "PORT:";
    //Set const comment char symbol.
    const char commentChar = '#';
    string singleLine, stringPort;
    ifstream inFile;
    //Open file.
    inFile.open(fileName);
    //Check if file opened.
    if (inFile.is_open()) {
        //Check if file is empty.
        if (!inFile.eof()) {
            //Get next line.
            getline(inFile, singleLine);
        }
        //Get all lines until we get to end of file.
        while (!inFile.eof()) {
            //Check if line is not comment line.
            if (singleLine.find(commentChar) != 0) {
                //Check if line contains ip sub string.
                if (singleLine.find(portSubString) == 0) {
                    stringPort = singleLine.substr(portSubString.length(), singleLine.length());
                    //Convert string to int.
                    sscanf(stringPort.c_str(), "%d", &port);
                }
            }
            //Get next line.
            getline(inFile, singleLine);
        }
        //Close file when there is no more lines to read.
        inFile.close();
    } else {
        //Throw exception when we can't open file.
        throw "Can't open settings file!";
    }
}

void Server::stop() {
    HandelClientsThreads::getHandleClientsThreads()->cancelAllThreads();
    pthread_cancel(serverThreadId);
    close(serverSocket);
    cout << "Server stopped" << endl;
}

string Server::receive(int clientSocket) {
    long n;
    char message[50] = {0};

    //Read from socket.
    n = read(clientSocket, &message, sizeof(message));
    //If reading failed.
    if (n == -1) {
        throw "Error reading from client.";
    } else if (n == 0) {
        //Checks if client disconnected and prints it.
        strcpy(message, "Client disconnected");
        cout << message << endl;
    }
    return message;
}

void Server::send(int clientSocket, string param) {
    char messageBuffer[50] = {0};
    strcpy(messageBuffer, param.c_str());
    //Send message.
    long n = write(clientSocket, &messageBuffer, sizeof(messageBuffer));
    if (n == -1) {
        throw "Error writing to client";
    } else if (n == 0) {
        //Checks if client disconnected and prints it.
        strcpy(messageBuffer, "Client disconnected");
        cout << messageBuffer << endl;
    }
}
