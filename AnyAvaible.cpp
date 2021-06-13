#include "AnyAvaible.hpp"
#include <iostream>

void AnyAvaible::wait()
{
    std::unique_lock<std::mutex> lock(mutex);
    // std::cout << counter << std::endl;
    while (counter == 0)
    {
        cv.wait(lock);
    }
}

void AnyAvaible::incAnyAvaible()
{
    std::unique_lock<std::mutex> lock(mutex);
    counter++;
    cv.notify_all();
}

void AnyAvaible::decAnyAvaible()
{
    std::unique_lock<std::mutex> lock(mutex);
    counter--;
    cv.notify_all();
}