#include "Manager.hpp"
#include "iostream"

Manager::Manager(Workshop &workshop) : workshop(workshop)
{
    std::cout << "ZROBILEM Menagera!" << std::endl;
}

Mechanic *Manager::askForEmployee()
{
    while (true)
    {
        for (auto &worker : workshop.getMechanics())
        {
            if (worker->getMutex().try_lock())
            {
                worker->setIsBusy(true);
                std::cout << "Manager przypisuje mechanika" << std::to_string(worker->getId()) << std::endl;

                return worker;
                // mechanicsIds.push_back(worker->getId());
                // break;
            }
        }
    }
}

std::vector<Mechanic *> Manager::askForTwoEmployees()
{
    std::vector<Mechanic *> twoWorkers;
    while (twoWorkers.size() < 2)
    {
        for (auto &worker : workshop.getMechanics())
        {
            if (worker->getMutex().try_lock())
            {
                worker->setIsBusy(true);
                twoWorkers.push_back(worker);
            }
            if (twoWorkers.size() == 2)
                break;
        }
    }
    return twoWorkers;
}
