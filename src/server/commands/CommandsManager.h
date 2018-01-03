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
    /**
     * Get command manager.
     * @return
     */
    static CommandsManager *getCommandManager();

    /**
     *
     * @param command
     * @param args
     */
    void executeCommand(string command,
                        vector<string> args);

private:
    explicit CommandsManager();

    ~CommandsManager();

    static CommandsManager *commandsManager;
    map<string, Command *> commandsMap;
    static pthread_mutex_t lock;
};


#endif //EX5_COMMANDSMANAGER_H
