class Consola():
    def __init__(self, srv):
        self.__srv = srv

    @staticmethod
    def afisare_meniu():
        print("1. Afiseaza toate speciile care au fost descoperite inainte o data")
        print("2. Statistici in functie de tip")
        print("3. Afiseaza toate speciile din baza de date")
        print("4. Exit")

    def afisare_specii(self, lista: list):
        if not lista:
            print("Lista este goala.")
        else:
            for element in lista:
                print(element)

    def find_discoveries_by_date_ui(self):
        try:
            an = int(input("Introduceti anul: "))
            luna = int(input("Introduceti luna: "))
            zi = input("Introduceti zi: ")
            data_str = str(an) + "/" + str(luna) + "/" + str(zi)
            species = self.__srv.find_discoveries_by_date(data_str)
            print(f"Speciile descoperite inainte de {data_str} sunt: ")
            self.afisare_specii(species)

        except ValueError as e:
            print(f"Eroare: {e}")

    def statistics_by_type_ui(self):
        type = input("Intruduceti un tip (ex: mammal, bird, reptile): ")
        specie, media = self.__srv.statistics_by_type(type)
        print(f"Cea mai recent descoperita specie de {type} este: {specie}" )
        print(f"Media duratei de viata a speciilor de tipul {type} este: {media}")

    def run(self):
        while True:
            self.afisare_meniu()
            optiune = input("Va rugam alegeti o optiune: ")
            match optiune:
                case "1":
                    self.find_discoveries_by_date_ui()
                case "2":
                    self.statistics_by_type_ui()
                case "3":
                    self.afisare_specii(self.__srv.get_all_species())
                case "4":
                    print("Iesire...")
                    break
                case _:
                    print("Va rugam alegeti o optiune valida")
