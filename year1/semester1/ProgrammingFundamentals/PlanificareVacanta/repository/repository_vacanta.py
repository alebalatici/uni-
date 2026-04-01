from domain.vacanta import Vacanta

class RepositoryException(Exception):
    def __init__(self, message):
        self.message = message

class VacantaDoesNotExist(RepositoryException):
    def __init__(self):
        self.message = "Vacanta cautata nu exista"

class VacantaAlreadyExists(RepositoryException):
    def __init__(self):
        self.message = "Vacanta exista deja"

class RepositoryVacantaMemory:
    def __init__(self):
        self.__vacante = {}

    def add_vacanta(self, vacanta: Vacanta):
        """
        Adauga o noua vacanta noua listei de vacante
        :param vacanta: vacanta de adaugat
        """
        if vacanta.id_locatie in self.__vacante:
            raise VacantaAlreadyExists()
        self.__vacante[vacanta.id_locatie] = vacanta

    def find_vacanta(self, id_vacanta: int) -> Vacanta:
        """
        Cauta o vacanta in lista de vacante in functie de id
        :param id_vacanta: ID-ul vacantei de cautat
        :return: vacanta cu ID-ul id_vacanta
        """
        if id_vacanta not in self.__vacante:
            raise VacantaDoesNotExist()
        return self.__vacante[id_vacanta]

    def get_all_vacante(self):
        """
        Returneaza intreaga lista de vacante
        :return: intreaga lista de vacante
        """
        return self.__vacante.values()

class RepositoryVacantaFile(RepositoryVacantaMemory):
    def __init__(self, filename):
        self.__filename = filename
        super().__init__()
        self.__load_from_file()

    def __load_from_file(self):
        """
        Citeste din fisier si incarca datele in memorie
        """
        try:
            with open(self.__filename, mode= "r", encoding="utf-8") as file:
                lines = file.readlines()
                for line in lines:
                    if line:
                        locatie_id, denumire, tip, pret = line.split(", ")
                        locatie_id = int(locatie_id.strip())
                        denumire = denumire.strip()
                        tip = tip.strip()
                        pret = int(pret.strip())
                        vacanta = Vacanta(locatie_id, denumire, tip, pret)
                        super().add_vacanta(vacanta)
        except IOError:
            print("Fisierul nu a fost gasit")

    def __save_to_file(self):
        """
        Salveaza datele din memorie in fisier
        """
        with open(self.__filename, mode= "w", encoding="utf-8") as file:
            for vacanta in super().get_all_vacante():
                str_vacanta = str(vacanta.id_locatie) + ', ' + vacanta.denumire + ', ' + vacanta.tip + ', ' + str(vacanta.pret_pe_zi) + '\n'
                file.write(str_vacanta)

    def add_vacanta(self, vacanta: Vacanta):
        """
        Adauga o noua vacanta
        :param vacanta: vacanta de adaugat
        """
        super().add_vacanta(vacanta) 
        self.__save_to_file()

    def find_vacanta(self, id_vacanta: int) -> Vacanta:
        """
        Cauta o vacanta dupa ID
        :param id_vacanta: ID-ul vacantei de cautat
        :return: vacanta gasita
        """
        return super().find_vacanta(id_vacanta)

    def get_all_vacante(self):
        """
        Returneaza intreaga lista de vacante
        :return: intreaga lista de vacante
        """
        return super().get_all_vacante()
