//
// Created by Alexandra on 5/10/2026.
//

#ifndef PRODUSE_VALIDATOR_H
#define PRODUSE_VALIDATOR_H

#include <exception>
#include <utility>
#include "produs.h"
class ValidationException : public std::exception
{
private:
    string msg;
public:
    explicit ValidationException(string msg) : msg(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override { return msg.c_str(); }
};

class Validator {
public:
    void validate(const Produs& produs) ;
};

#endif //PRODUSE_VALIDATOR_H
