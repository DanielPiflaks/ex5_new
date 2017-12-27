//
// Created by danielpiflaks on 23/12/17.
//

#ifndef EX5_CLOSEGAMECOMMAND_H
#define EX5_CLOSEGAMECOMMAND_H


#include "Command.h"
#include "../Client.h"

class CloseGameCommand : Command {
public:
    explicit CloseGameCommand(Client client);

    virtual void execute(vector<string> args);

private:
    Client client;
};


#endif //EX5_CLOSEGAMECOMMAND_H
