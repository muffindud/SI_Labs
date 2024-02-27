#ifndef TASK_H
#define TASK_H

enum PRIORITY{
    VERY_HIGH_PRIORITY,
    HIGH_PRIORITY,
    MEDIUM_PRIORITY,
    LOW_PRIORITY,
    VERY_LOW_PRIORITY
};


class Task{
    private:
        void (*task)();

    public:
        Task *previousTask = nullptr;
        Task *nextTask = nullptr;

        Task(void (*task)(), PRIORITY priority, bool permanent = false);
        Task(Task *previousTask, void (*task)(), PRIORITY priority, bool permanent);
        Task(Task *previousTask, Task *nextTask, void (*task)(), PRIORITY priority, bool permanent);

        PRIORITY priority = MEDIUM_PRIORITY;
        bool permanent = false;

        void execute();
};

#endif
