#include "console.h"
#include <stdio.h>
#include <stdlib.h>

void print_menu()
{
    printf("1. Adaugare de materie prima\n");
    printf("2. Modificare materie prima\n");
    printf("3. Stergere materie prima\n");
    printf("4. Vizualizare materii prime care satisfac un criteriu\n");
    printf("5. Vizualizare materii prime din stoc ordonat dupa nume sau cantitate disponibila\n");
    printf("6. Afiseaza toate materiile\n");
    printf("7. Filtreaza materiile al caror producator are numarul de vocale mai mare decat un numar dat\n");
    printf("8. Undo\n");
    printf("9. Exit\n");
    printf("Alegeti o optiune: \n");
}

void add_materie_ui(MyList* list, MyList* undo_list) {
    char nume[100], producator[100];
    int cantitate;

    printf("Introduceti numele materiei: ");
    int ok = scanf(" %99[^\n]", nume);  //pana la newline

    printf("Introduceti producatorul materiei: ");
    ok = scanf(" %99[^\n]", producator);

    printf("Introduceti cantitatea materiei: ");
    ok = scanf("%d", &cantitate);
    if (ok != 1) {
        printf("%s", "Optiune invalida!\n");
        while (getchar() != '\n');
        return;
    }

    int result = srv_add_calatorie(list, undo_list, nume, producator, cantitate);
    if (result == 0) {
        printf("%s", "Materia a dost adaugata cu succes\n");
        return;
    }
    if (result == -1) {
        printf("%s", "Numele trebuie sa aiba cel putin 2 caractere\n");
        return;
    }
    if (result == -2) {
        printf("%s", "Numele producatorului trebuie sa aiba cel putin 2 caractere\n");
        return;
    }
    if (result == -3) {
        printf("%s", "Cantitatea nu poate fi un numar negativ\n");
        return;
    }
}

void modify_materie_ui(MyList* list, MyList* undo_list) {
    char nume[100], producator[100];
    int cantitate;

    printf("Introduceti numele materiei pe care doriti sa o modificati: ");
    int ok = scanf(" %99[^\n]", nume);

    int result = find_by_name(list, nume);
    if (result == -1) {
        printf("%s", "Nu exista vreo materie cu acest nume\n");
        return;
    }
    printf("Introduceti noul producator al materiei: \n");
    ok = scanf(" %99[^\n]", producator);

    printf("Introduceti noua cantitate a materiei: \n");
    ok = scanf("%d", &cantitate);
    if (ok != 1) {
        printf("Optiune invalida!\n");
        while (getchar() != '\n');
        return;
    }
    result = modify_element(list, undo_list, nume, producator, cantitate);
    if (result == -2) {
        printf("%s", "Numele producatorului trebuie sa aiba cel putin 2 caractere\n");
        return;
    }
    if (result == -3) {
        printf("%s", "Cantitatea nu poate fi un numar negativ\n");
        return;
    }
    printf("Materia a fost modificata cu succes\n");
}

void delete_materie_ui(MyList* list, MyList* undo_list) {
    char nume[100];
    printf("Introduceti numele materiei pe care doriti sa o stergeti: ");
    int ok = scanf(" %99[^\n]", nume);
    int result = srv_delete_calatorie(list, undo_list, nume);
    if (result == -1)
        printf("Nu exista vreo materie cu acest nume\n");
    else
        printf("Materia a fost stearsa cu succes\n");
}

void print_menu_filtrare() {
    printf("1. Afiseaza materiile care incep cu o anumita litera\n");
    printf("2. Afiseaza materiile care au cantitatea mai mare decat un anumit numar\n");
}

void print_menu_sortare() {
    printf("1. Sorteaza materiile dupa initiala\n");
    printf("2. Sorteaza materiile dupa cantitate\n");
}

void filter_by_name_ui(MyList* list) {
    char c;
    printf("Introduceti initiala numelui materiei: ");
    int ok = scanf(" %c", &c);  //pana la newline
    MyList* new_list = filter_by_name(list, c);
    print_all(new_list);
    destroy_list(new_list, destroy_materie);
}

void filter_by_quantity_ui(MyList* list)
{
    int c;
    printf("Introduceti cantitatea minima a materiei: ");
    int ok = scanf("%d", &c);
    if (ok != 1) {
        printf("Optiune invalida!\n");
        while (getchar() != '\n');
        return;
    }
    MyList* new_list = filter_by_quantity(list, c);
    print_all(new_list);
    destroy_list(new_list, destroy_materie);
}

void filter_ui(MyList *list) {
    print_menu_filtrare();
    char option;
    if (scanf(" %c", &option) != 1) {
        printf("%s", "Optiune invalida");
        while (getchar() != '\n');
    }
    switch (option) {
        case '1':
            filter_by_name_ui(list);
            break;
        case '2':
            filter_by_quantity_ui(list);
            break;
        default:
            printf("%s", "Optiune invalida!\n");
            break;
    }
}

void print_all(MyList* list) {
    int n = list->length;

    if (n == 0) {
        printf("%s", "Lista este goala!\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        Materie* m = list->elements[i];
        printf("Nume: %s | Producator: %s | Cantitate: %d", m->nume, m->producator, m->cantitate);
        printf("\n");
    }
    printf("\n");
}

void sort_ui(MyList* list) {
    print_menu_sortare();
    char option;
    if (scanf(" %c", &option) != 1) {
        printf("%s", "Optiune invalida!");
        while (getchar() != '\n');
    }

    switch (option) {
        case '1':
            sort_by_name(list);
            print_all(list);
            break;
        case '2':
            sort_by_quantity(list);
            print_all(list);
            break;
        default:
            printf("%s", "Optiune invalida!\n");
    }
}

void undo_ui(MyList **list, MyList* undo_list) {
    /*
    MyList* new_list = undo(*list, undo_list);
    if (new_list == *list) {
        printf("Nu exista operatii pentru undo!\n");
        return;
    }


    *list = new_list;
    */

    *list = undo(*list, undo_list);
    printf("Undo efectuat cu succes!\n");

    //destroy_list(new_list, destroy_materie);
}

void filter_by_producator_ui(MyList* list) {
    int minimum_vowels;
    printf("Introduceti numarul minim de vocale: ");
    int ok = scanf("%d", &minimum_vowels);
    if (ok != 1) {
        printf("%s", "Optiune invalida!\n");
        while (getchar() != '\n');
        return;
    }
    MyList* new_list = filter_by_producator(list, minimum_vowels);
    print_all(new_list);
    destroy_list(new_list, destroy_materie);
}

void run() {
        MyList* list = create_empty_list();
        MyList* undo_list = create_empty_list();
        list->length = 0;
        list->capacity = 1;
        while (1) {
            print_menu();
            char option;
            if (scanf(" %c", &option) != 1) {
                printf("%s", "Optiune invalida!\n");
                while (getchar() != '\n');
                continue;
            }
            switch (option) {
                case '1':
                    add_materie_ui(list, undo_list);
                    break;
                case '2':
                    modify_materie_ui(list, undo_list);
                    break;
                case '3':
                    delete_materie_ui(list, undo_list);
                    break;
                case '4':
                    filter_ui(list);
                    break;
                case '5':
                    sort_ui(list);
                    break;
                case '6':
                    print_all(list);
                    break;
                case '7':
                    filter_by_producator_ui(list);
                    break;
                case '8':
                    undo_ui(&list, undo_list);
                    break;
                case '9':
                    printf("Iesire...");
                    destroy_list(list, destroy_materie);
                    destroy_list(undo_list, destroy_lista_materii);
                    exit(0);
                default:
                    printf("%s", "Optiune invalida!\n");
                    break;
            }
        }
    }