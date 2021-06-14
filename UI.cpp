#include "UI.hpp"
#include <iostream>
#include <string.h>
#include <math.h>
#include "State.hpp"

UI::UI(std::vector<Car *> &cars, Workshop &workshop) : cars(cars), workshop(workshop)
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();
    start_color();
    use_default_colors();
    init_pair(1, COLOR_MAGENTA, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_RED, -1);

    initializeWindow();
    refreshThread = std::make_unique<std::thread>(&UI::refreshView, this);
    keyboardThread = std::make_unique<std::thread>(&UI::endVisualisation, this);
}

UI::~UI()
{
    keyboardThread->join();
    refreshThread->join();
    destroyWindow(window);
    endwin();
}

void UI::destroyWindow(WINDOW *window)
{
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    delwin(window);
}

void UI::initializeWindow()
{
    window = newwin(LINES, COLS, 0, 0);
    const std::string centerHeader = "Workshop with threads";
    const std::string rightHeader = "Jakub Pawleniak 248897";

    mvprintw(0, COLS - centerHeader.length(), centerHeader.c_str());
    mvprintw(LINES - 1, COLS - rightHeader.length(), rightHeader.c_str());

    const std::string warningLine1 = "CLICK [ENTER] TO START";

    const int rowIndexw1 = LINES / 2;
    const int colIndexw1 = (COLS - warningLine1.length()) / 2 - 1;
    mvprintw(rowIndexw1, colIndexw1, warningLine1.c_str());

    while (getch() != 10)
        ;

    workshop.open();

    // UP OK
    // const int rowGap = LINES / (philosophers.size() * 2.5);
    // constexpr int colIndex = 0;

    // for (size_t i = 0; i < philosophers.size(); i++)
    // {
    //     const int rowIndex = rowGap * i + 3;
    //     OutputCoords coords = {{rowIndex, colIndex + 5}};
    //     outputCoordsPhil.push_back(coords);
    // }

    // for (size_t i = 0; i < forks.size(); i++)
    // {
    //     const int rowIndex = rowGap * i + 3;
    //     OutputCoords coords = {{rowIndex, colIndex + 140}};
    //     outputCoordsForks.push_back(coords);
    // }

    // for (size_t i = 0; i < philosophers.size(); i++)
    // {
    //     const int rowIndex = rowGap * i + 3;
    //     OutputCoords coords = {{rowIndex, colIndex + 85}};
    //     outputCoordsHungry.push_back(coords);
    // }

    wrefresh(window);
}

void UI::refreshView()
{
    clear();
    while (workshop.getIsOpen())
    {
        clear();
        // refreshStatuses();
        refreshSpaces();
        wrefresh(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void UI::refreshSpaces()
{
    for (int i = 0; i < workshop.getSpaces().size(); i++)
    {
        WINDOW *subwindow = subwin(stdscr, 10, 15, 0, 5 + (17 * i));
        box(subwindow, 0, 0);
        const std::string spaceName = "STANOWISKO " + std::to_string(i);
        mvwprintw(subwindow, 0, 1, spaceName.c_str());
        spaceWindows.push_back(subwindow);
        mvwprintw(subwindow, 2, 1, cars.at(0)->getStateString().c_str());
        wrefresh(subwindow);
    }

    // refresh();
}

void UI::refreshStatuses()
{
    // attron(COLOR_PAIR(4));
    // start_color();
    // init_color(COLOR_RED, 500, 0, 0);
    // init_color(COLOR_MAGENTA, 400, 600, 900);
    // init_pair(1, COLOR_RED, -1);
    // init_pair(2, COLOR_GREEN, -1);
    // init_pair(3, COLOR_MAGENTA, -1);
    // init_pair(4, COLOR_WHITE, -1);
    // std::string stateHeader = "PHILOSOPHER STATUS:";
    // std::string state1Header = "RESOURCE STATUS:";
    // std::string stateProgressHeader = "PROGRESS:";
    // std::string starvationHeader = "HUNGER TO THE ENTIRE HUNGER:";
    // std::string starvation1Header = "HUNGRY TO THINKING AND EATING:";
    // mvwprintw(stdscr, 1, 5, stateHeader.c_str());
    // mvwprintw(stdscr, 1, 140, state1Header.c_str());
    // mvwprintw(stdscr, 30, 73, starvation1Header.c_str());
    // mvwprintw(stdscr, 1, 42, stateProgressHeader.c_str());
    // mvwprintw(stdscr, 1, 80, starvationHeader.c_str());
    // for (size_t i = 0; i < philosophers.size(); i++)
    // {

    //     auto &philosopher = philosophers.at(i);
    //     switch (philosopher->getState())
    //     {
    //     case State::hungry:
    //         hungry[i]++;
    //         hungryAll++;
    //         //attron(COLOR_PAIR(1));
    //         break;
    //     case State::eating:
    //         notHungryAll++;
    //         //attron(COLOR_PAIR(2));
    //         break;
    //     case State::thinking:
    //         notHungryAll++;
    //         //attron(COLOR_PAIR(3));
    //         break;
    //     }
    //     attron(COLOR_PAIR(4));
    //     std::pair<int, int> coords = outputCoordsPhil.at(i).coords;
    //     refreshState(stdscr, coords.first, coords.second, philosopher->getProgress(), philosopher->getName(), philosopher->getStateString());
    // }

    // for (unsigned i = 0; i < forks.size(); i++)
    // {
    //     auto &fork = forks.at(i);
    //     std::pair<int, int> coords = outputCoordsForks.at(i).coords;
    //     int owner = fork->getOwner();
    //     std::string ownerName = philosophers.at(owner)->getName();
    //     refreshOwner(stdscr, coords.first, coords.second, i, ownerName);
    // }
    // refreshHungryBar(stdscr);
    // refreshHungryBars(stdscr);
}

void UI::refreshHungryBar(WINDOW *win)
{
    // std::string finString;
    // float result;
    // int barLength = 30;
    // if (notHungryAll != 0 && hungryAll != 0)
    //     result = static_cast<float>(hungryAll) / static_cast<float>(notHungryAll);
    // else
    //     result = 0;

    // int lpad = std::round(result * barLength);
    // int rpad = barLength - lpad;
    // result = result * 100;
    // std::string hungryInPercent = std::to_string((int)std::round(result));

    // finString = "\t" + hungryInPercent;
    // if (hungryInPercent.size() == 3)
    // {
    //     finString = finString + "% [";
    // }
    // else if (hungryInPercent.size() == 2)
    // {
    //     finString = finString + " % [";
    // }
    // else
    // {
    //     finString = finString + "  % [";
    // }

    // for (int i = 0; i < lpad; i++)
    // {
    //     finString = finString + "#";
    // }
    // for (int i = 0; i < rpad; i++)
    // {
    //     finString = finString + " ";
    // }
    // finString = finString + "]";
    // ;
    // if (result > 30)
    //     attron(COLOR_PAIR(1));
    // else
    //     attron(COLOR_PAIR(2));
    // std::scoped_lock lock(changeMutex);
    // mvwprintw(win, 31, 75, finString.c_str());
    // refresh();
}
void UI::refreshState(WINDOW *win, int y, int x, float progress, std::string name, std::string status)
{
    // int barLength = 30;
    // std::string finString;
    // std::string progressInPercent = std::to_string((int)std::round(progress * 100));
    // int lpad = std::round(progress * barLength);
    // int rpad = barLength - lpad;
    // if (status.compare("hungry") != 0)
    // {
    //     finString = name + " is " + status + "\t\t" + progressInPercent;
    //     if (progressInPercent.size() == 2)
    //     {
    //         finString = finString + "% [";
    //     }
    //     else
    //     {
    //         finString = finString + " % [";
    //     }
    //     for (int i = 0; i < lpad; i++)
    //     {
    //         finString = finString + "#";
    //     }
    //     for (int i = 0; i < rpad; i++)
    //     {
    //         finString = finString + " ";
    //     }
    //     finString = finString + "]";
    // }
    // else
    // {
    //     finString = name + " is " + status;
    // }
    // std::scoped_lock lock(changeMutex);
    // mvwprintw(win, y, x, finString.c_str());
    // refresh();
}

void UI::refreshOwner(WINDOW *win, int y, int x, unsigned i, std::string ownerName)
{
    // init_color(COLOR_CYAN, 200, 700, 900);
    // init_pair(4, COLOR_WHITE, -1);
    // attron(COLOR_PAIR(4));
    // std::string finString = "Fork " + std::to_string(i) + " is owned by " + ownerName;
    // std::scoped_lock lock(changeMutex);
    // mvwprintw(win, y, x, finString.c_str());

    // refresh();
}

void UI::refreshHungryBars(WINDOW *win)
{
    // init_pair(1, COLOR_RED, -1);
    // init_pair(2, COLOR_GREEN, -1);
    // float result;
    // std::string finString = "";
    // for (unsigned i = 0; i < philosophers.size(); i++)
    // {
    //     int barLength = 30;
    //     if (hungry[i] != 0 && hungryAll != 0)
    //         result = static_cast<float>(hungry[i]) / static_cast<float>(hungryAll);
    //     else
    //         result = 0;

    //     int lpad = std::round(result * barLength);
    //     int rpad = barLength - lpad;
    //     result = result * 100;
    //     std::string hungryInPercent = std::to_string((int)std::round(result));

    //     finString = "\t" + hungryInPercent;
    //     if (hungryInPercent.size() == 3)
    //     {
    //         finString = finString + "% [";
    //     }
    //     else if (hungryInPercent.size() == 2)
    //     {
    //         finString = finString + " % [";
    //     }
    //     else
    //     {
    //         finString = finString + "  % [";
    //     }
    //     for (int i = 0; i < lpad; i++)
    //     {
    //         finString = finString + "#";
    //     }
    //     for (int i = 0; i < rpad; i++)
    //     {
    //         finString = finString + " ";
    //     }
    //     finString = finString + "]";

    //     std::pair<int, int> coords = outputCoordsHungry.at(i).coords;
    //     if (result > 100 / 7)
    //         attron(COLOR_PAIR(1));
    //     else
    //         attron(COLOR_PAIR(2));
    //     std::scoped_lock lock(changeMutex);
    //     mvwprintw(win, coords.first, coords.second, finString.c_str());
    //     refresh();
    // }
}
void UI::endVisualisation()
{
    while (workshop.getIsOpen())
    {
        int keyPressed = wgetch(window);

        switch (keyPressed)
        {
        case 27: // ESCAPE KEY
            workshop.close();
            break;
        }
    }
}