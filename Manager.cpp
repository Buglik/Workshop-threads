#include "Manager.hpp"
#include "iostream"

Manager::Manager(Workshop &workshop) : workshop(workshop)
{
}

Mechanic *Manager::askForEmployee()
{
    std::lock_guard<std::mutex> lock(mutex);
    while (true)
    {
        workshop.getSetup().anyAvaible.wait();
        for (auto &worker : workshop.getMechanics())
        {
            if (worker->getMutex().try_lock())
            {
                // worker->setIsBusy(true);
                workshop.getSetup().anyAvaible.decAnyAvaible();
                return worker;
            }
        }
    }
}

std::vector<Mechanic *> Manager::askForTwoEmployees(int spaceId)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<Mechanic *> twoWorkers;
    while (twoWorkers.size() < 2)
    {

        workshop.getSetup().anyAvaible.wait();
        for (auto &worker : workshop.getMechanics())
        {
            if (worker->getMutex().try_lock())
            {
                // worker->setIsBusy(true);
                workshop.getSetup().anyAvaible.decAnyAvaible();
                twoWorkers.push_back(worker);
                workshop.getSpaces().at(spaceId)->addMechanic(worker->getId());
            }
            if (twoWorkers.size() == 2)
            {
                workshop.getSetup().priority.decPriority();
                break;
            }
        }
    }
    return twoWorkers;
}
