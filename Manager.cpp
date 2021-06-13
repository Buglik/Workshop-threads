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

void Manager::freeEmployee(Mechanic *mechanic)
{
    std::cout << "Manager zwalnia mechanika" << std::to_string(mechanic->getId()) << std::endl;
    mechanic->setIsBusy(false);
    mechanic->getMutex().unlock();
}
