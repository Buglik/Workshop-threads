#pragma once
#include <ncurses.h>
#include <string>
#include <array>
#include <thread>
#include "Workshop.hpp"
#include "Car.hpp"
// #include "OutputCoords.hpp"
#include <vector>

class UI
{
public:
    UI(std::vector<Car *> &cars, Workshop &workshop);
    ~UI();

    std::vector<Car *> &cars;
    Workshop &workshop;

private:
    std::unique_ptr<std::thread> refreshThread;
    std::unique_ptr<std::thread> keyboardThread;

    WINDOW *window;

    void initializeWindow();
    void destroyWindow(WINDOW *window);
    void refreshView();
    void refreshSpaces();
    void endVisualisation();
};