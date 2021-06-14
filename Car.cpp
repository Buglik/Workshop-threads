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
    // std::cout << "ZROBILEM Cara!" << std::endl;
}

Car::~Car()
{
    print("Umiera :(");
    thread.join();
}

void Car::run()
{

    workshop.getSetup().hornSound.wait();
    // std::cout << "Car " << id << "sobie zyje" << std::endl;
    wait();
    getIntoWorkshop();
    repairProcess();
    leaveWorkshop();

    // try to get one employee
    // random type of repair
    // if hard one
    //free the one employee
    //wait for parts
    //get two employees
    //repair
    // else repair (employee got earlier)

    //and die
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
    print("FINITO");
    state = State::ready;
    print("puszczam stanowisko " + std::to_string(spaceId));
    workshop.getSpaces().at(spaceId)->resetSpace();
    workshop.getSpaces().at(spaceId)->getMutex().unlock();
    spaceId = -1;
    // print("uzywam horna");
    // go out with horn
    workshop.getSetup().hornSound.letEveryoneKnowOut();
}

void Car::repairProcess()
{
    // try to get one employee
    //check cv if any free
    print("checking if there are any mechanics ...");
    workshop.getSetup().anyAvaible.wait();
    print(std::to_string(workshop.getSetup().anyAvaible.getCounter()));
    print("there is a mechanic");
    //check cv if no priority
    print("checking priority ...");
    workshop.getSetup().priority.wait();
    print("... there is no priority");

    manager.getMutex().lock();
    Mechanic *mechanicForCheckup = manager.askForEmployee();
    manager.getMutex().unlock();
    workshop.getSpaces().at(spaceId)->addMechanic(mechanicForCheckup->getId());
    // currentMechanicsIds = workshop.assignMechanics(1);

    print("biore pracownika" + std::to_string(mechanicForCheckup->getId()));
    // print(std::to_string(workshop.getSetup().anyAvaible.getCounter()));
    // random type of repair
    int repairType = Random().randomInt(0, 100) % 2;
    // int repairType = 2;
    workshop.getSpaces().at(spaceId)->setRepairType(repairType);
    if (repairType == 0) //hard one
    {
        // if hard one
        state = State::diagnosing;

        wait();
        print("hard one");
        //free the one employee
        mechanicForCheckup->getMutex().unlock();
        workshop.getSpaces().at(spaceId)->removeMechanics();
        // print(std::to_string(workshop.getSetup().anyAvaible.getCounter()));
        workshop.getSetup().anyAvaible.incAnyAvaible();
        // std::cout << "Mechanik " << mechanicForCheckup->getId() << " zamowil czesci" << std::endl;
        print(std::to_string(workshop.getSetup().anyAvaible.getCounter()));
        //wait for parts
        state = State::waitingForParts;
        wait();

        print("oczekuje na naprawe (czesci juz sa)");
        state = State::waitingForMechanics;
        //let know cv that there is priority
        workshop.getSetup().priority.incPriority();
        //get two employees
        //check if if any free
        print(std::to_string(workshop.getSetup().anyAvaible.getCounter()));
        workshop.getSetup().anyAvaible.wait();
        manager.getMutex().lock();
        std::vector<Mechanic *> mechanicsForHardJob = manager.askForTwoEmployees(spaceId);
        print("zarezerwowal" + std::to_string(mechanicsForHardJob.at(0)->getId()) + " oraz " + std::to_string(mechanicsForHardJob.at(1)->getId()));
        // std::cout << std::to_string(mechanicsForHardJob.size()) << std::endl;
        manager.getMutex().unlock();
        state = State::repairing;
        print("naprawia sie");
        wait();
        print("juz sie naprawil");
        for (auto &m : mechanicsForHardJob)
        {
            m->setIsBusy(false);
            m->getMutex().unlock();
            workshop.getSetup().anyAvaible.incAnyAvaible();
            print("zwolnil" + std::to_string(m->getId()));
        }
        workshop.getSpaces().at(spaceId)->removeMechanics();
    }
    else
    {
        state = State::diagnosing;
        wait();
        // else repair (employee got earlier)
        state = State::repairing;
        print("naprawiam sie");
        wait();
        print("juz sie naprawilem");
        // workshop.getMechanics().at(currentMechanicsIds.at(0))->getMutex().unlock();
        // workshop.getMechanics().at(currentMechanicsIds.at(0))->setIsBusy(false);
        mechanicForCheckup->setIsBusy(false);
        // std::cout << "Mechanik " << mechanicForCheckup->getId() << " skonczyl robote" << std::endl;
        mechanicForCheckup->getMutex().unlock();
        workshop.getSetup().anyAvaible.incAnyAvaible();
        workshop.getSpaces().at(spaceId)->removeMechanics();
    }
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
        return "Wait for Mechanic";
    case State::repairing:
        return "Reparing ...";
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