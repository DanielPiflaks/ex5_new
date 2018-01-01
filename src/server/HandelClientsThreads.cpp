//
// Created by danielpiflaks on 01/01/18.
//

#include <algorithm>
#include <unistd.h>
#include "HandelClientsThreads.h"

HandelClientsThreads *HandelClientsThreads::handelClientsThreads = 0;
pthread_mutex_t HandelClientsThreads::lock;

HandelClientsThreads *HandelClientsThreads::getHandleClientsThreads() {
    if (handelClientsThreads == 0) {
        pthread_mutex_lock(&lock);
        if (handelClientsThreads == 0) {
            handelClientsThreads = new HandelClientsThreads();
        }
        pthread_mutex_unlock(&lock);
    }
    return handelClientsThreads;
}

void HandelClientsThreads::addThreadHandler(int clientSocket, pthread_t pthread) {
    threadsMap[clientSocket] = pthread;
}

void HandelClientsThreads::removeThreadHandler(pthread_t pthread) {
    for (map<int, pthread_t>::iterator currentThread = threadsMap.begin();
         currentThread != threadsMap.end(); ++currentThread) {
        if (pthread_equal(currentThread->second, pthread)) {
            pthread_cancel(pthread);
            close(currentThread->first);
            threadsMap.erase(currentThread);
            break;
        }
    }
}

void HandelClientsThreads::cancelAllThreads() {
    for (map<int, pthread_t>::iterator currentThread = threadsMap.begin();
         currentThread != threadsMap.end(); ++currentThread) {
        pthread_cancel(currentThread->second);
        close(currentThread->first);
        threadsMap.erase(currentThread);
    }
}

