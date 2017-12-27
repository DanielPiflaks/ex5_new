//
// Created by danielpiflaks on 23/12/17.
//

#ifndef EX5_STARTGAMECOMMAND_H
#define EX5_STARTGAMECOMMAND_H


#include "Command.h"
#include "../Server.h"

class StartGameCommand : public Command {
public:
    explicit StartGameCommand(Server *server);

    virtual void execute(vector<string> args);
private:
    Server *server;
};


#endif //EX5_STARTGAMECOMMAND_H
