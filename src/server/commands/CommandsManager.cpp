//
// Created by danielpiflaks on 24/12/17.
//

#include "CommandsManager.h"
#include "StartGameCommand.h"
#include "GetListGamesCommand.h"
#include "JoinGameCommand.h"
#include "PlayTurnCommand.h"
#include "CloseGameCommand.h"

CommandsManager::CommandsManager(Server server) : server(server) {
    commandsMap["start"] = new StartGameCommand(server);
    commandsMap["list_games"] = new GetListGamesCommand(server);
    commandsMap["join"] = new JoinGameCommand(server);
    commandsMap["play"] = new PlayTurnCommand(server);
    commandsMap["close"] = new CloseGameCommand(server);
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