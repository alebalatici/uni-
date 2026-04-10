from domain.concurenti_manager import *
#from domain.calculations import *
#from tests.test import test_all
#from main import lista_participanti, lista_participanti_test, lista_noua_participanti, istoric_lista

def afisare_meniu_principal():
    print ("Meniu Principal")
    print ("1. Adauga un scor unui participant")
    print ("2. Modifica scorul unui participant")
    print ("3. Tipareste lista de participanti")
    print ("4. Operatii pe un subset de participanti")
    print ("5. Filtreaza participantii dupa un anumit criteriu")
    print ("6. Undo")
    print ("7. Exit")

def afisare_meniu_f1():
    print ("1. Adauga un scor unui nou participant")
    print ("2. Insereaza scorul unui nou participant")

def afisare_meniu_f2():
    print ("1. Sterge scorul unui participant")
    print ("2. Sterge scorul pentru un interval de participanti")
    print ("3. Inlocuieste scorul unui participant")

def afisare_meniu_f3():
    print ("1. Tipareste participantii care au scorul mai mic decat n")
    print ("2. Tipareste participantii in ordinea scorului")
    print ("3. Tipareste participantii care au scorul mai mare decat n, in ordinea scorului")

def afisare_meniu_f32():
    print ("a. Ordonare Crescatoare")
    print ("b. Ordonare Descrescatoare")

def afisare_meniu_f4():
    print ("1. Calculeaza media scorurilor pentru un interval [a, b]")
    print ("2. Calculeaza scorul minim pentru un interval [a, b]")
    print ("3. Tipareste participantii dintr-un interval [a, b] care au scorul multiplu de 10")

def afisare_meniu_f5():
    print ("1. Filtreaza participantii care au scorul total multiplu de n")
    print ("2. Filtreaza participantii care au scorul mai mic decat n")

def introducere_interval(lista: list, a: int, b: int):
    """
    Pentru interfata cu utilizatorul, introduce intervalul [a, b] si il valideaza
    :param lista: lista de participanti
    :param a: extremitatea din stanga
    :param b: extremitateate din dreapta
    """
    while True:
        try:
            a = int(input("Introduceti numarul a: "))
            if a < 1 or a > len(lista):
                raise ValueError
            b = int(input("Introduceti numarul b: "))
            if b > len(lista) or b < a:
                raise ValueError
            print(f"Intervalul este [{a}, {b}]")
            return a, b
        except ValueError:
            print("Va rugam introduceti numere naturale valide")

def validare_participant_n (lista_participanti):
    while True:
        try:
            #n = (
            n = int(input("Introduceti numarul participantului pentru care doriti sa modificati scorul: "))
            if n < 1 or n > len(lista_participanti):
                raise ValueError
            print(f"Ati selectat participantul cu numarul {n}")
            return n
        except ValueError:
            print(f"Va rugam introduceti un numar valid. Nu exista acest participant")

#lista_participanti = creare_participanti_preexistenti()  # lista de dicționare
#lista_noua_participanti = transforma_in_lista_simpla(lista_participanti)
#tiparire_lista_noua(lista_noua_participanti)

def run():
    global lista_participanti_test
    global lista_participanti
    global istoric_lista
    while True:
        # salvare_stare()
        # print(istoric_lista)
        afisare_meniu_principal()
        optiune = input(">>>").upper()
        match optiune:
            case '1':
                afisare_meniu_f1()
                optiune1 = input(">>>")
                match optiune1:
                    case '1':
                        lista_de_scoruri = []
                        adauga_scoruri_participant(lista_de_scoruri, len(lista_participanti)+1)
                        adauga_participant(lista_participanti, lista_de_scoruri)
                        print(f"Participantul {len(lista_participanti)} a fost introdus cu succes. Punctajul sau total este {get_scortotal(lista_participanti[-1])}")
                    case '2':
                        try:
                            n = int(input("Introduceti pozitia pe care doriti sa inserati concurentul nou: "))
                            lista_de_scoruri = []
                            adauga_scoruri_participant(lista_de_scoruri, n)
                            insereaza_participant(lista_participanti, lista_de_scoruri, n)
                            print(f"Participantul {n} a fost introdus cu succes. Punctajul sau total este {get_scortotal(lista_participanti[n-1])}")
                        except ValueError:
                            print("Va rugam introduceti un numar valid.")
                    case _:
                        print("Optiune invalida.")
            case '2':
                afisare_meniu_f2()
                optiune2 = input(">>>")
                match optiune2:
                    case '1':
                        n = 0
                        n = validare_participant_n(lista_participanti)
                        ordonare_dupa_numar(lista_participanti)
                        sir = stergere_participant(lista_participanti, n)
                        lista_participanti = sir
                    case '2':
                        a = b = 0
                        a, b = introducere_interval(lista_participanti, a, b)
                        ordonare_dupa_numar(lista_participanti)
                        stergere_interval_participanti(lista_participanti, a, b)
                    case '3':
                        n = 0
                        n = validare_participant_n(lista_participanti)
                        print (f"Participantul {n} are scorul {get_scortotal(lista_participanti[n-1])}.")
                        try:
                            scor_nou = int(input(f"Va rugam introduceti noul scor al participantului {n}: "))
                            ordonare_dupa_numar(lista_participanti)
                            modificare_scor_participant(lista_participanti, n, scor_nou)
                            print ("Scor modificat cu succes.")
                        except ValueError:
                            print("Va rugam introduceti un numar valid.")
                    case _:
                        print("Optiune invalida.")
            case '3':
                afisare_meniu_f3()
                optiune3 = input(">>>")
                match optiune3:
                    case '1':
                        try:
                            n = int(input("Introduceti numarul n: "))
                            if n < calculare_scor_minim(lista_participanti):
                                print(f"Nu exista participanti cu scorul mai mic decat {n}.")
                            else:
                                sir = []
                                sir = filtrare_participanti_less_n(lista_participanti, sir, n)
                                tiparire(sir)
                        except ValueError:
                            print("Va rugam introduceti un numar valid")
                    case '2':
                        afisare_meniu_f32()
                        optiune32 = input("Alegeti ordinea: ").lower()
                        match optiune32:
                            case 'a':
                                ordonare_crescatoare(lista_participanti)
                                tiparire(lista_participanti)
                            case 'b':
                                ordonare_descrescatoare(lista_participanti)
                                tiparire(lista_participanti)
                            case _:
                                print("Optiune invalida.")
                    case '3':
                        try:
                            n = int(input("Introduceti numarul n: "))
                            sir = []
                            creare_lista_33(lista_participanti, sir, n)
                            #if n > calculare_scor_maxim(lista_participanti):
                            if len(sir) == 0:
                                print(f"Nu exista participanti cu scor mai mare decat {n}.")
                            else:
                                afisare_meniu_f32()
                                optiune33 = input("Alegeti ordinea: ").lower()
                                match optiune33:
                                    case 'a':
                                        ordonare_crescatoare(sir)
                                        tiparire(sir)
                                    case 'b':
                                        ordonare_descrescatoare(sir)
                                        tiparire(sir)
                                    case _:
                                        print("Optiune invalida.")
                        except ValueError:
                            print("Va rugam introduceti un numar valid")
                    case _:
                        print("Optiune invalida.")
            case '4':
                afisare_meniu_f4()
                optiune4 = input(">>>")
                match optiune4:
                    case '1':
                        a = b = 0
                        a, b = introducere_interval(lista_participanti, a, b)
                        n = calculare_medie_interval(lista_participanti, a, b)
                        print(f"Media intervalului [{a}, {b}] este {n}")
                    case '2':
                        a = b = 0
                        a, b = introducere_interval(lista_participanti, a, b)
                        n = calculare_scor_minim_interval(lista_participanti, a, b)
                        print(f"Scorul minim din intervalul [{a}, {b}] este {n}")
                    case '3':
                        a = b = 0
                        a, b = introducere_interval(lista_participanti, a, b)
                        sir = []
                        sir = filtrare_lista_multiplu_n(lista_participanti, sir, 10, a, b)
                        if not sir:
                            print("Nu exista participanti cu scorul total divizibil cu 10.")
                        else:
                            tiparire(sir)
                    case _:
                        print("Optiune invalida.")
            case '5':
                afisare_meniu_f5()
                optiune5 = input(">>>")
                match optiune5:
                    case '1':
                        try:
                            n = int(input("Introduceti numarul n: "))
                            sir = []
                            sir = filtrare_lista_multiplu_n(lista_participanti, sir, n, 1, 10)
                            tiparire(sir)
                        except ValueError:
                            print("Va rugam introduceti un numar valid")
                    case '2':
                        try:
                            n = int(input("Introduceti numarul n: "))
                            sir = []
                            sir = filtrare_participanti_less_n(lista_participanti, sir, n)
                            tiparire(sir)
                        except ValueError:
                            print("Va rugam introduceti un numar valid")
                    case _:
                        print("Optiune invalida.")
            case '6':
                if istoric_lista:
                    undo()
                    print("Undo efectuat cu succes.")
                else:
                    print("Nu exista pasi de refacut.")
            case '7':
                print("Iesire din aplicatie...")
                break
            case _:
                print(f"Nu exista optiunea {optiune}. Introduceti o optiune valida.")
