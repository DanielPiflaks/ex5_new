//
// Created by danielpiflaks on 27/12/17.
//

#include <algorithm>
#include <cstdio>
#include <sstream>
#include "HandelClient.h"


void *HandelClient::waitForClients(void *handleClientParam) {
    vector<pthread_t> threadsVector;
    int threadCounter = 0;

    HandelClientParams *handelClient = (struct HandelClientParams *) handleClientParam;

    while (threadCounter < 15) {
        int clientSocket = connectToClient(handelClient->connectionParam);
        HandelClientParams handleClientParam;
        handleClientParam.clientSocket = clientSocket;
        handleClientParam.commandsManager = handelClient->commandsManager;
        pthread_t newThread;
        threadsVector.push_back(newThread);
        pthread_create(&threadsVector[threadCounter], NULL, handleClient, (void *) &handleClientParam);

        threadCounter++;
    }
}

int HandelClient::connectToClient(ClientConnectionParam parameters) {
    cout << "Waiting for client connections..." << endl;
    // Accept first client.
    int clientSocket = accept(parameters.serverSocket, (struct sockaddr *) &parameters.clientAddress,
                              &parameters.clientAddressLen);
    //Check that socket for first client opened correctly.
    if (clientSocket == -1) {
        throw "Error on accept";
    }
    cout << "First client connected" << endl;
    return clientSocket;
}

void *HandelClient::handleClient(void *handleClientParam) {
    HandelClientParams *handelClient = (struct HandelClientParams *) handleClientParam;

    string receivedMessage = Server::receive(handelClient->clientSocket);

    vector<string> args;

    //Convert int to string.
    stringstream ss;
    ss << handelClient->clientSocket;
    string clientSocketString = ss.str();

    args.push_back(clientSocketString);

    string command;
    if (receivedMessage.find(' ') == string::npos) {
        command = receivedMessage;
    } else {
        unsigned long startArgPlace = receivedMessage.find(' ');
        if (startArgPlace == string::npos) {
            command = receivedMessage;
        } else {
            command = receivedMessage.substr(0, startArgPlace);
        }

        string arg = receivedMessage.substr(startArgPlace + 1, receivedMessage.size());
        args.push_back(arg);
    }

    command.erase(remove_if(command.begin(), command.end(), ::isspace), command.end());
    handelClient->commandsManager->executeCommand(command, args);
}



