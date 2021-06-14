#pragma once
#include <mutex>

class Mechanic
{
private:
    int id;
    std::mutex mutex;

public:
    Mechanic(int id);

    std::mutex &getMutex()
    {
        return mutex;
    }

    int getId()
    {
        return id;
    }
};