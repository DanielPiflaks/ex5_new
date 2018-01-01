/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#ifndef EX5_JOINGAMECOMMAND_H
#define EX5_JOINGAMECOMMAND_H


#include "Command.h"
#include "../Server.h"

class JoinGameCommand : public Command {
public:
    explicit JoinGameCommand();

    virtual void execute(vector<string> args);
};


#endif //EX5_JOINGAMECOMMAND_H
