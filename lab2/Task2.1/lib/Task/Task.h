#ifndef TASK_H
#define TASK_H

enum PRIORITY{
    VERY_HIGH_PRIORITY = 0,
    HIGH_PRIORITY = 1,
    MEDIUM_PRIORITY = 2,
    LOW_PRIORITY = 3,
    VERY_LOW_PRIORITY = 4
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

        PRIORITY priority;
        bool permanent = false;

        void execute();
};

#endif
