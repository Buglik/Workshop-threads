#pragma once
#include "WorkshopSetup.hpp"
#include "Space.hpp"
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

public:
    void prepareSpaces();
    std::vector<Space *> &getSpaces();
    WorkshopSetup &getSetup();
    bool getIsOpen() const;
    void open();
    void close();
};