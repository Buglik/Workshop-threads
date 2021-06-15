#include "AnyAvaible.hpp"
#include <iostream>

void AnyAvaible::wait()
{
    std::unique_lock<std::mutex> lock(mutex);
    while (counter == 0)
    {
        cv.wait(lock);
    }
}

void AnyAvaible::incAnyAvaible()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        counter++;
    }
    cv.notify_all();
}

void AnyAvaible::decAnyAvaible()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        counter--;
    }
    cv.notify_all();
}

void AnyAvaible::setCount(int n)
{
    std::lock_guard<std::mutex> lock(mutex);
    counter = n;
}