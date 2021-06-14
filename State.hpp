#pragma once

enum class State
{
    waiting,
    inPosition,
    diagnosing,
    waitingForParts,
    waitingForMechanics,
    repairing,
    ready
};