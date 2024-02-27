#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#define MAX_TASKS 10

#include <stdio.h>
#include <Arduino.h>

#include "Task.h"

class TaskScheduler{
    private:
        Task *firstTask = nullptr;
        Task *currentTask = nullptr;
        int taskCount = 0;

    public:
        TaskScheduler();
        TaskScheduler(Task *firstTask);

        void addTask(void (*task)(), PRIORITY priority);
        void setFirstTask(Task *task);
        void setCurrentTask(Task *task);
        void executeTasks();
};

#endif
