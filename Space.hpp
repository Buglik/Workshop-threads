#pragma once
#include <mutex>
#include <vector>

class Space
{
private:
    int id;
    std::mutex mutex;
    int repairType = -1;
    int carId = -1;
    std::vector<int> mechanics;

public:
    Space(int id);
    void finished();

    std::mutex &getMutex()
    {
        return mutex;
    }

    int getId()
    {
        return id;
    }

    int getMechanicAmount()
    {
        return mechanics.size();
    }

    int getCarId()
    {
        return carId;
    }

    void setRepairType(int n)
    {
        repairType = n;
    }

    void setCarId(int n)
    {
        carId = n;
    }

    void addMechanic(int n)
    {
        mechanics.push_back(n);
    }

    void removeMechanics()
    {
        mechanics.clear();
    }

    void resetSpace()
    {
        carId = -1;
        repairType = -1;
        removeMechanics();
    }
};