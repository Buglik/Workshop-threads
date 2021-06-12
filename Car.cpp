#include "Car.hpp"
#include <array>
#include <chrono>
#include <iomanip>
#include <thread>
#include <atomic>
#include <iostream>
#include <iomanip>
#include <string>
#include <condition_variable>
#include <mutex>
#include "Random.hpp"

Car::Car(int id, std::string n, WorkshopSetup &s, float speedRatio) : id(id), name(n), setup(s), speedRatio(speedRatio), progress(0.0f), state(State::waiting), thread(&Car::run, this)
{
}

Car::~Car()
{
    thread.join();
}

void Car::run()
{
    // try to get space
    // if no space
    //wait for horn
    // try to get one employee
    // random type of repair
    // if hard one
    //free the one employee
    //wait for parts
    //get two employees
    //repair
    // else repair (employee got earlier)
    // go out with horn and die
}

void Car::wait()
{
    int delayCounter = Random().randomInt(100, 150);
    // delayCounter *= speedRatio;

    for (int i = 0; i <= delayCounter; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        progress = static_cast<float>(i) / static_cast<float>(delayCounter);
    }
    progress = 0.0f;
}

void Car::print(std::string text)
{
    // std::ostringstream s1;
    std::cout << name << text << std::endl;
}

State Car::getState() const
{
    return state;
}

std::string Car::getStateString() const
{
    switch (state)
    {
    case State::waiting:
        return "waiting";
    case State::inPosition:
        return "inPosition";
    case State::waitingForParts:
        return "waitingForParts";
    case State::waitingForMechanics:
        return "waitingForMechanics";
    case State::repairing:
        return "repairing";
    case State::ready:
        return "ready";
    default:
        return "no state";
    }
}

std::string Car::getName() const
{
    return name;
}

float Car::getProgress() const
{
    return progress;
}