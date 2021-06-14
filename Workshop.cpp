#include "Workshop.hpp"

Workshop::Workshop(int n) : amount(n)
{
    prepareSpaces();
    prepareMechanics();
}

void Workshop::prepareSpaces()
{
    for (size_t i = 0; i < amount; i++)
    {
        spaceV.push_back(new Space(i));
    }
}

void Workshop::prepareMechanics()
{
    for (size_t i = 0; i < amount - 1; i++)
    {
        mechanicV.push_back(new Mechanic(i));
    }
}

std::vector<int> Workshop::assignMechanics(int n)
{
    std::vector<int> mechanicsIds;
    if (n == 1)
    {
        while (!mechanicsIds.size())
        {
            for (auto &worker : mechanicV)
            {
                if (worker->getMutex().try_lock())
                {
                    worker->setIsBusy(true);
                    mechanicsIds.push_back(worker->getId());
                    break;
                }
            }
        }
    }
    return mechanicsIds;
}

std::vector<Space *> &Workshop::getSpaces()
{
    return spaceV;
}

std::vector<Mechanic *> &Workshop::getMechanics()
{
    return mechanicV;
}

WorkshopSetup &Workshop::getSetup()
{
    return setup;
}

bool Workshop::getIsOpen() const
{
    return isOpen;
}

void Workshop::open()
{
    isOpen = true;
    setup.hornSound.letEveryoneKnowOut();
}

void Workshop::close()
{
    isOpen = false;
}