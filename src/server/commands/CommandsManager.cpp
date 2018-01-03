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
    //Check that commands manager isn't initialized yet.
    if (commandsManager == 0) {
        //Lock thread so command manager won't initialize twice.
        pthread_mutex_lock(&lock);
        //Check that after first thread created commands manager second thread won't create it.
        if (commandsManager == 0) {
            //Create command manager.
            commandsManager = new CommandsManager();
        }
        //Unlock thread from commands manager.
        pthread_mutex_unlock(&lock);
    }
    return commandsManager;
}

CommandsManager::CommandsManager() {
    //Initialize map of commands.
    commandsMap["start"] = new StartGameCommand();
    commandsMap["list_games"] = new GetListGamesCommand();
    commandsMap["join"] = new JoinGameCommand();
    commandsMap["close"] = new CloseGameCommand();
}

void CommandsManager::executeCommand(string
                                     command, vector<string> args) {
    //Create iterator.
    map<string, Command *>::iterator it;
    //Find command in iterator.
    it = commandsMap.find(command);
    //Check if iterator ended and we still didn't find wanted command.
    if (it == commandsMap.end()) {
        //Print that there is no such command in our map.
        cout << "There is no such command!";
        //Exit execute command
        return;
    }
    //Get command.
    Command *commandObj = commandsMap[command];
    //Execute command.
    commandObj->execute(args);
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}