/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex4
******************************************/

#include <iostream>
#include <cstdlib>
#include "Server.h"
#include "commands/CommandsManager.h"
#include "commands/GamesThreadsList.h"
#include "HandelClient.h"


int main() {
    //Name of file with port and IP data.
    const char *fileName = "ServerConnectionSettings.txt";


    pthread_t threadWaitForClient;

    try {
        Server *server = new Server(fileName);
        CommandsManager *commandsManager = new CommandsManager(server);
        ClientConnectionParam connectionParam = server->start();
        HandelClientParams handelClientParams;
        handelClientParams.connectionParam = connectionParam;
        handelClientParams.commandsManager = commandsManager;
        pthread_create(&threadWaitForClient, NULL, HandelClient::waitForClients, (void *) &handelClientParams);
        GamesThreadsList *threadsList;

        //server.start();
        server->stop();
    } catch (const char *msg) {
        //If something went wrong print the reason.
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }

    return 0;
}

