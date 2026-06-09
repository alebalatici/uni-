//
// Created by Alexandra on 6/9/2026.
//

#ifndef TASKS_SRV_TASKS_H
#define TASKS_SRV_TASKS_H

#include <utility>
#include <algorithm>
#include <cstring>

#include "../domain/validator.h"
#include "../repository/repo_tasks.h"
#include "../observer/observer.h"

using std::sort;
using std::copy_if;
class ServiceException : public std::exception
{
    private:
    string message;
    public:
    explicit ServiceException(string message) : message{std::move(message)} {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class ServiceTasks : public Observable {
    private:
    Repo& repo;
    Validator& val;
    public:
    ServiceTasks() = delete;
    virtual ~ServiceTasks() = default;
    ServiceTasks(const ServiceTasks& ot) = delete;
    ServiceTasks(Repo& _repo, Validator& _val) : repo{_repo}, val {_val} {}
    void addTask(int id, const string& descriere, const vector<string>& programatori, const string& stare)
    {
        try
        {
            Task task{id, descriere, programatori, stare};
            val.validate(task);
            repo.addTask(task);
            notify();
        }
        catch (std::exception& e)
        {
            throw ServiceException{e.what()};
        }
    }

    Task& findTask(int id)
    {
        try
        {
            return repo.findTask(id);
        }
        catch (std::exception& e)
        {
            throw ServiceException{e.what()};
        }
    }

    [[nodiscard]] const vector<Task>& getTasks() const
    {
        return repo.getTasks();
    }

    static vector<Task> sortByStare(const vector<Task>& tasks)
    {
        vector<Task> sorted_tasks = tasks;
        std::ranges::sort(sorted_tasks, [](const Task& a, const Task& b)
        {
            return a.getStare() < b.getStare();
        });
        return sorted_tasks;
    }

    static vector<string> getVectorProgrammers(string str)
    {
        vector<string> programmers;
        stringstream linestream{str};
        string current_item;
        while (getline(linestream, current_item, ';'))
        {
            programmers.push_back(current_item);
        }
        return programmers;
    }

    static vector<Task> filterByString(string str, const vector<Task>& tasks)
    {
        vector<Task> filtered_tasks;
        std::ranges::copy_if(tasks, back_inserter(filtered_tasks),
        [str](const Task& t)
        {
            for (const auto& p : t.getProgramatori())
            {
                if (strstr(p.c_str(), str.c_str()) != nullptr) return true;
            }
            return false;
        });
        return filtered_tasks;
    }

    static vector<Task> filterByStare(const string& stare, const vector<Task>& tasks)
    {
        vector<Task> filtered_tasks;
        std::ranges::copy_if(tasks, back_inserter(filtered_tasks),
        [stare](const Task& t)
        {
            return stare == t.getStare();
        });
        return filtered_tasks;
    }

    void changeStare(int id, const string& stare)
    {
        try
        {
            Task& task = repo.findTask(id);
            val.validate(Task{task.getId(), task.getDescriere(), task.getProgramatori(), stare});
            repo.changeStare(id, stare);
            notify();
        }
        catch (std::exception& e)
        {
            throw ServiceException{e.what()};
        }
    }

};

#endif //TASKS_SRV_TASKS_H
