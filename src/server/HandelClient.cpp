//
// Created by danielpiflaks on 27/12/17.
//

#include <algorithm>
#include "HandelClient.h"


void *HandelClient::waitForClients(void *handleClientParam) {
    vector<pthread_t> threadsVector;
    int threadCounter = 0;

    HandelClientParams *handelClient = (struct HandelClientParams *) handleClientParam;

    while (threadCounter < 15) {
        int clientSocket = connectToClient(handelClient->connectionParam);
        HandelClientParams handleClientParam;
        handleClientParam.clientSocket = clientSocket;
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
    const char paramTokenStart = '<';
    const char paramTokenEnd = '>';
    HandelClientParams *handelClient = (struct HandelClientParams *) handleClientParam;

    string receivedMessage = Server::receive(handelClient->clientSocket);

    vector<string> args;
    unsigned long startArgPlace = 0;
    unsigned long endArgPlace = 0;
    do {
        startArgPlace = receivedMessage.find(paramTokenStart, startArgPlace);
        if (startArgPlace == string::npos) {
            break;
        }

        endArgPlace = receivedMessage.find(paramTokenEnd, endArgPlace);
        if (endArgPlace == string::npos) {
            break;
        }
        string arg = receivedMessage.substr(startArgPlace + 1, endArgPlace - 1);
        args.push_back(arg);

    } while (true);

    startArgPlace = receivedMessage.find(paramTokenStart);
    string command;
    if (startArgPlace == string::npos) {
        command = receivedMessage;
    } else {
        command = receivedMessage.substr(0, startArgPlace - 1);
    }

    command.erase(remove_if(command.begin(), command.end(), ::isspace), command.end());
    handelClient->commandsManager->executeCommand(command, args);
}

