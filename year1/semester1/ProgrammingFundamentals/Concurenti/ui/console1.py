from domain.concurenti_manager import *
import ast
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

def run():
    global lista_participanti
    while True:
        comenzi = input("Introduceti o comanda: ")
        if comenzi.lower() == 'exit':
            break

        comenzi_lista = comenzi.split(';') #separa comenzile daca utilizatorul introduce mai multe

        for comanda in comenzi_lista:
            comanda = comanda.strip() #eliminam spatiile dinaintea fiecarei comenzi
            if not comanda:
                continue

            elemente_comanda = comanda.split(" ", 1) #numarul maxim de bucati in care se desparte comanda
            c = elemente_comanda[0]
            if c == 'add': #add 1, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 55
                try:
                    if len(elemente_comanda) < 2:
                        print("Format invalid pentru comanda 'add'. Va rugam introduceti o alta comanda.")
                        continue

                    scoruri_str = elemente_comanda[1]  #[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
                    #parts = detalii.split(",", 1)
                    #numar_str = parts[0]
                    #lista_str = parts[]
                    #numar_participant = int(numar_str.strip())
                    scoruri_str = scoruri_str.strip()
                    if not (scoruri_str.startswith('[') and scoruri_str.endswith(']')):
                        print("Lista scorurilor trebuie sa fie intre paranteze[].")
                        continue

                    scoruri = ast.literal_eval(scoruri_str)#interpretez stringul drept o lista
                    for i in scoruri:
                        if not isinstance(i, (int, float)):
                            print("Toate scorurile trebuie sa fie numere!")
                            continue

                    #participant = creare_participant(numar_participant, scoruri)
                    #lista_participanti.append(participant)
                    adauga_participant(lista_participanti, scoruri)
                    print(f"Participantul {len(lista_participanti)} are scorurile: {scoruri}. Acesta are scorul total {get_scortotal(lista_participanti[-1])}")

                except Exception as e:
                    print(f"Eroare la comanda '{comanda}': {e}")

            elif c == 'delete':
                if len (elemente_comanda) < 2:
                    print("Va rugam specificati numarul participantului pe care doriti sa il stergeti.")
                    continue

                numar_participant = int(elemente_comanda[1].strip())
                stergere_participant(lista_participanti, numar_participant)
                print(f"Participantul {numar_participant} a fost sters cu succes")

            elif c == 'filter':#filtreaza participantii cu scorul total mai mic ca n
                try:
                    if len(elemente_comanda) != 2:
                        print("Formatul este invalid. Va rugam introduceti un numar n pentru a filtra scorurile totale mai mici ca n din lista de participanti.")
                        continue

                    n = int(elemente_comanda[1].strip())
                    sir = []
                    sir = filtrare_participanti_less_n(lista_participanti, sir,  n)
                    if not sir:
                        print(f"Nu exista participanti cu scorul toatal mai mic decat n in lista de participanti.")
                    else:
                        tiparire(sir)
                except Exception as e:
                    print(f"Eroare la comanda '{comanda}': {e}")


            elif c == 'undo':
                try:
                    undo()
                    print('Undo efectuat cu succes.')
                except ValueError as ve:
                    print(ve)

            elif c == 'print':
                tiparire(lista_participanti)

            else:
                print("Va rugam introduceti o comanda valida.")

