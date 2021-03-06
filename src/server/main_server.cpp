/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <iostream>
#include <cstdlib>
#include "Server.h"
#include "CommandsManager.h"
#include "HandelClient.h"
#include "GameManager.h"

int main() {
    const int threadNumbers = 5;
    //Name of file with port and IP data.
    const char *fileName = "ServerConnectionSettings.txt";

    try {
        Server server(fileName, threadNumbers);
        //Start server.
        server.start();
        //Wait so it won't be printed when thread print it's message.
        sleep(0.2);
        cout << "Enter exit to stop server" << endl;
        string str;
        //Wait until user wants to stop server.
        while (true) {
            cin >> str;
            if (str == "exit") {
                //Stop server.
                server.stop();
                break;
            }
        }
    } catch (const char *msg) {
        //If something went wrong print the reason.
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    return 0;
}

