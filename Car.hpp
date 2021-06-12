#pragma once
#include <thread>
#include <iostream>
#include <atomic>
#include <string>
#include "State.hpp"
#include "WorkshopSetup.hpp"

class Car
{
private:
    int id;
    std::string name;
    WorkshopSetup &setup;

    std::thread thread;
    std::atomic<float> progress;
    std::atomic<State> state;
    float speedRatio;

public:
    Car(int id, std::string n, WorkshopSetup &s, float speedRatio);
    ~Car();

    void run();
    void getIntoWorkshop();
    void print(std::string text);
    void eat();
    void wait();
    void think();
    float getProgress() const;
    State getState() const;
    std::string getName() const;
    std::string getStateString() const;
};