#pragma once

enum class State
{
    waiting,
    inPosition,
    waitingForParts,
    waitingForMechanics,
    repairing,
    ready
};