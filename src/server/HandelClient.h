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
     *
     * @param connectionParam
     * @return
     */
    static void *waitForClients(void *connectionParam);

    static void *handleClient(void *socket);

    static int connectToClient(ClientConnectionParam *parameters);
};


#endif //EX5_HANDELCLIENT_H
