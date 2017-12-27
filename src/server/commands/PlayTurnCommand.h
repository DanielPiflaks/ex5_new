//
// Created by danielpiflaks on 23/12/17.
//

#ifndef EX5_PLAYTURNCOMMAND_H
#define EX5_PLAYTURNCOMMAND_H


#include "Command.h"
#include "../Server.h"

class PlayTurnCommand : public Command {
public:
    explicit PlayTurnCommand(Server *server);

    virtual void execute(vector<string> args);
private:
    Server *server;
};


#endif //EX5_PLAYTURNCOMMAND_H
