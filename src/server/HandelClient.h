/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#ifndef EX5_HANDELCLIENT_H
#define EX5_HANDELCLIENT_H

#include "Server.h"
#include "commands/CommandsManager.h"
#include <iostream>

class HandelClient {
public:
    /**
     *Waits for clients connection.
     * @param connectionParam connection parameters to accomplish connection.
     * @return null.
     */
    static void *waitForClients(void *connectionParam);

    /**
     * Handles client.
     * @param socket socket to handle client.
     * @return null.
     */
    static void *handleClient(void *socket);

    /**
     * Connect to client.
     * @param parameters connection parameters.
     * @return client socket.
     */
    static int connectToClient(ClientConnectionParam *parameters);
};


#endif //EX5_HANDELCLIENT_H
