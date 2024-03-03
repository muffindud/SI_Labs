#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(){}

TaskScheduler::TaskScheduler(Task *firstTask){
    this->firstTask = firstTask;
    this->currentTask = firstTask;
}

void TaskScheduler::addTaskToQueue(void (*task)(), PRIORITY priority, bool permanent){
    if(taskQueue == nullptr){
        taskQueue = new TaskQueue{task, priority, permanent, nullptr};
        lastTask = taskQueue;
    }else{
        lastTask->nextTask = new TaskQueue{task, priority, permanent, nullptr};
        lastTask = lastTask->nextTask;
    }
}

void TaskScheduler::addTask(void (*task)(), PRIORITY priority, bool permanent){
    if(firstTask == nullptr){
        firstTask = new Task(task, priority, permanent);
        currentTask = firstTask;
        return;
    }else{
        Task *tempTask = firstTask;

        while(true){
            if(tempTask->priority <= priority){
                if(tempTask->nextTask == nullptr){
                    tempTask->nextTask = new Task(tempTask, task, priority, permanent);
                    break;
                }else{
                    tempTask = tempTask->nextTask;
                }
            }else{
                if(tempTask->previousTask == nullptr){
                    firstTask = new Task(task, priority, permanent);
                    firstTask->nextTask = tempTask;
                    tempTask->previousTask = firstTask;
                    break;
                }else{
                    tempTask->previousTask->nextTask = new Task(tempTask->previousTask, task, priority, permanent);
                    tempTask->previousTask->nextTask->nextTask = tempTask;
                    tempTask->previousTask = tempTask->previousTask->nextTask;
                    break;
                }
            }
        }
    }

    return;
}

void TaskScheduler::taskReset(){
    TaskQueue *tempTask = taskQueue;

    while(true){
        if(tempTask == nullptr){
            lastTask = nullptr;
            break;
        }else{
            addTask(tempTask->task, tempTask->priority, tempTask->permanent);
            tempTask = tempTask->nextTask;
            delete taskQueue;
            taskQueue = tempTask;
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
        delete prevTask;
    }

    if(currentTask == nullptr){
        currentTask = firstTask;
    }

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
