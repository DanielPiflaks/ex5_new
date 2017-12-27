//
// Created by danielpiflaks on 23/12/17.
//

#ifndef EX5_STARTGAMECOMMAND_H
#define EX5_STARTGAMECOMMAND_H


#include "Command.h"
#include "../Client.h"

class StartGameCommand : Command {
public:
    explicit StartGameCommand(Client client);

    virtual void execute(vector<string> args);

private:
    Client client;
};


#endif //EX5_STARTGAMECOMMAND_H
