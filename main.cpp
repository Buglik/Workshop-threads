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
// #include "UI.hpp"

void start()
{
    Workshop workshop(2);
    Manager manager(workshop);

    std::vector<Car *> carV;

    //for testing purposes
    for (size_t i = 0; i < 5; i++)
    {
        std::string name = "Car ";
        name += std::to_string(i);
        carV.push_back(new Car(i, name, workshop, manager));
    }

    // UI ui(table.getPhilosophers(), table, table.getForks());
    workshop.open();
    while (workshop.getIsOpen())
    {
        // generating new cars
    };
}

int main()
{
    start();
    return 0;
}