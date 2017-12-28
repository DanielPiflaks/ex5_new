//
// Created by danielpiflaks on 27/12/17.
//

#ifndef EX5_HANDELCLIENT_H
#define EX5_HANDELCLIENT_H

#include "Server.h"
#include "../client/commands/CommandsManager.h"

#include <iostream>

struct HandelClientParams {
    struct ClientConnectionParam connectionParam;
    CommandsManager *commandsManager;
    int clientSocket;
};


class HandelClient {
public:
    static void *waitForClients(void *handleClientParam);

    static void *handleClient(void *handleClientParam);

    static int connectToClient(ClientConnectionParam parameters);
};


#endif //EX5_HANDELCLIENT_H
