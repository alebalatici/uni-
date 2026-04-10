def get_numar(participanti):
    """
    returneaza numarul/codul unui participant
    """
    return participanti[0]
def get_scoruri(participanti):
    """
    returneaza lista de scoruri a unui participant
    """
    return participanti[1]
def get_scortotal(participanti):
    """
    returneaza scorul total al unui participant
    """
    return participanti[2]


def calculare_scor_minim(lista: list):
    """
    Functie pentru calcularea celui mai mic scor
    :param lista: lista de participanti
    :return: scorul minim
    """
    min = get_scortotal(lista[0])
    for i in range(1, len(lista)):
        if get_scortotal(lista[i]) < min:
            min = get_scortotal(lista[i])
    return min

def calculare_scor_maxim(lista: list):
    """
    Functie pentru calcularea celui mai mare scor
    :param lista: lista de participanti
    :return: scorul maxim
    """
    max = get_scortotal(lista[0])
    for i in range (len(lista)):
        if get_scortotal(lista[i]) > max:
            max = lista[i]["scortotal"]
    return max

def calculare_scor_minim_interval(lista: list, a: int, b: int):
    """
    Functie pentru calcularea celui mai mic scor din intervalul [a, b]
    :param lista: lista de participanti
    :param a: extremitatea din stanga
    :param b: extremitatea din dreapta
    :return: scorul minim
    """
    min = get_scortotal(lista[a-1])
    for i in range(a, b):
        if get_scortotal(lista[i]) < min:
            min = get_scortotal(lista[i])
    return min

# def scor_total(lista: list, indice: int):
#     """
#     Functie pentru calcularea scorului total al unui indice din lista
#     :param lista: lista de participanti
#     :param indice: indicele unui element din lista
#     :return: suma scorurilor pentru fiecare indice din lista
#     """
#     s = 0
#     for i in lista[indice]["scoruri"]:
#         s = s + i
#     return s

# def calculare_scoruri_participanti(lista: list):
#     """
#     Functie pentru calcularea scorului fiecarui participant, adauga o cheie noua dictionarelor "scortotal"
#     :param lista: lista de participanti
#     """
#     for i in range(len(lista)):
#         lista[i]["scortotal"] = scor_total(lista, i)