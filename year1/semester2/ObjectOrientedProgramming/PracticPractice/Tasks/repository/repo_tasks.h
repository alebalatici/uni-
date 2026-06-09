//
// Created by Alexandra on 6/8/2026.
//

#ifndef TASKS_REPO_TASKS_H
#define TASKS_REPO_TASKS_H

#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "../domain/task.h"

using std::find_if;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::stringstream;
class RepoException : public std::exception
{
    private:
    string message;
    public:
    explicit RepoException(string message) : message(std::move(message)) {}
    [[nodiscard]] const char *what() const noexcept override { return message.c_str(); }
};

class Repo
{
    public:
    virtual ~Repo() = default;
    virtual void addTask(const Task& task) = 0;
    virtual Task& findTask(int id) = 0;
    virtual void changeStare(int id, const string& stare) = 0;
    [[nodiscard]] virtual const vector<Task>& getTasks() const = 0;
};

class RepoTasks : public Repo {
    protected:
    vector<Task> tasks;
    public:
    RepoTasks() = default;

    void addTask(const Task& task) override
    {
        auto it = find_if(tasks.begin(), tasks.end(),
            [task](const Task& t)
            {
                return t.getId()  == task.getId();
            });

        if (it != tasks.end())
        {
            throw RepoException("Task already added");
        }
        tasks.push_back(task);
    }

    Task& findTask(int id) override
    {
        auto it = find_if(tasks.begin(), tasks.end(), [id](const Task& t)
        {
            return t.getId() == id;
        });
        if (it == tasks.end())
        {
            throw RepoException("Task not found");
        }
        return *it;
    }

    void changeStare(int id, const string& stare) override
    {
        Task& task = findTask(id);
        task.setStare(stare);
    }

    [[nodiscard]] const vector<Task>& getTasks() const override
    {
        return tasks;
    }
};

class RepoTasksFile : public RepoTasks
{
private:
    string filename;
    void load_from_file()
    {
        ifstream fin{filename};
        if (!fin.is_open())
        {
            throw RepoException("File not found");
        }
        string line;
        while (getline(fin, line))
        {
            while (line.back() == '\r')
            {
                line.pop_back();
            }

            int id;
            string descriere;
            string programatori_string;
            string stare;

            stringstream linestream{line};
            string current_component;
            int item_no = 0;
            try {
                while (getline(linestream, current_component, ','))
                {
                    switch (item_no)
                    {
                        case 0: id = std::stoi(current_component); break;
                        case 1: descriere = current_component; break;
                        case 2: programatori_string = current_component; break;
                        case 3: stare = current_component; break;
                        default: break;
                        }
                        item_no++;
                    }
                    if (item_no != 4)
                    {
                        throw RepoException("Formatting error on line " + line);
                    }

                    vector<string> programatori;
                    stringstream linestream1{programatori_string};
                    string current_line;
                    while (getline(linestream1 , current_line, ';'))
                    {
                        programatori.push_back(current_line);
                    }
                    Task task{id, descriere, programatori, stare};
                    RepoTasks::addTask(task);
                }
            catch(std::exception& e)
            {
                throw RepoException(e.what());
            }
        }
    }

    void save_to_file()
    {
        ofstream fout{filename};
        if (!fout.is_open())
        {
            throw RepoException("File not found");
        }

        for (const auto& t : RepoTasks::getTasks())
        {
            string programatori_string;
            for (const auto& p : t.getProgramatori())
            {
                programatori_string += p + ";";
            }
            programatori_string.pop_back();
            fout << t.getId() << ',' << t.getDescriere() << ',' << programatori_string << ',' << t.getStare() << '\n';
        }
    }
    public:
    RepoTasksFile(string _filename) : filename(std::move(_filename))
    {
        load_from_file();
    }

    void addTask(const Task& task) override
    {
        RepoTasks::addTask(task);
        save_to_file();
    }

    Task& findTask(int id) override
    {
        return RepoTasks::findTask(id);
    }

    void changeStare(int id, const string& stare) override
    {
        RepoTasks::changeStare(id, stare);
        save_to_file();
    }

    [[nodiscard]] const vector<Task>& getTasks() const override
    {
        return RepoTasks::getTasks();
    }
};

#endif //TASKS_REPO_TASKS_H