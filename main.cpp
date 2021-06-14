#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <condition_variable>
#include "Workshop.hpp"
#include "Car.hpp"
#include "Manager.hpp"
#include "UI.hpp"

void start()
{
    Workshop workshop(5);
    Manager manager(workshop);

    std::vector<Car *> carV;

    for (size_t i = 0; i < 25; i++)
    {
        std::string name = "Car ";
        name += std::to_string(i);
        carV.push_back(new Car(i, name, workshop, manager));
    }

    UI ui(carV, workshop);

    while (workshop.getIsOpen())
    {
    };
}

int main()
{
    start();
    return 0;
}