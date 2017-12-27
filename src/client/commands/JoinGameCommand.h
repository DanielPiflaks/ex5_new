//
// Created by danielpiflaks on 23/12/17.
//

#ifndef EX5_JOINGAMECOMMAND_H
#define EX5_JOINGAMECOMMAND_H


#include "Command.h"
#include "../Client.h"

class JoinGameCommand : Command {
public:
    explicit JoinGameCommand(Client client);

    virtual void execute(vector<string> args);

private:
    Client client;
};


#endif //EX5_JOINGAMECOMMAND_H
