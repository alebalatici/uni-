//
// Created by Alexandra on 5/9/2026.
//

#include "validator.h"

void Validator::validate(const Melodie& melodie)
{
    string errors;
    if (melodie.get_id() <= 0)
        errors += "Id-ul nu poate fi negativ\n";
    if (melodie.get_titlu().empty())
        errors += "Titlul nu poate fi vid\n";
    if (melodie.get_artist().empty())
        errors += "Artistul nu poate fi vid\n";
    bool contains = false;
    for (auto& i : ranks)
        if (i == melodie.get_rank())
            contains = true;
    if (!contains)
        errors += "Rank-ul trebuie sa fie din multimea [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]\n";

    if (!errors.empty())
    {
        throw ValidationException(errors);
    }
}
