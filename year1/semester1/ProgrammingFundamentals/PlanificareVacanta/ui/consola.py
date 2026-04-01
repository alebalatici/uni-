from service.service_vacanta import ServiceVacanta

class Consola:
    def __init__(self, srv_vacante):
        self.__srv_vacante = srv_vacante

    @staticmethod
    def print_menu():
        print("1. Cauta vacanta dupa string")
        print("2. Rezerva o vacanta")
        print("3. Afiseaza toate vacantele")
        print("4. Exit")

    def tiparire_vacante(self, list):
        if not list:
            print("Lista este goala")
        for vacanta in list:
            print(vacanta)

    def cautare_dupa_string_ui(self, lista: dict):
        string = input("Cauta vacantele de tipul: ")
        sir = self.__srv_vacante.cautare_vacante_dupa_tip(string, lista)
        self.tiparire_vacante(sir)

    def get_number_of_days_ui(self):
        try:
            id_locatie = int(input("Introdu id-ul locatiei pe care doresti sa o cauti: "))
            buget = int(input("Introdu bugetul tau: "))
            result = self.__srv_vacante.get_number_of_days_service(id_locatie, buget)
            print(result)
        except ValueError as e:
            print(f"Date invalide: {e}")

    def run(self):
        while True:
            self.print_menu()
            optiune = input("Va rugam introduceti o optiune: ")
            match optiune:
                case "1":
                    self.cautare_dupa_string_ui(self.__srv_vacante.get_all_vacante())
                case "2":
                    self.get_number_of_days_ui()
                case "3":
                    self.tiparire_vacante(self.__srv_vacante.get_all_vacante())
                case "4":
                    break
                case _:
                    print("Va rugam introduceti o optiune valida")
