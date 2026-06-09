//
// Created by Alexandra on 6/8/2026.
//

#ifndef PRODUSE_OBSERVER_H
#define PRODUSE_OBSERVER_H

#include <algorithm>
#include <vector>
using std::vector;
using std::remove;
class Observer
{
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
           std::ranges::remove(observers, observer).begin(), observers.end()
        );
    }

    void notify()
    {
        for (auto observer : observers)
        {
            observer->update();
        }
    }
};

#endif //PRODUSE_OBSERVER_H