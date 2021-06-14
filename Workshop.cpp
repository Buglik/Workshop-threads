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
    for (size_t i = 0; i < amount; i++)
    {
        mechanicV.push_back(new Mechanic(i));
    }
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