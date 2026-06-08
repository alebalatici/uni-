//
// Created by Alexandra on 6/7/2026.
//

#ifndef MELODII_OBSERVER_H
#define MELODII_OBSERVER_H

#include <vector>
#include <algorithm>

using std::vector;
using std::remove;
class Observer {
    public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Observable
{
    private:
    vector<Observer*> observers;

    public:
    void add_observer(Observer* observer)
    {
        observers.push_back(observer);
    }

    void remove_observer(Observer* observer)
    {
        observers.erase(
            remove(observers.begin(), observers.end(), observer), observers.end()
        );
    }

    void notify()
    {
        for (auto& observer : observers)
        {
            observer->update();
        }
    }
};

#endif //MELODII_OBSERVER_H
