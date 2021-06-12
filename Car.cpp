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

Car::Car(int id, std::string n, Workshop &ws) : id(id), name(n), workshop(ws), progress(0.0f), spaceId(-1), state(State::waiting), thread(&Car::run, this)
{
    std::cout << "ZROBILEM Cara!" << std::endl;
}

Car::~Car()
{
    print("Umiera :(");
    thread.join();
}

void Car::run()
{

    std::cout << "Car " << id << "sobie zyje" << std::endl;

    do
    { // try to get space
        for (auto &space : workshop.getSpaces())
        {
            if (space->getMutex().try_lock())
            {
                workshop.getSetup().hornSound.letEveryoneKnowIn();
                spaceId = space->getId();
                print("zablokowalem" + std::to_string(spaceId));
                state = State::inPosition;
                break;
            }
        }
        // if no space
        //wait for horn
        if (spaceId == -1)
        {
            print("Czekam na horna");
            workshop.getSetup().hornSound.wait();
            print("uslyszalem horna");
        }
    } while (state == State::waiting);
    if (state == State::inPosition)
    {
        // try to get one employee
        // random type of repair
        // if hard one
        //free the one employee
        //wait for parts
        //get two employees
        //repair
        // else repair (employee got earlier)

        wait();
        print("puszczam stanowisko" + std::to_string(spaceId));
        workshop.getSpaces().at(spaceId)->getMutex().unlock();
        state = State::waiting;
        spaceId = -1;
        print("uzywam horna");
        // go out with horn
        workshop.getSetup().hornSound.letEveryoneKnowOut();
    }

    //and die
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