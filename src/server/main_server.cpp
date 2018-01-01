/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <iostream>
#include <cstdlib>
#include "Server.h"
#include "commands/CommandsManager.h"
#include "HandelClient.h"

int main() {
    //Name of file with port and IP data.
    const char *fileName = "ServerConnectionSettings.txt";

    try {
        Server *server = new Server(fileName);
        server->start();

    } catch (const char *msg) {
        //If something went wrong print the reason.
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }

    return 0;
}

