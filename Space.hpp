#pragma once
#include <mutex>
#include <atomic>
#include "Horn.hpp"
// #include "SpaceState.hpp"

class Space
{
private:
    int id;
    std::mutex mutex;
    // std::atomic<SpaceState> state;

public:
    Space(int id);
    void finished();
    void getWorkers(int n);

    std::mutex &getMutex()
    {
        return mutex;
    }

    int getId()
    {
        return id;
    }

    // SpaceState getSpaceState()
    // {
    //     return state;
    // }
};