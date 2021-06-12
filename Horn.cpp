#include "Horn.hpp"

void Horn::wait()
{
    std::unique_lock<std::mutex> lock(mutex);
    while (!go)
    {
        cv.wait(lock);
    }
    // go = false;
}

void Horn::letEveryoneKnowOut()
{
    std::unique_lock<std::mutex> lock(mutex);
    go = true;
    cv.notify_all();
}

void Horn::letEveryoneKnowIn()
{
    std::unique_lock<std::mutex> lock(mutex);
    go = false;
    cv.notify_all();
}