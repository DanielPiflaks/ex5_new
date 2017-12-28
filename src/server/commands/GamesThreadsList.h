//
// Created by sapirblutman on 28/12/17.
//

#ifndef EX5_GAMESTHREADSLIST_H
#define EX5_GAMESTHREADSLIST_H


#include <sys/param.h>
#include <iostream>

using namespace std;

class GamesThreadsList {

public:
    static GamesThreadsList *getThreadsList();

    void addToList(pthread_t threadName);

private:
    GamesThreadsList() {}; // Private c'tor
    GamesThreadsList(const GamesThreadsList &copy); // Private copy c'tor
    ~GamesThreadsList() {};

    static GamesThreadsList *threadsList;

};


#endif //EX5_GAMESTHREADSLIST_H
