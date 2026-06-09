//
// Created by Alexandra on 5/10/2026.
//

#include "validator.h"

void Validator::validate(const Produs& produs)
{
    string errors;
    if (produs.get_nume().empty())
        errors += "Numele produsului nu poate fi vid\n";
    if (!(produs.get_pret() >=1.0 && produs.get_pret() <= 100.0))
        errors += "Pretul produsului trebuie sa fie intre 1.0 si 100.0\n";
    if (!errors.empty())
    {
        throw ValidationException(errors);
    }
}