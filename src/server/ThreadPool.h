//
// Created by danielpiflaks on 20/01/18.
//

#ifndef EX5_THREADPOOL_H
#define EX5_THREADPOOL_H

#include <sys/types.h>
#include <queue>
#include "Task.h"

using namespace std;

class ThreadPool {
public:
    /**
     * Constructor.
     * @param threadsNum number of threads.
     */
    ThreadPool(int threadsNum);
    /**
     * Task to add.
     * @param task wanted task.
     */
    void addTask(Task *task);
    /**
     * Terminate thread pool.
     */
    void terminate();
    /**
     * Destructor.
     */
    virtual ~ThreadPool();
private:
    queue<Task *> tasksQueue;
    pthread_t* threads;
    void executeTasks();
    bool stopped;
    pthread_mutex_t lock;
    static void *execute(void *arg);
};


#endif //EX5_THREADPOOL_H
