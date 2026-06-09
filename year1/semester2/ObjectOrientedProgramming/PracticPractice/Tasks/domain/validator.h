//
// Created by Alexandra on 6/9/2026.
//

#ifndef TASKS_VALIDATOR_H
#define TASKS_VALIDATOR_H

#include <utility>

#include "../domain/task.h"

class ValidationException : public std::exception
{
    private:
    string message;
    public:
    explicit ValidationException(string message) : message{std::move(message)} {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class Validator {
    public:
    string errors;
    void validate(const Task& task)
    {
        if (task.getDescriere().empty())
        {
            errors += "The task description should not be empty.\n";
        }
        if (task.getStare() != "open" && task.getStare() != "closed" && task.getStare() != "inprogress")
        {
            errors += "Stare should be open, closed or inprogress.\n";
        }
        if (task.getProgramatori().empty() || task.getProgramatori().size() > 4)
        {
            errors += "The number of programmers should be between 1 and 4.\n";
        }

        if (!errors.empty())
        {
            throw ValidationException(errors);
        }
    }
};

#endif //TASKS_VALIDATOR_H
