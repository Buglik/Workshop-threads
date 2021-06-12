#include "Workshop.hpp"

Workshop::Workshop(int n) : amount(n)
{
    prepareSpaces();
    // prepareMechanics();  //TODO
}

void Workshop::prepareSpaces()
{
    for (size_t i = 0; i < amount; i++)
    {
        spaceV.push_back(new Space(i));
    }
}

std::vector<Space *> &Workshop::getSpaces()
{
    return spaceV;
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
}

void Workshop::close()
{
    isOpen = false;
}