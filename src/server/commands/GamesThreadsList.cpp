//
// Created by sapirblutman on 28/12/17.
//

#include "GamesThreadsList.h"
#include <iostream>

GamesThreadsList *GamesThreadsList::threadsList = 0;

GamesThreadsList *GamesThreadsList::getThreadsList()
{
    if (threadsList == 0)
    {
        threadsList = new GamesThreadsList;
    }
    return threadsList;
}

void GamesThreadsList::addToList(pthread_t threadName)
{
    cout << "Method of the Singleton class" << endl;
}