/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#ifndef EX5_COMMANDSMANAGER_H
#define EX5_COMMANDSMANAGER_H


#include <map>
#include "Command.h"
#include "../Server.h"

class CommandsManager {
public:
    static CommandsManager *getCommandManager();

    void executeCommand(string command,
                        vector<string> args);
private:
    explicit CommandsManager();
    ~CommandsManager();

    static CommandsManager *commandsManager;
    map<string, Command *> commandsMap;
};


#endif //EX5_COMMANDSMANAGER_H
