#pragma once
#include <mutex>
#include <condition_variable>

class Horn
{
private:
    std::mutex mutex;
    std::condition_variable cv;
    bool go = false;

public:
    void wait();
    void letEveryoneKnowOut();
    void letEveryoneKnowIn();
};