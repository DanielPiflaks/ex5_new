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

    //Create index for first and second players.
    const int firstPlayerIndex = 1;
    const int secondPlayerIndex = 2;
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

    connectionParam.serverSocket = serverSocket;
    connectionParam.clientAddress = clientAddress;
    memset(&connectionParam.clientAddressLen, 0, sizeof(connectionParam.clientAddressLen));
    connectionParam.clientAddressLen = clientAddressLen;

    //clientSocket1 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);

    pthread_create(&serverThreadId, NULL, &HandelClient::waitForClients, (void *) &connectionParam);
    /*cout << "Waiting for client connections..." << endl;
    // Accept first client.
    clientSocket1 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
    //Check that socket for first client opened correctly.
    if (clientSocket1 == -1) {
        throw "Error on accept";
    }
    cout << "First client connected" << endl;*/

/*    Server::StartGameAgain startGameAgain = Server::StartGame;
    while (startGameAgain == Server::StartGame){
        cout << "Waiting for client connections..." << endl;
        // Accept first client.
        clientSocket1 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        //Check that socket for first client opened correctly.
        if (clientSocket1 == -1) {
            throw "Error on accept";
        }
        cout << "First client connected" << endl;

        // Write the result back to the client.
        long n = write(clientSocket1, &firstPlayerIndex, sizeof(firstPlayerIndex));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }

        // Accept second client.
        clientSocket2 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);

        if (clientSocket2 == -1) {
            throw "Error on accept";
        }
        cout << "Second client connected" << endl;
        // Write the result back to the client.
        n = write(clientSocket2, &secondPlayerIndex, sizeof(secondPlayerIndex));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }

        notifyFirstPlayerStart();
        startGameAgain = sendAndReceiveMoves();
        if (startGameAgain == Server::StartGame){
            close(clientSocket1);
            close(clientSocket2);
        }
    }*/
}

void Server::notifyFirstPlayerStart(int clientSocket) {
    const int trueParam = 1;
    //Write to socket 1.
    long n = write(clientSocket, &trueParam, sizeof(trueParam));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return;
    }
}

Server::StartGameAgain Server::sendAndReceiveMoves() {
    const char *endGameMessage = "End";
    long n;
    char message[7];
    while (true) {
        //Read from 1st socket.
        //n = read(clientSocket1, &message, sizeof(message));
        //If reading failed.
        if (n == -1) {
            throw "Error reading move";
        } else if (n == 0) {
            return StartGame;
        }

        if (strcmp(message, endGameMessage) == 0) {
            //If massage from socket is about game ending then stop the loop.
            break;
        }

        //Write to 2nd socket.
        //long n = write(clientSocket2, &message, sizeof(message));
        //If writing failed.
        if (n == -1) {
            throw "Error reading move";
        }

        //Read from 2nd socket.
        //n = read(clientSocket2, &message, sizeof(message));
        //If reading failed.
        if (n == -1) {
            throw "Error reading move";
        } else if (n == 0) {
            return StartGame;
        }

        if (strcmp(message, endGameMessage) == 0) {
            //If massage from socket is about game ending then stop the loop.
            break;
        }

        //Write to 1st socket.
        //n = write(clientSocket1, &message, sizeof(message));
        //If writing failed.
        if (n == -1) {
            throw "Error reading move";
        }
    }
    //return EndGame;
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

    //Read from 1st socket.
    n = read(clientSocket, &message, sizeof(message));
    //If reading failed.
    if (n == -1) {
        throw "Error reading from client.";
    }
    return message;
}

void Server::send(int clientSocket, string param) {
    char messageBuffer[50] = {0};
    strcpy(messageBuffer, param.c_str());

    long n = write(clientSocket, &messageBuffer, sizeof(messageBuffer));
    if (n == -1) {
        throw "Error writing to client";
    }
}


/*void *Server::waitForClients(void *clientConnectionParam) {
    vector<pthread_t> threadsVector;
    int threadCounter = 0;

    ClientConnectionParam *connectionParam = (struct ClientConnectionParam *) clientConnectionParam;

    int counter = 0;
    while (counter < 15) {
        int clientSocket = connectToClient(connectionParam);
        HandelClientParam handleClientParam;
        handleClientParam.clientSocket = clientSocket;
        //handleClientParam.commandsManager
        //pthread_create(&threadsVector[threadCounter], NULL, connectToClient, clientConnectionParam);
        counter++;
    }
}*/

/*int Server::connectToClient(ClientConnectionParam *parameters) {
    cout << "Waiting for client connections..." << endl;
    // Accept first client.
    int clientSocket = accept(parameters->serverSocket, (struct sockaddr *) &parameters->clientAddress,
                              &parameters->clientAddressLen);
    //Check that socket for first client opened correctly.
    if (clientSocket == -1) {
        throw "Error on accept";
    }
    cout << "First client connected" << endl;
    return clientSocket;
}*/

/*void *Server::handleClient(void *clientSocket) {
    return NULL;
}*/

