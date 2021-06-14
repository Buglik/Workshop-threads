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
}

void UI::refreshView()
{
    clear();
    while (workshop.getIsOpen())
    {
        clear();
        refreshSpaces();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void UI::refreshSpaces()
{
    for (int i = 0; i < workshop.getSpaces().size(); i++)
    {
        int sizeX = 17;
        int sizeY = 10;
        auto &space = workshop.getSpaces().at(i);
        int x = space->getCarId();
        WINDOW *subwindow = subwin(stdscr, sizeY, sizeX, 0, 5 + ((sizeX + 2) * i));
        if (x < 0)
        {
            wattron(subwindow, COLOR_PAIR(2));
        }
        box(subwindow, 0, 0);
        const std::string spaceName = "STANOWISKO " + std::to_string(i);
        mvwprintw(subwindow, 0, 1, spaceName.c_str());
        int m = space->getMechanicAmount();
        for (int j = 0; j < m; j++)
        {
            mvwprintw(subwindow, 0, sizeX - 2 - j, "I");
        }

        if (x < 0)
        {
            wattroff(subwindow, COLOR_PAIR(2));
        }
        if (x >= 0)
        {

            mvwprintw(subwindow, sizeY - 3, 1, cars.at(x)->getName().c_str());
            mvwprintw(subwindow, sizeY - 2, 1, cars.at(x)->getStateString().c_str());

            int barLength = sizeX - 2;
            float progress = cars.at(x)->getProgress();
            std::string finString;
            std::string progressInPercent = std::to_string((int)std::round(progress * 100));
            int lpad = std::round(progress * barLength);
            int rpad = barLength - lpad;

            for (int k = 0; k < lpad; k++)
            {
                finString = finString + "#";
            }
            for (int k = 0; k < rpad; k++)
            {
                finString = finString + " ";
            }

            mvwprintw(subwindow, sizeY - 1, 1, finString.c_str());
        }
        wrefresh(subwindow);
    }
    // refresh();
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