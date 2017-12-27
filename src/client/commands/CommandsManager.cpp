//
// Created by danielpiflaks on 24/12/17.
//

#include "CommandsManager.h"

CommandsManager::CommandsManager(Client client) : client(client) {
    //commandsMap["print"] = new PrintCommand();
    // Add more commands...
}

void CommandsManager::executeCommand(string
                                     command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}