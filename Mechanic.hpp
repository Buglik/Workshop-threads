#pragma once
#include <mutex>
#include <atomic>
#include "Horn.hpp"

class Mechanic
{
private:
    int id;
    std::mutex mutex;
    std::atomic<bool> isBusy;
    // std::atomic<SpaceState> state;

public:
    Mechanic(int id);
    // void finished();
    // void getWorkers(int n);

    std::mutex &getMutex()
    {
        return mutex;
    }

    int getId()
    {
        return id;
    }

    bool getIsBusy()
    {
        return isBusy;
    }

    void setIsBusy(bool x)
    {
        isBusy = x;
    }
};