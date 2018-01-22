/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <algorithm>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include "HandelClient.h"


void *HandelClient::waitForClients(void *connectionParam) {
    vector<pthread_t> threadsVector;
    //int threadCounter = 0;

    //Get client connection params.
    ClientConnectionParam *params = (struct ClientConnectionParam *) connectionParam;
    ThreadPool * threadPool = params->threadPool;

    //Get all connection and assign thread to handle it's requests.
    while (true) {
        int clientSocket = connectToClient(params);

        Task *handleClient = new Task(HandelClient::handleClient, (void *) (intptr_t) clientSocket);
        threadPool->addTask(handleClient);
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
    //Receive wanted command from client.
    string receivedMessage = Server::receive(clientSocket);

    //Convert int to string.
    stringstream ss;
    ss << clientSocket;
    string clientSocketString = ss.str();
    istringstream iss(receivedMessage);
    string command;
    iss >> command;
    vector<string> args;
    //Add client socket to args.
    args.push_back(clientSocketString);
    //Add all args to vector.
    while (iss) {
        string arg;
        iss >> arg;
        args.push_back(arg);
    }
    //Remove all spaces command.
    command.erase(remove_if(command.begin(), command.end(), ::isspace), command.end());
    //Execute command.
    CommandsManager::getCommandManager()->executeCommand(command, args);

}



