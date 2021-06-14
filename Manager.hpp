#pragma once
#include <mutex>
#include "Workshop.hpp"

class Manager
{
private:
    std::mutex mutex;
    Workshop &workshop;

public:
    Manager(Workshop &workshop);

    std::mutex &getMutex()
    {
        return mutex;
    }

    Mechanic *askForEmployee();
    std::vector<Mechanic *> askForTwoEmployees(int spaceId);
};