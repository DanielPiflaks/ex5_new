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
    /**
     * Return handle clients threads vector.
     * @return  handle client threads vector.
     */
    static HandelClientsThreads *getHandleClientsThreads();

    /**
     * Adding thread handler with wanted client socket to map.
     * @param clientSocket client socket to add.
     * @param pthread thread to add.
     */
    void addThreadHandler(int clientSocket, pthread_t pthread);

    /**
     * Removes thread handler from map.
     * @param pthread wanted thread to remove.
     */
    void removeThreadHandler(pthread_t pthread);

    /**
     * Removes all threads.
     */
    void cancelAllThreads();

private:
    /**
     * Constructor
     */
    HandelClientsThreads() {};

    /**
     * Copy constructor
     * @param copy handleclientsThreads to copy.
     */
    HandelClientsThreads(const HandelClientsThreads &copy);

    /**
     * Destructor.
     */
    ~HandelClientsThreads() {};

    static HandelClientsThreads *handelClientsThreads;
    map<int, pthread_t> threadsMap;
    static pthread_mutex_t lock1;
    static pthread_mutex_t lock2;
    static pthread_mutex_t lock3;
    static pthread_mutex_t lock4;
};


#endif //EX5_HANDELCLIENTSTHREADS_H
