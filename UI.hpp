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

    std::mutex changeMutex;
    bool ifStart = false;

private:
    // std::vector<OutputCoords> outputCoordsPhil;
    // std::vector<OutputCoords> outputCoordsForks;
    // std::vector<OutputCoords> outputCoordsHungry;

    std::unique_ptr<std::thread> refreshThread;
    std::unique_ptr<std::thread> keyboardThread;

    std::vector<WINDOW *> spaceWindows;

    WINDOW *window;

    long hungry[100] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    long hungryAll = 0;
    long notHungryAll = 0;
    void initializeWindow();
    void destroyWindow(WINDOW *window);
    void refreshView();
    void refreshStatuses();
    void refreshHungryBar(WINDOW *win);
    void refreshOwner(WINDOW *win, int y, int x, unsigned i, std::string ownerName);
    void refreshState(WINDOW *win, int y, int x, float progress, std::string name, std::string status);
    void refreshHungryBars(WINDOW *win);
    void refreshSpaces();
    void endVisualisation();
};