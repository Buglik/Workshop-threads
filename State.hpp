#pragma once

enum class State
{
    waiting,
    inPosition,
    diagnosing,
    waitingForParts,
    waitingForMechanics,
    repairing,
    repairing_H,
    ready
};