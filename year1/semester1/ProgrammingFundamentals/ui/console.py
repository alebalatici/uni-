class Console:
    def __init__(self, srv_jucator):
        self.srv_jucator = srv_jucator

    @staticmethod
    def print_menu():
        print("1. Cautare jucator dupa pozitie si nume echipa")
        print("2. Evaluare jucator pe sezon")
        print("3. Afiseaza toti jucatorii")
        print("4. Exit")

    # def evaluare_ui(self):
    #     try:
    #         id_jucator = int(input("ID jucator: "))
    #         nr_meciuri = int(input("Nr meciuri: "))
    #     except ValueError as e:
    #         print(f"Date invalide: {e}")

    def cautare_jucator_pozitie_echipa_ui(self, lista: list):
        pozitie = input("Introduceti la tastatura pozitia jucatorului: ")
        echipa = input("Introduceti la tastatura numele echipei din care face parte jucatorul: ")
        ans = self.srv_jucator.cautare_jucator_pozitie_echipa(pozitie, echipa, lista)
        self.tiparire_jucatori(ans)

    def get_points_average_ui(self):
        try:
            id_jucator = input("ID jucator: ")
            nr_meciuri = int(input("Nr meciuri: "))
            result = self.srv_jucator.get_average(id_jucator, nr_meciuri)
            print(result)
        except ValueError as e:
            print(f"Date invalide: {e}")

    def tiparire_jucatori(self, lista: list):
        if not lista:
            print("Lista este goala.")
        for jucator in lista:
            print(jucator)

    def run(self):
        while True:
            self.print_menu()
            optiune = input(">>>")
            match optiune:
                case "1":
                    self.cautare_jucator_pozitie_echipa_ui(self.srv_jucator.get_all_jucatori())
                case "2":
                    self.get_points_average_ui()
                case "3":
                    self.tiparire_jucatori(self.srv_jucator.get_all_jucatori())
                case "4":
                    break
                case _:
                    print("Date invalide")