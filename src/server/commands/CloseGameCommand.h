/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#ifndef EX5_CLOSEGAMECOMMAND_H
#define EX5_CLOSEGAMECOMMAND_H


#include "Command.h"
#include "../Server.h"

class CloseGameCommand : public Command {
public:
    /**
     * Constructor.
     */
    explicit CloseGameCommand();

    /**
     * Execute the command.
     * @param args vector of command- first is client socket,
     * second is command args.
     */
    virtual void execute(vector<string> args);
};


#endif //EX5_CLOSEGAMECOMMAND_H
