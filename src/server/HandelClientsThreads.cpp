//
// Created by danielpiflaks on 01/01/18.
//

#include <algorithm>
#include <unistd.h>
#include "HandelClientsThreads.h"

HandelClientsThreads *HandelClientsThreads::handelClientsThreads = 0;
pthread_mutex_t HandelClientsThreads::lock1;
pthread_mutex_t HandelClientsThreads::lock2;
pthread_mutex_t HandelClientsThreads::lock3;
pthread_mutex_t HandelClientsThreads::lock4;

HandelClientsThreads *HandelClientsThreads::getHandleClientsThreads() {
    if (handelClientsThreads == 0) {
        pthread_mutex_lock(&lock1);
        if (handelClientsThreads == 0) {
            handelClientsThreads = new HandelClientsThreads();
        }
        pthread_mutex_unlock(&lock1);
    }
    return handelClientsThreads;
}

void HandelClientsThreads::addThreadHandler(int clientSocket, pthread_t pthread) {
    pthread_mutex_lock(&lock2);
    threadsMap[clientSocket] = pthread;
    pthread_mutex_unlock(&lock2);
}

void HandelClientsThreads::removeThreadHandler(pthread_t pthread) {
    for (map<int, pthread_t>::iterator currentThread = threadsMap.begin();
         currentThread != threadsMap.end(); ++currentThread) {
        if (pthread_equal(currentThread->second, pthread)) {
            pthread_mutex_lock(&lock3);
            pthread_cancel(pthread);
            close(currentThread->first);
            threadsMap.erase(currentThread);
            pthread_mutex_unlock(&lock3);
            break;
        }
    }
}

void HandelClientsThreads::cancelAllThreads() {
    for (map<int, pthread_t>::iterator currentThread = threadsMap.begin();
         currentThread != threadsMap.end(); ++currentThread) {
        pthread_mutex_lock(&lock4);
        pthread_cancel(currentThread->second);
        close(currentThread->first);
        threadsMap.erase(currentThread);
        pthread_mutex_unlock(&lock4);
    }
}

