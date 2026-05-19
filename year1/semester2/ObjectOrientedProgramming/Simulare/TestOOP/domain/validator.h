//
// Created by Alexandra on 5/19/2026.
//

#ifndef TESTOOP_VALIDATOR_H
#define TESTOOP_VALIDATOR_H

#include <qmath.h>
#include <utility>

#include "radiation.h"

class ValidationException : public std::exception
{
    private:
    string message;
    public:
    explicit ValidationException(string message) : message(std::move(message)) {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class Validator {
    public:
    /**
     * Valideaza o anumita radiatie in lista de radiatii
     * @param radiation Radiatia de validat
     */
    void validate(const Radiation& radiation) {
        string errors;
        if (radiation.get_description().empty())
            errors += "Radiation description is required\n";

        if (radiation.get_frecventa() < 0.0 && radiation.get_frecventa() > 100.0)
            errors += "Frecventa is required to be greater than or equal to 0.0 and less than 100.0\n";

        if (radiation.get_tip_frecventa() != "alpha" && radiation.get_tip_frecventa() != "beta" && radiation.get_tip_frecventa() != "gamma" && radiation.get_tip_frecventa() != "delta" && radiation.get_tip_frecventa() != "theta")
            errors += "Tip frecventa is required to be alpha or beta or gamma or delta or theta\n";

        if (!errors.empty())
        {
            throw ValidationException(errors);
        }
    }
};



#endif //TESTOOP_VALIDATOR_H
