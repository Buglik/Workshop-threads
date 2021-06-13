#pragma once
#include <atomic>
#include "Horn.hpp"
#include "Priority.hpp"
#include "AnyAvaible.hpp"

class WorkshopSetup
{
private:
    std::atomic<bool> status{false};

public:
    Horn hornSound;
    Priority priority;
    AnyAvaible anyAvaible;
    bool getStatus();
    void setStatus(bool newStatus);
};