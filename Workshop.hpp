#pragma once
#include "WorkshopSetup.hpp"
#include "Space.hpp"
#include "Mechanic.hpp"
#include <vector>

class Workshop
{
public:
    Workshop(int n);

private:
    std::atomic<bool> isOpen;
    WorkshopSetup setup;
    int amount;

    std::vector<Space *> spaceV;
    std::vector<Mechanic *> mechanicV;

public:
    void prepareSpaces();
    void prepareMechanics();
    std::vector<Space *> &getSpaces();
    std::vector<Mechanic *> &getMechanics();
    WorkshopSetup &getSetup();
    bool getIsOpen() const;
    void open();
    void close();
};