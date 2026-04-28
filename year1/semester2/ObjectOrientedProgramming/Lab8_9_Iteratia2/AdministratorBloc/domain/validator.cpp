#include "validator.h"

void ValidatorLocatar::validate(const Locatar &locatar) const {
    string errors;
    if (locatar.get_apartment() <= 0) {
        errors += "Numarul apartamentului trebuie sa fie natural!\n";
    }
    if (locatar.get_nume().empty()) {
        errors += "Numele nu poate fi vid!\n";
    }
    if (locatar.get_suprafata() <= 0) {
        errors += "Suprafata nu poate fi negativa!\n";
    }
    if (locatar.get_tip().empty()) {
        errors += "Tipul nu poate fi vid\n";
    }

    if (!errors.empty()) {
        throw ValidationException(errors);
    }
}