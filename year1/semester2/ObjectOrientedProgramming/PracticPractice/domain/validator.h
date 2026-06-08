//
// Created by Alexandra on 5/9/2026.
//

#ifndef MELODII_VALIDATOR_H
#define MELODII_VALIDATOR_H
#include <exception>
#include <string>
#include <utility>
#include "melodie.h"
using std::string;
class ValidationException : public std::exception
{
    private:
    std::string msg;
    public:
    explicit ValidationException(std::string msg) : msg{std::move(msg)} {}
    [[nodiscard]] const char* what() const noexcept override { return msg.c_str(); }
};

class Validator {
private:
    int ranks[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
public:
    void validate(const Melodie& melodie);
};

#endif //MELODII_VALIDATOR_H
