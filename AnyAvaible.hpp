#pragma once
#include <mutex>
#include <condition_variable>

class AnyAvaible
{
private:
    std::mutex mutex;
    std::condition_variable cv;
    int counter = 4; //TODO THATS AMOUNT OF MECHANICS

public:
    void wait();
    void incAnyAvaible();
    void decAnyAvaible();
    int getCounter()
    {
        return counter;
    };
};