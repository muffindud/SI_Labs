#include "Task.h"

Task::Task(void (*task)(), PRIORITY priority, bool permanent){
    this->previousTask = nullptr;
    this->nextTask = nullptr;
    this->priority = priority;
    this->task = task;
    this->permanent = permanent;
}

Task::Task(Task *previousTask, void (*task)(), PRIORITY priority, bool permanent){
    this->previousTask = previousTask;
    this->priority = priority;
    this->task = task;
    this->permanent = permanent;
}

Task::Task(Task *previousTask, Task *nextTask, void (*task)(), PRIORITY priority, bool permanent){
    this->previousTask = previousTask;
    this->nextTask = nextTask;
    this->priority = priority;
    this->task = task;
    this->permanent = permanent;
}

void Task::execute(){
    task();
    return;
}
