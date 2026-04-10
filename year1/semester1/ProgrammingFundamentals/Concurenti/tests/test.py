import copy
from domain.concurenti_manager import *
from domain.concurenti_manager import lista_participanti, lista_participanti_test, get_numar, get_scoruri, get_scortotal

def test_all():
    try:
        test_f11()
        test_f12()
        test_f21()
        test_f22()
        test_f23()
        test_f31()
        test_f32()
        test_f33()
        test_f41()
        test_f42()
        test_f43()
        test_f51()
        test_f52()
        test_f61()
    except AssertionError as e:
        print("Testele au esuat")
        raise #opreste programul

def test_f11():
    lista = copy.deepcopy(lista_participanti)
    adauga_participant(lista, [1, 1, 1, 1, 1, 1, 1, 1, 1, 1])
    assert get_scortotal(lista[10]) == 10
    adauga_participant(lista, [10, 10, 10, 10, 10, 10, 10, 10, 10, 10])
    assert get_scortotal(lista[11]) == 100
    adauga_participant(lista, [5, 5, 5, 5, 5, 5, 5, 5, 5, 5])
    assert get_scortotal(lista[12]) == 50

def test_f12():
    lista = copy.deepcopy(lista_participanti)
    insereaza_participant(lista, [1, 1, 1, 1, 1, 1, 1, 1, 1, 1], 5)
    assert get_scortotal(lista[4]) == 10
    insereaza_participant(lista, [10, 10, 10, 10, 10, 10, 10, 10, 10, 10], 4)
    assert get_scortotal(lista[3]) == 100
    insereaza_participant(lista, [5, 5, 5, 5, 5, 5, 5, 5, 5, 5], 3)
    assert get_scortotal(lista[2]) == 50

def test_f21():
    lista_test = copy.deepcopy(lista_participanti)
    lista_test = stergere_participant(lista_participanti_test, 1)
    lista_test = stergere_participant(lista_participanti_test, 2)
    lista_test = stergere_participant(lista_participanti_test, 3)
    ordonare_dupa_numar(lista_test)
    assert get_scortotal(lista_test[0]) == 0
    assert get_scortotal(lista_test[1]) == 0
    assert get_scortotal(lista_test[2]) == 0

def test_f22():
    lista = copy.deepcopy(lista_participanti_test)
    stergere_interval_participanti(lista, 1, 10)
    assert get_scortotal(lista[0]) == 0
    assert get_scortotal(lista[1]) == 0
    assert get_scortotal(lista[2]) == 0
    assert get_scortotal(lista[-1]) == 0
    assert get_scortotal(lista[-2]) == 0
    assert get_scortotal(lista[-3]) == 0
    lista = copy.deepcopy(lista_participanti)
    stergere_interval_participanti(lista, 5, 10)
    assert get_scortotal(lista[4]) == 0
    assert get_scortotal(lista[9]) == 0
    assert get_scortotal(lista[0]) == 81
    assert get_scortotal(lista[1]) == 74
    assert get_scortotal(lista[2]) == 81
    assert get_scortotal(lista[3]) == 58
    assert get_scortotal(lista[-2]) == 0
    lista = copy.deepcopy(lista_participanti_test)
    stergere_interval_participanti(lista, 2, 7)
    assert (get_scortotal(lista[1]) == get_scortotal(lista[2]) ==
            get_scortotal(lista[3]) == get_scortotal(lista[4]) ==
            get_scortotal(lista[5]) == get_scortotal(lista[6]) == 0)

def test_f23():
    lista = copy.deepcopy(lista_participanti_test)
    modificare_scor_participant(lista, 1, 10)
    assert get_scortotal(lista[0]) == 10
    modificare_scor_participant(lista, 5, 10)
    assert get_scortotal(lista[4]) == get_scortotal(lista[0])
    modificare_scor_participant(lista, 1, 20)
    assert get_scortotal(lista[0]) == 20
    modificare_scor_participant(lista, 5, 20)
    assert get_scortotal(lista[4]) == get_scortotal(lista[0])
    modificare_scor_participant(lista, 2, 30)
    assert get_scortotal(lista[1]) == 30

def test_f31(): #Tipareste participantii care au scorul mai mic decat n
    # Tipărește participanții care au scorul mai mic decât n
    n = 75
    sir = []
    sir = filtrare_participanti_less_n(lista_participanti, sir, n)
    assert get_scortotal(sir[0]) == 74  # primul participant din sir
    assert len(sir) == 5
    assert get_scortotal(sir[-1]) == 61  # ultimul participant din sir
    assert calculare_scor_maxim(sir) <= n

def test_f32(): #Tipareste participantii in ordinea scorului
    ordonare_crescatoare(lista_participanti)
    assert get_numar(lista_participanti[0]) == 4
    assert get_scortotal(lista_participanti[0]) == 58
    assert get_numar(lista_participanti[-1]) == 1
    assert get_scortotal(lista_participanti[-1]) == 81
    ordonare_descrescatoare(lista_participanti)
    assert get_numar(lista_participanti[0]) == 3
    assert get_scortotal(lista_participanti[0]) == 81
    assert get_numar(lista_participanti[-1]) == 4
    assert get_scortotal(lista_participanti[-1]) == 58

def test_f33(): #Tipareste participantii care au scorul mai mare decat n, in ordinea scorului
    n = 75
    sir = []
    creare_lista_33(lista_participanti, sir, n)
    ordonare_crescatoare(sir)
    assert get_numar(sir[0]) == 8
    assert get_scortotal(sir[0]) == 77
    assert get_numar(sir[1]) == 9
    assert get_scortotal(sir[1]) == 78
    assert get_numar(sir[-1]) == 3
    assert get_scortotal(sir[-1]) == 81

def test_f41(): #Calculeaza media scorurilor pentru un interval [a, b]
    n = calculare_medie_interval(lista_participanti, 3, 9)
    assert n > 71
    assert n < 72
    assert n == 71.14285714285714
    n = calculare_medie_interval(lista_participanti, 1, 10)
    assert n == 71.8
    n = calculare_medie_interval(lista_participanti, 1, 1)
    assert n == 81
    n = calculare_medie_interval(lista_participanti, 10, 10)
    assert n == 58
    n = calculare_medie_interval(lista_participanti, 5, 10)
    assert n == 66.5

def test_f42(): #Calculeaza scorul minim pentru un interval [a, b]
    ordonare_dupa_numar(lista_participanti)
    n = calculare_scor_minim_interval(lista_participanti, 3, 9)
    assert n == 58
    n = calculare_scor_minim_interval(lista_participanti, 1, 10)
    assert n == 58
    n = calculare_scor_minim_interval(lista_participanti, 10, 10)
    assert n == 61
    n = calculare_scor_minim_interval(lista_participanti, 5, 10)
    assert n == 59
    n = calculare_scor_minim_interval(lista_participanti,  7, 8)
    assert n == 59

def test_f43(): #Tipareste participantii dintr-un interval [a, b] care au scorul multiplu de 10
    sir = []
    sir = filtrare_lista_multiplu_n(lista_participanti, sir, 10, 1, 10)
    assert len(sir) == 1
    assert get_numar(sir[0]) == 6
    assert get_scortotal(sir[0]) == 70
    sir = []
    sir = filtrare_lista_multiplu_n(lista_participanti, sir, 10, 1, 5)
    assert len(sir) == 0

def test_f51(): #Filtreaza participantii care au scorul total multiplu de n
    sir = []
    sir = filtrare_lista_multiplu_n(lista_participanti, sir, 2, 1, 10)
    assert len(sir) == 4
    sir = []
    sir = filtrare_lista_multiplu_n(lista_participanti, sir, 9, 1, 10)
    assert len(sir) == 2
    sir = []
    sir = filtrare_lista_multiplu_n(lista_participanti, sir, 7, 1, 10)
    assert len(sir) == 2

def test_f52(): #Filtreaza participantii care au scorul mai mic decat n
    sir = []
    sir = filtrare_participanti_less_n(lista_participanti, sir, 70)
    assert len(sir) == 4
    sir = []
    sir = filtrare_participanti_less_n(lista_participanti, sir, 80)
    assert len(sir) == 8
    sir = []
    sir = filtrare_participanti_less_n(lista_participanti, sir, 58)
    assert len(sir) == 1
    sir = []
    sir = filtrare_participanti_less_n(lista_participanti, sir, 50)
    assert len(sir) == 0

def test_f61():
    adauga_participant(lista_participanti, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
    assert get_scortotal(lista_participanti[-1]) == 55
    undo()
    assert get_scortotal(lista_participanti[-1]) == 61
    insereaza_participant(lista_participanti, [1, 1, 1, 1, 1, 1, 1, 1, 1, 1], 3)
    assert get_scortotal(lista_participanti[2]) == 10
    insereaza_participant(lista_participanti, [2, 2, 2, 2, 2, 2, 2, 2, 2, 2], 3)
    assert get_scortotal(lista_participanti[2]) == 20
    undo()
    assert get_scortotal(lista_participanti[2]) == 10
    undo()
    assert get_scortotal(lista_participanti[2]) == 81
    stergere_participant(lista_participanti, 1)
    assert get_scortotal(lista_participanti[0]) == 0
    stergere_participant(lista_participanti, 2)
    assert get_scortotal(lista_participanti[1]) == 0
    undo()
    undo()
    assert get_scortotal(lista_participanti[1]) == 74
    assert get_scortotal(lista_participanti[0]) == 81
    stergere_interval_participanti(lista_participanti, 2, 10)
    assert get_scortotal(lista_participanti[2]) == 0
    assert get_scortotal(lista_participanti[1]) == 0
    assert get_scortotal(lista_participanti[9]) == 0
    undo()
    assert get_scortotal(lista_participanti[9]) == 61
    assert get_scortotal(lista_participanti[2]) == 81
    assert get_scortotal(lista_participanti[1]) == 74
    modificare_scor_participant(lista_participanti, 1, 10)
    assert get_scortotal(lista_participanti[0]) == 10
    undo()
    assert get_scortotal(lista_participanti[0]) == 81
    modificare_scor_participant(lista_participanti, 2, 100)
    assert get_scortotal(lista_participanti[1]) == 100
    undo()
    assert get_scortotal(lista_participanti[1]) == 74

if __name__ == '__main__':
    test_all()