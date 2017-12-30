//
// Created by danielpiflaks on 27/12/17.
//

#include <iostream>
#include "CommandsManager.h"
#include "StartGameCommand.h"
#include "GetListGamesCommand.h"
#include "JoinGameCommand.h"
#include "CloseGameCommand.h"

CommandsManager::CommandsManager(Server *server) : server(server) {
    commandsMap["start"] = new StartGameCommand(server);
    commandsMap["list_games"] = new GetListGamesCommand(server);
    commandsMap["join"] = new JoinGameCommand(server);
    commandsMap["close"] = new CloseGameCommand(server);
}

void CommandsManager::executeCommand(string
                                     command, vector<string> args) {
    map<string, Command *>::iterator it;
    it = commandsMap.find(command);
    if (it == commandsMap.end()){
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