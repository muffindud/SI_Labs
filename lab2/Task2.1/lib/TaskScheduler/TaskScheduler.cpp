#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(){}

TaskScheduler::TaskScheduler(Task *firstTask){
    this->firstTask = firstTask;
    this->currentTask = firstTask;
    this->taskCount = 1;
}

void TaskScheduler::addTask(void (*task)(), PRIORITY priority){
    if(priority < 0 || priority > 4){
        return;
    }

    
}

void TaskScheduler::setFirstTask(Task *task){
    firstTask = task;
}

void TaskScheduler::setCurrentTask(Task *task){
    currentTask = task;
}

void TaskScheduler::executeTasks(){
    Task *prevTask = firstTask;
    currentTask = firstTask;

    while(true){
        // Take milliseconds time here
        unsigned long currentTime = micros();

        currentTask->execute();
        prevTask = currentTask;
        currentTask = currentTask->nextTask;

        if(!prevTask->permanent){
            prevTask->previousTask->nextTask = currentTask;
            delete prevTask;
        }

        // Take time delta here
        unsigned long delta = micros() - currentTime;
        printf("Delta: %ld \n\r", delta);
        // printf("Task executed\n\r");

        if(currentTask == nullptr){
            currentTask = firstTask;
            break;
        }
    }

    this->executeTasks();
}
