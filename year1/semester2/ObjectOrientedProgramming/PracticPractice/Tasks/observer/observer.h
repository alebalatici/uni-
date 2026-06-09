//
// Created by Alexandra on 6/9/2026.
//

#ifndef TASKS_OBSERVER_H
#define TASKS_OBSERVER_H

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
    void addObserver(Observer* observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer)
    {
        observers.erase(
            std::ranges::remove(observers, observer).begin(), observers.end()
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



#endif //TASKS_OBSERVER_H
