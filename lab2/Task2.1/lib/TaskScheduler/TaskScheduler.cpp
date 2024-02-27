#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(){}

TaskScheduler::TaskScheduler(Task *firstTask){
    this->firstTask = firstTask;
    this->currentTask = firstTask;
    this->taskCount = 1;
}

void TaskScheduler::addTask(void (*task)(), PRIORITY priority, bool permanent){
    if(priority < 0 || priority > 4){
        return;
    }

    if(firstTask == nullptr){
        firstTask = new Task(task, priority, permanent);
        currentTask = firstTask;
        taskCount++;
        return;
    }else{
        Task *tempTask = firstTask;
        while(true){
            if(tempTask->priority < priority){
                if(tempTask->nextTask == nullptr){
                    tempTask->nextTask = new Task(tempTask, task, priority, permanent);
                    taskCount++;
                    return;
                }else{
                    tempTask = tempTask->nextTask;
                }
            }
        }
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
            if(prevTask == firstTask){
                firstTask = currentTask;
            }
            prevTask->previousTask->nextTask = currentTask;
            delete prevTask;
        }

        // Take time delta here
        unsigned long delta = micros() - currentTime;
        printf("Delta: %ld \n\r", delta);

        if(currentTask == nullptr){
            currentTask = firstTask;
            break;
        }
    }

    this->executeTasks();
}
