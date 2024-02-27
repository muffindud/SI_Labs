#include "Task.h"

Task::Task(PRIORITY priority, void (*task)(), bool permanent = false){
    this->previousTask = nullptr;
    this->nextTask = nullptr;
    this->priority = MEDIUM_PRIORITY;
    this->task = task;
    this->permanent = false;
}

Task::Task(Task *previousTask, PRIORITY priority, void (*task)(), bool permanent){
    this->previousTask = previousTask;
    this->priority = priority;
    this->task = task;
}

Task::Task(Task *previousTask, Task *nextTask, PRIORITY priority, void (*task)(), bool permanent){
    this->previousTask = previousTask;
    this->nextTask = nextTask;
    this->priority = priority;
    this->task = task;
}

void Task::execute(){
    task();
    return;
}

