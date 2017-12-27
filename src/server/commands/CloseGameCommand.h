//
// Created by danielpiflaks on 23/12/17.
//

#ifndef EX5_CLOSEGAMECOMMAND_H
#define EX5_CLOSEGAMECOMMAND_H


#include "Command.h"
#include "../Server.h"

class CloseGameCommand : public Command {
public:
    explicit CloseGameCommand(Server server);

    virtual void execute(vector<string> args);
private:
    Server server;
};


#endif //EX5_CLOSEGAMECOMMAND_H
