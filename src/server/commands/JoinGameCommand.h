//
// Created by danielpiflaks on 23/12/17.
//

#ifndef EX5_JOINGAMECOMMAND_H
#define EX5_JOINGAMECOMMAND_H


#include "Command.h"
#include "../Server.h"

class JoinGameCommand : public Command {
public:
    explicit JoinGameCommand(Server *server);

    virtual void execute(vector<string> args);
private:
    Server *server;
};


#endif //EX5_JOINGAMECOMMAND_H
