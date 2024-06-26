#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <stdio.h>

#include "Task.h"

struct TaskQueue{
    void (*task)();
    PRIORITY priority;
    bool permanent;
    TaskQueue *nextTask;
};

class TaskScheduler{
    private:
        Task *firstTask = nullptr;
        Task *currentTask = nullptr;
        int taskCount = 0;
        int loopCounter = 0;

        TaskQueue *taskQueue = nullptr;
        TaskQueue *lastTask = nullptr;

        void addTask(void (*task)(), PRIORITY priority, bool permanent = false);

    public:
        TaskScheduler();
        TaskScheduler(Task *firstTask);

        void addTaskToQueue(void (*task)(), PRIORITY priority, bool permanent);
        void taskReset();
        void executeTasks();
        void executeTask();

        void printTaskList();
};

#endif
