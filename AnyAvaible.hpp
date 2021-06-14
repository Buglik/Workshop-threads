#pragma once
#include <mutex>
#include <condition_variable>

class AnyAvaible
{
private:
    std::mutex mutex;
    std::condition_variable cv;
    int counter;

public:
    void wait();
    void incAnyAvaible();
    void decAnyAvaible();
    void setCount(int n);
};