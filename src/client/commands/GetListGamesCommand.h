//
// Created by danielpiflaks on 23/12/17.
//

#ifndef EX5_GETLISTGAMESCOMMAND_H
#define EX5_GETLISTGAMESCOMMAND_H


#include "../Client.h"
#include "Command.h"

class GetListGamesCommand : Command {
public:
    explicit GetListGamesCommand(Client
                                 client);

    virtual void execute(vector <string> args);

private:
    Client client;
};


#endif //EX5_GETLISTGAMESCOMMAND_H
