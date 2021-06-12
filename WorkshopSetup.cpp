#include "WorkshopSetup.hpp"

bool WorkshopSetup::getStatus()
{
    return status;
}

void WorkshopSetup::setStatus(bool newStatus)
{
    status.exchange(newStatus);
}