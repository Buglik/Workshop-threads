#pragma once
#include <thread>
#include <iostream>
#include <atomic>
#include <string>
#include "State.hpp"
#include "Workshop.hpp"
#include "Manager.hpp"

class Car
{
private:
    int id;
    std::string name;
    Workshop &workshop;
    Manager &manager;
    std::thread thread;
    std::atomic<float> progress;
    std::atomic<State> state;
    std::atomic<int> spaceId;
    std::vector<int> currentMechanicsIds;

public:
    Car(int id, std::string n, Workshop &ws, Manager &m);
    ~Car();

    void run();
    void getIntoWorkshop();
    void leaveWorkshop();
    void repairProcess();
    void print(std::string text);
    void wait();
    float getProgress() const;
    State getState() const;
    std::string getName() const;
    std::string getStateString() const;
};