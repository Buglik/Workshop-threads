#include "Manager.hpp"
#include "iostream"

Manager::Manager(Workshop &workshop) : workshop(workshop)
{
    // std::cout << "ZROBILEM Menagera!" << std::endl;
}

Mechanic *Manager::askForEmployee()
{
    while (true)
    {
        workshop.getSetup().anyAvaible.wait();
        for (auto &worker : workshop.getMechanics())
        {
            if (worker->getMutex().try_lock())
            {
                worker->setIsBusy(true);
                workshop.getSetup().anyAvaible.decAnyAvaible();
                // std::cout << "Manager przypisuje mechanika" << std::to_string(worker->getId()) << std::endl;

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

        workshop.getSetup().anyAvaible.wait();
        for (auto &worker : workshop.getMechanics())
        {
            if (worker->getMutex().try_lock())
            {
                worker->setIsBusy(true);
                workshop.getSetup().anyAvaible.decAnyAvaible();
                twoWorkers.push_back(worker);
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
