//
// Created by danielpiflaks on 20/01/18.
//

#ifndef EX5_TASK_H
#define EX5_TASK_H

class Task {
public:
    /**
     * Constructor.
     * @param func wanted function.
     * @param arg arguments.
     */
    Task(void * (*func)(void *arg), void* arg) :
            func(func), arg(arg) {}
    /**
     * Execute task.
     */
    void execute() {
        func(arg);
    }
    /**
     * Destructor.
     */
    virtual ~Task() {}
private:
    void * (*func)(void *arg);
    void *arg;
};

#endif //EX5_TASK_H
