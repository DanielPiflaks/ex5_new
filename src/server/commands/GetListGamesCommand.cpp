//
// Created by danielpiflaks on 23/12/17.
//

#include <iostream>
#include "GetListGamesCommand.h"
#include "GamesThreadsList.h"

GetListGamesCommand::GetListGamesCommand(Server *server): server(server){};

void GetListGamesCommand::execute(vector<string> args){
    GamesThreadsList::getThreadsList();
}