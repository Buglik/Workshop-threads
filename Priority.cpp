#include "Priority.hpp"

void Priority::wait()
{
    std::unique_lock<std::mutex> lock(mutex);
    while (counter)
    {
        cv.wait(lock);
    }
}

void Priority::incPriority()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        counter++;
    }
    cv.notify_all();
}

void Priority::decPriority()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        counter--;
    }
    cv.notify_all();
}