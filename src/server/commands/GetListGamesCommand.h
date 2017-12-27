//
// Created by danielpiflaks on 23/12/17.
//

#ifndef EX5_GETLISTGAMESCOMMAND_H
#define EX5_GETLISTGAMESCOMMAND_H


#include "Command.h"
#include "../Server.h"

class GetListGamesCommand : public Command {
public:
    explicit GetListGamesCommand(Server *server);

    virtual void execute(vector <string> args);
private:
    Server *server;
};


#endif //EX5_GETLISTGAMESCOMMAND_H
