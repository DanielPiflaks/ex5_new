/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <algorithm>
#include <sstream>
#include "HandelClient.h"
#include "HandelClientsThreads.h"


void *HandelClient::waitForClients(void *connectionParam) {
    vector<pthread_t> threadsVector;
    int threadCounter = 0;

    ClientConnectionParam *params = (struct ClientConnectionParam *) connectionParam;

    while (true) {
        int clientSocket = connectToClient(params);
        pthread_t newThread;
        threadsVector.push_back(newThread);
        pthread_create(&threadsVector[threadCounter], NULL, handleClient, (void *) clientSocket);

        HandelClientsThreads::getHandleClientsThreads()->addThreadHandler(clientSocket,
                                                                          threadsVector[threadCounter]);
        threadCounter++;
    }
}

int HandelClient::connectToClient(ClientConnectionParam *parameters) {
    cout << "Waiting for client connections..." << endl;
    // Accept first client.
    int clientSocket = accept(parameters->serverSocket, (struct sockaddr *) &parameters->clientAddress,
                              &parameters->clientAddressLen);
    //Check that socket for first client opened correctly.
    if (clientSocket == -1) {
        throw "Error on accept";
    }
    cout << "Client connected" << endl;
    return clientSocket;
}

void *HandelClient::handleClient(void *socket) {
    long clientSocket = (long) socket;

    string receivedMessage = Server::receive(clientSocket);

    //Convert int to string.
    stringstream ss;
    ss << clientSocket;
    string clientSocketString = ss.str();

    istringstream iss(receivedMessage);
    string command;
    iss >> command;
    vector<string> args;
    args.push_back(clientSocketString);
    while (iss) {
        string arg;
        iss >> arg;
        args.push_back(arg);
    }

    command.erase(remove_if(command.begin(), command.end(), ::isspace), command.end());
    CommandsManager::getCommandManager()->executeCommand(command, args);
}



