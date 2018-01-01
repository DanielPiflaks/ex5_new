//
// Created by danielpiflaks on 01/01/18.
//

#ifndef EX5_HANDELCLIENTSTHREADS_H
#define EX5_HANDELCLIENTSTHREADS_H


#include <sys/types.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class HandelClientsThreads {
public:
    static HandelClientsThreads *getGameManager();

    void addThreadHandler(int clientSocket, pthread_t pthread);

    void removeThreadHandler(pthread_t pthread);

private:
    HandelClientsThreads() {}; // Private c'tor
    HandelClientsThreads(const HandelClientsThreads &copy); // Private copy c'tor
    ~HandelClientsThreads() {};

    static HandelClientsThreads *handelClientsThreads;
    map<int, pthread_t> threadsMap;
};


#endif //EX5_HANDELCLIENTSTHREADS_H
