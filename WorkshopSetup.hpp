#pragma once
#include <atomic>
#include "Horn.hpp"
#include "Priority.hpp"

class WorkshopSetup
{
private:
    std::atomic<bool> status{false};

public:
    Horn hornSound;
    Priority priority;
    bool getStatus();
    void setStatus(bool newStatus);
};