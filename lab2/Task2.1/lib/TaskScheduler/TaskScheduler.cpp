#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(){}

TaskScheduler::TaskScheduler(Task *firstTask){
    this->firstTask = firstTask;
    this->currentTask = firstTask;
    this->taskCount = 1;
}

void TaskScheduler::addTask(void (*task)(), PRIORITY priority, bool permanent){
    if(firstTask == nullptr){
        firstTask = new Task(task, priority, permanent);
        currentTask = firstTask;
        taskCount++;
        return;
    }else{
        Task *tempTask = firstTask;

        while(true){
            if(tempTask->priority <= priority){
                if(tempTask->nextTask == nullptr){
                    tempTask->nextTask = new Task(tempTask, task, priority, permanent);
                    taskCount++;
                    break;
                }else{
                    tempTask = tempTask->nextTask;
                }
            }else{
                if(tempTask->previousTask == nullptr){
                    firstTask = new Task(task, priority, permanent);
                    firstTask->nextTask = tempTask;
                    tempTask->previousTask = firstTask;
                    taskCount++;
                    break;
                }else{
                    tempTask->previousTask->nextTask = new Task(tempTask->previousTask, task, priority, permanent);
                    tempTask->previousTask->nextTask->nextTask = tempTask;
                    tempTask->previousTask = tempTask->previousTask->nextTask;
                    taskCount++;
                    break;
                }
            }
        }
    }

    return;
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
        // unsigned long currentTime = micros();

        currentTask->execute();
        prevTask = currentTask;
        currentTask = currentTask->nextTask;

        if(!prevTask->permanent){
            if(prevTask == firstTask){
                firstTask = currentTask;
            }
            prevTask->previousTask->nextTask = currentTask;
            taskCount--;
            delete prevTask;
        }

        // Take time delta here
        // unsigned long delta = micros() - currentTime;
        // printf("Delta: %ld \n\r", delta);

        // delay((MICROSECONDS_PER_TASK - delta) / 1000);
        // delayMicroseconds((MICROSECONDS_PER_TASK - delta) % 1000);

        if(currentTask == nullptr){
            currentTask = firstTask;
            break;
        }
    }
}

void TaskScheduler::executeTask(){
    Task *prevTask = currentTask;

    currentTask->execute();
    currentTask = currentTask->nextTask;

    if(!prevTask->permanent){
        if(prevTask == firstTask){
            firstTask = currentTask;
        }

        prevTask->previousTask->nextTask = currentTask;
        taskCount--;
        delete prevTask;
    }

    if(currentTask == nullptr){
        currentTask = firstTask;
    }

    loopCounter = (loopCounter + 1) % taskCount;

    return;
}

void TaskScheduler::printTaskList(){
    Task *tempTask = firstTask;

    while(true){
        printf("Priority: %d, Permanent: %d\n\r", tempTask->priority, tempTask->permanent);

        if(tempTask->nextTask == nullptr){
            break;
        }else{
            tempTask = tempTask->nextTask;
        }
    }

    return;
}
