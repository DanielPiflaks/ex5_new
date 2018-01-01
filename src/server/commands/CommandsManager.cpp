/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#include <iostream>
#include "CommandsManager.h"
#include "StartGameCommand.h"
#include "GetListGamesCommand.h"
#include "JoinGameCommand.h"
#include "CloseGameCommand.h"

CommandsManager *CommandsManager::commandsManager = 0;
pthread_mutex_t CommandsManager::lock;

CommandsManager *CommandsManager::getCommandManager() {
    if (commandsManager == 0) {
        pthread_mutex_lock(&lock);
        if (commandsManager == 0) {
            commandsManager = new CommandsManager();
        }
        pthread_mutex_unlock(&lock);
    }
    return commandsManager;
}

CommandsManager::CommandsManager() {
    commandsMap["start"] = new StartGameCommand();
    commandsMap["list_games"] = new GetListGamesCommand();
    commandsMap["join"] = new JoinGameCommand();
    commandsMap["close"] = new CloseGameCommand();
}

void CommandsManager::executeCommand(string
                                     command, vector<string> args) {
    map<string, Command *>::iterator it;
    it = commandsMap.find(command);
    if (it == commandsMap.end()) {
        cout << "There is no such command!";
        return;
    }

    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}