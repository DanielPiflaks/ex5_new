/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex4
******************************************/

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Server.h"
#include <pthread.h>


int main() {
    //Name of file with port and IP data.
    const char *fileName = "ServerConnectionSettings.txt";

    pthread_t threadWaitForClient;


    try {
        Server server(fileName);
        ClientConnectionParam connectionParam = server.start();
        pthread_create(&threadWaitForClient, NULL, Server::waitForClients, (void *) &connectionParam);

        //server.start();
        server.stop();
    } catch (const char *msg) {
        //If something went wrong print the reason.
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }

    return 0;
}

