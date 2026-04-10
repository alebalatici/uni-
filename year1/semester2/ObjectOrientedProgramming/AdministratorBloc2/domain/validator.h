#ifndef ADMINISTRATORBLOC_VALIDATOR_H
#define ADMINISTRATORBLOC_VALIDATOR_H
#include "locatar.h"
#include <string>
#include <exception>
#include <utility>
using std::string;

class ValidationException : public std::exception {
    string msg;
public:
    ValidationException(string  msg) : msg(std::move(msg)) {

    }
    [[nodiscard]] string get_message() const {
        return msg;
    }
};

class ValidatorLocatar {
public:
    static void validate(const Locatar &locatar) ;
};

#endif //ADMINISTRATORBLOC_VALIDATOR_H