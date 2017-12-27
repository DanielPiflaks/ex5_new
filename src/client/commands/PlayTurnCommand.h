//
// Created by danielpiflaks on 23/12/17.
//

#ifndef EX5_PLAYTURNCOMMAND_H
#define EX5_PLAYTURNCOMMAND_H


#include "../Client.h"
#include "Command.h"

class PlayTurnCommand : Command {
public:
    explicit PlayTurnCommand(Client client);

    virtual void execute(vector<string> args);

private:
    Client client;
};


#endif //EX5_PLAYTURNCOMMAND_H
