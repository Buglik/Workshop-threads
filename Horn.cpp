#include "Horn.hpp"

void Horn::wait()
{
    std::unique_lock<std::mutex> lock(mutex);
    while (!go)
    {
        cv.wait(lock);
    }
}

void Horn::letEveryoneKnowOut()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        go = true;
    }
    cv.notify_all();
}

void Horn::letEveryoneKnowIn()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        go = false;
    }
    cv.notify_all();
}