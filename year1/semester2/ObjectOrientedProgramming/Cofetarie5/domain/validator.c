#include "validator.h"
#include <string.h>

int valideaza_materie(Materie* m) {
    if (strlen(m->nume) < 2)
        return -1;

    if (strlen(m->producator) < 2)
        return -2;

    if (m->cantitate < 0)
        return -3;

    return 0;
}
