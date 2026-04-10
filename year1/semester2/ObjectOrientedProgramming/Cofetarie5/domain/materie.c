#define _CRT_SECURE_NO_WARNINGS
#include "materie.h"
#include <stdio.h>
#include <stdlib.h>

Materie* create_materie(char* nume, char* producator, int cantitate) {
    Materie* m = malloc(sizeof(Materie));
    m->nume = malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(m->nume, nume);
    m->producator = malloc((strlen (producator) + 1) * sizeof(char));
    strcpy(m->producator, producator);
    m->cantitate = cantitate;
    return m;
};

void destroy_materie(void *m) {
    Materie* temp = (Materie*)m;
    free(temp->nume);
    free(temp->producator);
    free(temp);
}

Materie* copy_materie(Materie* m) {
    return create_materie(m->nume, m->producator, m->cantitate);
}