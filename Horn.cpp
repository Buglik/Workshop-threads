#include "Horn.hpp"

void Horn::wait()
{
    std::unique_lock<std::mutex> lock(mutex);
    while (!go)
    {
        cv.wait(lock);
    }
    go = true;
}

void Horn::letEveryoneKnow()
{
    std::unique_lock<std::mutex> lock(mutex);
    go = true;
    cv.notify_all();
}