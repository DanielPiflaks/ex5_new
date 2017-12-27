//
// Created by danielpiflaks on 24/12/17.
//

#ifndef EX5_COMMANDSMANAGER_H
#define EX5_COMMANDSMANAGER_H


#include <map>
#include "Command.h"
#include "../Server.h"

class CommandsManager {
public:
    explicit CommandsManager(Server server);
    ~CommandsManager();
    void executeCommand(string command,
                        vector<string> args);

private:
    Server server;
    map<string, Command *> commandsMap;
};


#endif //EX5_COMMANDSMANAGER_H
