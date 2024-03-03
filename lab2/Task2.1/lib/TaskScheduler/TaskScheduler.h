#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#define MAX_TASKS 10
#define MICROSECONDS_PER_TASK 500000

#include <stdio.h>
#include <Arduino.h>

#include "Task.h"

class TaskScheduler{
    private:
        Task *firstTask = nullptr;
        Task *currentTask = nullptr;
        int taskCount = 0;
        int loopCounter = 0;

    public:
        TaskScheduler();
        TaskScheduler(Task *firstTask);

        void addTask(void (*task)(), PRIORITY priority, bool permanent = false);
        void setFirstTask(Task *task);
        void setCurrentTask(Task *task);
        void executeTasks();
        void executeTask();

        void printTaskList();
};

#endif
