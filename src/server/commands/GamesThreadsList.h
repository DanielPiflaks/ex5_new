//
// Created by sapirblutman on 28/12/17.
//

#ifndef EX5_GAMESTHREADSLIST_H
#define EX5_GAMESTHREADSLIST_H


class GamesThreadsList {

public:
    static GamesThreadsList *getThreadsList();

    void addToList();

private:
    GamesThreadsList() {}; // Private c'tor
    GamesThreadsList(const GamesThreadsList &copy); // Private copy c'tor
    ~GamesThreadsList() {};

    static GamesThreadsList *threadsList;

};


#endif //EX5_GAMESTHREADSLIST_H
