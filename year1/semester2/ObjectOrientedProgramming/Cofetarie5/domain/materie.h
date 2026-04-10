#ifndef COFETARIE5_MATERIE_H
#define COFETARIE5_MATERIE_H
#include <stdbool.h>
#include <string.h>

typedef struct {
    char* nume;
    char* producator;
    int cantitate;
} Materie;

Materie* create_materie(char nume[50], char producator[50], int cantitate);

void destroy_materie(void *m);

Materie* copy_materie(Materie* m);

#endif //COFETARIE5_MATERIE_H