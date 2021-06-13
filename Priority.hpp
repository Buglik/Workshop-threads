#pragma once
#include <mutex>
#include <condition_variable>

class Priority
{
private:
    std::mutex mutex;
    std::condition_variable cv;
    int counter = 0;

public:
    void wait();
    void incPriority();
    void decPriority();
};