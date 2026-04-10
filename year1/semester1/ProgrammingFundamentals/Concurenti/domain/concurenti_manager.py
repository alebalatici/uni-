from domain.calculations import *
def creare_participant(cod: int, scoruri: list):
    """
    cream un participant
    """
    return [cod, scoruri, sum(scoruri)]

def creare_participanti_preexistenti():
    """
    creeeaza o lista preexistenta de participanti
    :return: lista de participanti
    """
    return [
        creare_participant(1, [10, 10, 8, 10, 7, 8, 8, 3, 9, 8]), #81 #lista_participanti[0]
        creare_participant(2, [10, 9, 10, 10, 10, 8, 7, 5, 2, 3]), #74
        creare_participant(3, [10, 10, 10, 10, 10, 3, 4, 5, 10, 9]), #81
        creare_participant(4, [9, 9, 10, 7, 4, 5, 2, 9, 3]),
        creare_participant(5, [10, 6, 10, 9, 9, 9, 7, 10, 9]),
        creare_participant(6, [10, 10, 7, 7, 3, 10, 5, 8, 10]),
        creare_participant(7, [10, 2, 9, 9, 4, 3, 2, 10, 10]),
        creare_participant(8, [10, 8, 9, 5, 10, 10, 10, 6, 9]),
        creare_participant(9, [10, 10, 10, 9, 10, 9, 3, 7, 10]),
        creare_participant(10, [8, 8, 7, 7, 9, 5, 3, 4, 10]) #61
    ]

lista_participanti = creare_participanti_preexistenti()

def tiparire(lista_participanti: list):
    # tipareste lista de participnati
    if not lista_participanti:
        print("Lista este goala.")
    else:
        for participant in lista_participanti:
            numar = get_numar(participant)
            scoruri = get_scoruri(participant)
            scortotal = get_scortotal(participant)
            print(f"Concurentul {numar} cu scorul total {scortotal}")

def filtrare_participanti_less_n(lista: list, sir: list, n: int):
    #filtreaza participantii cu scorul mai mic decat n
    for i in range(len(lista)):
        if get_scortotal(lista[i]) <= n:
            sir.append(lista[i])
    return sir

def ordonare_crescatoare(lista: list):
    #ordonare crescatoare
    for i in range(len(lista)):
        for j in range (i+1, len(lista)):
            if get_scortotal(lista[i]) > get_scortotal(lista[j]):
                lista[i], lista[j] = lista[j], lista[i]

def ordonare_descrescatoare(lista: list):
    #ordonare descrescatoare
    for i in range(len(lista)):
        for j in range (i+1, len(lista)):
            if get_scortotal(lista[i]) < get_scortotal(lista[j]):
                lista[i], lista[j] = lista[j], lista[i]

def creare_lista_33(lista: list, sir: list, n: int):
    #creeaza o lista noua cu concurentii care au scorul mai mare sau egal cu n
    for i in range(len(lista)):
        if get_scortotal(lista[i]) >= n:
            sir.append(lista[i])

def calculare_medie_interval(lista: list, a: int, b: int):
    """
    calculeaza media scorurilor totale din intervalul [a, b]
    """
    s = 0
    for i in range(a-1, b):
        s += get_scortotal(lista[i])
    return s / (b-a+1)

def filtrare_lista_multiplu_n(lista: list, sir: list, n: int, a: int, b: int):
    """
    filtreaza lista in functie de multiplii lui n (din intervalul [a, b])
    :param lista: lista de participanti
    :param sir: sirul nou/ filtrat
    :param n:
    :param a: capatul din stanga al intervalului
    :param b: capatul din dreapta al intervalului
    :return: sirul nou, cu concurentii din intervalul [a,b] care sunt multiplii lui n
    """
    for i in range (a-1, b):
        if get_scortotal(lista[i]) % n == 0:
            sir.append(lista[i])
    return sir

def set_scoruri(participant, scoruri_noi: list):
    #seteaza scorul unui [articipant
    participant[1] = scoruri_noi

def set_numar(participant, numar_nou: int):
    #seteaza numarul unui particpant
    participant[0] = numar_nou

def set_scortotal(participant, scortotal_nou: int):
    #seteaza scorul total al unui participnat
    participant[2] = scortotal_nou

def stergere_participant(lista: list, n: int):
    """
    sterge scorul participantului cu numarul n din lista
    :return: lista fara scorul participantului cu numarul n
    """
    salvare_stare()
    participant = lista[n - 1]
    set_scoruri(participant, [])
    participant[2] = 0
    return lista

def stergere_interval_participanti(lista: list, a: int, b: int):
    """
    sterge un interval de participanti
    :param lista: lista de participanti
    :param a: capatul din stanga al intervalului
    :param b: capatul din dreapta al intervalului
    :return: lista de participanti cu participantii din intervalul [a, b] stersi
    """
    salvare_stare()
    for i in range (a, b+1):
        #stergere_participant(lista, i)
        participant = lista[i - 1]
        set_scoruri(participant, [])
        participant[2] = 0

def modificare_scor_participant(lista: list, n:int, scor: int):
    """
    modifica scorul participantului n cu scor
    :param lista_de_scoruri: lista de scoruri ce va fi returnata
    :param n: numarul paritcipantului n
    :return: lista de scoruri
    """
    salvare_stare()
    set_scortotal(lista[n - 1], scor)

def adauga_scoruri_participant(lista_de_scoruri: list, n:int):
    """
    adauga scoruri pentru fiecare participant
    :param lista_de_scoruri: lista de scoruri ce va fi returnata
    :param n: numarul paritcipantului n
    :return: lista de scoruri
    """
    print(f"Va rugam introduceti scorurile participantului {n} la fiecare problema.")
    try:
        lista_de_scoruri.append(int(input("Scorul pentru problema 1: ")))
        lista_de_scoruri.append(int(input("Scorul pentru problema 2: ")))
        lista_de_scoruri.append(int(input("Scorul pentru problema 3: ")))
        lista_de_scoruri.append(int(input("Scorul pentru problema 4: ")))
        lista_de_scoruri.append(int(input("Scorul pentru problema 5: ")))
        lista_de_scoruri.append(int(input("Scorul pentru problema 6: ")))
        lista_de_scoruri.append(int(input("Scorul pentru problema 7: ")))
        lista_de_scoruri.append(int(input("Scorul pentru problema 8: ")))
        lista_de_scoruri.append(int(input("Scorul pentru problema 9: ")))
        lista_de_scoruri.append(int(input("Scorul pentru problema 10: ")))
    except ValueError:
        print("Va rugam introduceti scorurile numere valide")
        return

def adauga_participant(lista:list, lista_de_scoruri: list):
    """
    adauga un nou participant pe pozitia len(list)+1
    """
    salvare_stare()
    participant_nou =  creare_participant(len(lista)+1, lista_de_scoruri)
    lista.append(participant_nou)

def potrivire_participanti(lista: list):
    """
    ordoneaza participantii in functie de numarul lor
    """
    for i in range (len(lista)):
        set_numar(lista[i], i+1)

def insereaza_participant(lista: list, lista_de_scoruri, n: int):
    """
    insereaza un nou participant in lista
    """
    salvare_stare()
    participant_nou = creare_participant(n, lista_de_scoruri)
    lista.insert(n-1, participant_nou)
    potrivire_participanti(lista)

def ordonare_dupa_numar(lista: list):
    """
    ordoneaza participantii in functie de numarul lor
    """
    for i in range(len(lista)):
        for j in range (i+1, len(lista)):
            if get_numar(lista[i]) > get_numar(lista[j]):
                lista[i], lista[j] = lista[j], lista[i]

istoric_lista = []
def salvare_stare():
    """
    salveaza starea listei de participanti inaintea fiecarei modificari
    """
    copie = []
    n = 0
    for participant in lista_participanti:
        numar = participant[0]
        scoruri = participant[1][:]
        scortotal = participant[2]
        copie.append([numar, scoruri, scortotal])
    istoric_lista.append(copie)

def undo():
    """
    reface ultima operatie facand un pop in lista istoricului starilor/ revine la starea dinaintea ultimei instructiuni
    """
    global lista_participanti
    stare_anterioara = istoric_lista.pop()
    lista_participanti.clear()
    lista_participanti.extend(stare_anterioara)

lista_participanti_test = creare_participanti_preexistenti()