//
// Created by danielpiflaks on 24/12/17.
//

#ifndef EX5_COMMANDSMANAGER_H
#define EX5_COMMANDSMANAGER_H


#include <map>
#include "Command.h"
#include "../Client.h"

class CommandsManager {
public:
    CommandsManager(Client client);
    ~CommandsManager();
    void executeCommand(string command,
                        vector<string> args);

private:
    map<string, Command *> commandsMap;
    Client client;
};


#endif //EX5_COMMANDSMANAGER_H
