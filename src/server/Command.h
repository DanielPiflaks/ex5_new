/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/

#ifndef EX5_COMMAND_H
#define EX5_COMMAND_H

#include <vector>
#include <string>

using namespace std;

class Command {
public:
    /**
     * Execute the command.
     * @param args vector of command- first is client socket,
     * second is command args.
     */
    virtual void execute(vector<string> args) = 0;

    /**
     * D'constructor.
     */
    virtual ~Command() {}
};

#endif //EX5_COMMAND_H
