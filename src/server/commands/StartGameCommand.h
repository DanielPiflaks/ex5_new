/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#ifndef EX5_STARTGAMECOMMAND_H
#define EX5_STARTGAMECOMMAND_H


#include "Command.h"
#include "../Server.h"

class StartGameCommand : public Command {
public:
    explicit StartGameCommand();

    virtual void execute(vector<string> args);
};


#endif //EX5_STARTGAMECOMMAND_H
