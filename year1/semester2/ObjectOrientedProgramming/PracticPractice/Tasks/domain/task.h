//
// Created by Alexandra on 6/8/2026.
//

#ifndef TASKS_TASK_H
#define TASKS_TASK_H

#include <string>
#include <utility>
#include <vector>

using std::vector;
using std::string;
class Task {
    private:
    int id;
    string descriere;
    vector<string>programatori;
    string stare;
    public:
    Task(int _id, string _descriere, const vector<string>& _programatori, string _stare) :
    id{_id}, descriere{std::move(_descriere)}, programatori{_programatori}, stare{std::move(_stare)} {}

    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] string getDescriere() const { return descriere; }
    [[nodiscard]] vector<string> getProgramatori() const { return programatori; }
    [[nodiscard ]] string getStare() const { return stare; }

    void setStare(const string& _stare) { stare = _stare; }

    bool operator==(const Task& task) const
    {
        return id == task.id && descriere == task.descriere && programatori == task.programatori && stare == task.stare;
    }
};

#endif //TASKS_TASK_H
