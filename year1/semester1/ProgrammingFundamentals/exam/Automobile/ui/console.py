from service.service_automobil import ServiceError

class Console:
    def __init__(self, srv):
        self.__srv = srv

    @staticmethod
    def print_menu():
        print("1. Adauga un automobil")
        print("2. Sterge automobilele care contin cifra data")
        print("3. Filtreaza automobilele in functie de anumite criterii")
        print("4. Undo la ultima operatie")
        print("5. Afiseaza toate automobilele")
        print("6. Exit")

    def afiseaza_toate_masinile(self, lista: list):
        if not lista:
            print("Lista este goala")
        else:
            for masina in lista:
                print(masina)

    def add_masina_ui(self):
        try:
            id = int(input("Introduceti ID-ul masinii de adaugat: "))
            marca = input("Introduceti marca masinii de adaugat: ")
            pret = int(input("Introduceti pretul masinii de adaugat: "))
            model = input("Introduceti modelul masinii de adaugat: ")
            data = input("Introduceti data la care expira inspectia tehnica periodica (formatul este zi/luna/an): ")
            self.__srv.add_automobil(id, marca, pret, model, data)
            print("Masina adaugata cu succes")
        except ValueError as e:
            print(f"Eroare: {e}")

        except ServiceError as e:
            print(f"Eroare: {e}")

    def remove_masina_ui(self):
        try:
            cifra = int(input("Introduceti cifra masinii dupa care se va face stergerea: "))
            nr_automobile_sterse = 0
            for masina in self.__srv.get_all_automobile():
                if self.__srv.digit_in_number(cifra, masina.pret) == True:
                    self.__srv.remove_automobil(masina.id)
                    nr_automobile_sterse += 1
            print(f"Au fost sterse: {nr_automobile_sterse} masini")
        except ValueError as e:
            print(f"Eroare: {e}")

    def remove_masina_ui1(self, lista: list):
        try:
            cifra = int(input("Introduceti cifra masinii dupa care se va face stergerea: "))
            nr_automobile_sterse = self.__srv.delete_all_autos_with_digit_in_price(cifra, lista)
            print(f"Au fost sterse: {nr_automobile_sterse} masini")
        except ValueError as e:
            print(f"Eroare: {e}")

    def undo_ui(self):
        try:
            self.__srv.undo()
        except ServiceError as e:
            print(f"Eroare: {e}")

    def filtrare_ui(self, filtru_text, filtru_numar, list):
        try:
            print(f"Filtru curent este: {filtru_text}, {filtru_numar}")
            filtru_text = input("Introduceti un sir da caractere dupa care sa se filtreze lista: ")
            filtru_numar = int(input("introduceti un numar dupa care sa se filtreze lista: "))
            print(f"Nout filtru este: filtru marca =  {filtru_text}, filtru pret = {filtru_numar}")
            return filtru_text, filtru_numar
        except ValueError as e:
            print(f"Eroare: {e}")

    def afiseaza_toate_masininile_expired(self, list):
        for masina in list:
            if self.__srv.verify_if_expired(masina) == True:
                print(f"ID: {masina.id} | Marca: *{masina.marca} | Pret: {masina.pret} | Model: {masina.model} | Data: {masina.data_str}")
            else:
                print(masina)

    def print_by_filter(self, filtru_text, filtru_numar, lista: list):
        print(f"Filtru curent este: filtru marca =  {filtru_text}, filtru pret = {filtru_numar}")
        filtrare_dupa_text = self.__srv.filter_by_text(filtru_text, lista)
        filtrare_dupa_ambele = self.__srv.filter_by_price(filtru_numar, filtrare_dupa_text)
        self.afiseaza_toate_masininile_expired(filtrare_dupa_ambele)

    def run(self):
        filtru_text = ""
        filtru_numar = -1
        while True:
            self.print_by_filter(filtru_text, filtru_numar, self.__srv.get_all_automobile())
            self.print_menu()
            try:
                optiune = int(input("Introduceti o optiune: "))
                match optiune:
                    case 1:
                        self.add_masina_ui()
                    case 2:
                        self.remove_masina_ui1(self.__srv.get_all_automobile())
                    case 3:
                        filtru_text, filtru_numar = self.filtrare_ui(filtru_text, filtru_numar, self.__srv.get_all_automobile())
                    case 4:
                        self.undo_ui()
                    case 5:
                        self.afiseaza_toate_masinile(self.__srv.get_all_automobile())
                    case 6:
                        print("Iesire...")
                        break

            except ValueError as e:
                print(f"Eroare: {e}")