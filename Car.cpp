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

Car::Car(int id, std::string n, Workshop &ws, Manager &m) : id(id), name(n), workshop(ws), manager(m), progress(0.0f), spaceId(-1), state(State::waiting), thread(&Car::run, this)
{
}

Car::~Car()
{
    thread.join();
}

void Car::run()
{

    workshop.getSetup().hornSound.wait();
    wait();
    getIntoWorkshop();
    repairProcess();
    leaveWorkshop();
}

void Car::getIntoWorkshop()
{
    do
    { // try to get space

        for (auto &space : workshop.getSpaces())
        {
            if (space->getMutex().try_lock())
            {
                workshop.getSetup().hornSound.letEveryoneKnowIn();

                spaceId = space->getId();
                workshop.getSpaces().at(spaceId)->setCarId(id);
                print("zablokowalem stanowisko " + std::to_string(spaceId));
                state = State::inPosition;
                break;
            }
        }
        // if no space
        //wait for horn
        if (spaceId == -1)
        {
            // print("Czekam na horna");
            workshop.getSetup().hornSound.wait();
            // print("uslyszalem horna");
        }
    } while (state == State::waiting);
}

void Car::leaveWorkshop()
{

    manager.getMutex().lock();
    //getting payment
    manager.getMutex().unlock();

    print("puszczam stanowisko " + std::to_string(spaceId));
    workshop.getSpaces().at(spaceId)->resetSpace();
    workshop.getSpaces().at(spaceId)->getMutex().unlock();
    spaceId = -1;
    print("uzywam horna");
    // go out with horn
    workshop.getSetup().hornSound.letEveryoneKnowOut();
}

void Car::repairProcess()
{
    // try to get one employee
    //check cv if any free
    print("checking if there are any mechanics ...");
    workshop.getSetup().anyAvaible.wait();
    print("there is a mechanic");
    //check cv if no priority
    print("checking priority ...");
    workshop.getSetup().priority.wait();
    print("... there is no priority");

    manager.getMutex().lock();
    Mechanic *mechanicForCheckup = manager.askForEmployee();
    manager.getMutex().unlock();
    workshop.getSpaces().at(spaceId)->addMechanic(mechanicForCheckup->getId());

    print("biore pracownika" + std::to_string(mechanicForCheckup->getId()));
    // random type of repair
    int repairType = Random().randomInt(0, 100) % 2;
    // int repairType = 2;
    workshop.getSpaces().at(spaceId)->setRepairType(repairType);
    state = State::diagnosing;
    wait();
    if (repairType == 0) //hard one
    {
        // if hard one
        print("hard one");
        //free the one employee
        mechanicForCheckup->getMutex().unlock();
        workshop.getSpaces().at(spaceId)->removeMechanics();
        workshop.getSetup().anyAvaible.incAnyAvaible();
        //wait for parts
        state = State::waitingForParts;
        wait();
        print("oczekuje na naprawe (czesci juz sa)");
        state = State::waitingForMechanics;
        //let know cv that there is priority
        workshop.getSetup().priority.incPriority();
        //get two employees
        //check if if any free
        workshop.getSetup().anyAvaible.wait();
        manager.getMutex().lock();
        std::vector<Mechanic *> mechanicsForHardJob = manager.askForTwoEmployees(spaceId);
        print("zarezerwowal" + std::to_string(mechanicsForHardJob.at(0)->getId()) + " oraz " + std::to_string(mechanicsForHardJob.at(1)->getId()));
        manager.getMutex().unlock();
        state = State::repairing_H;
        print("naprawia sie");
        wait();
        print("juz sie naprawil");
        for (auto &m : mechanicsForHardJob)
        {
            // m->setIsBusy(false);
            m->getMutex().unlock();
            workshop.getSetup().anyAvaible.incAnyAvaible();
            print("zwolnil" + std::to_string(m->getId()));
        }
        workshop.getSpaces().at(spaceId)->removeMechanics();
    }
    else
    {
        // else repair (employee got earlier)
        state = State::repairing;
        print("naprawiam sie");
        wait();
        print("juz sie naprawilem");
        mechanicForCheckup->getMutex().unlock();
        workshop.getSetup().anyAvaible.incAnyAvaible();
        workshop.getSpaces().at(spaceId)->removeMechanics();
        state = State::ready;
    }
}

void Car::wait()
{
    int delayCounter;
    switch (state)
    {
    case State::diagnosing:
        delayCounter = Random().randomInt(0, 150);
        break;
    case State::waitingForParts:
        delayCounter = Random().randomInt(50, 300);
        break;
    case State::repairing:
        delayCounter = Random().randomInt(100, 150);
        break;
    case State::repairing_H:
        delayCounter = Random().randomInt(200, 400);
        break;
    default:
        delayCounter = 0;
    }

    for (int i = 0; i <= delayCounter; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        progress = static_cast<float>(i) / static_cast<float>(delayCounter);
    }
    progress = 0.0f;
}

void Car::print(std::string text)
{
    // std::cout << name << " " << text << std::endl;
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
        return "In workshop";
    case State::diagnosing:
        return "Diagnosing";
    case State::waitingForParts:
        return "Wait for Parts";
    case State::waitingForMechanics:
        return "Wait for Mech.";
    case State::repairing:
        return "Reparing ...";
    case State::repairing_H:
        return "Reparing(H) ...";
    case State::ready:
        return "Ready";
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