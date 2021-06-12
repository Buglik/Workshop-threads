#pragma once
#include <atomic>
#include "Horn.hpp"

class WorkshopSetup
{
private:
    std::atomic<bool> status{false};

public:
    Horn hornSound;
    bool getStatus();
    void setStatus(bool newStatus);
};