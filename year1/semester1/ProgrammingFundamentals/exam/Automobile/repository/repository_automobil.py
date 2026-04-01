from domain.automobil import Automobil
class RepositoryError(Exception):
    def __init__(self, message):
        self.message = message

class AutomobilAlreadyExists(RepositoryError):
    def __init__(self):
        super().__init__("Automobilul exista deja")

class AutomobilDoesNotExists(RepositoryError):
    def __init__(self):
        super().__init__("Automobilul nu exista")

class Repository:
    def __init__(self):
        self.__automobile = {}

    def add_automobil(self, automobil: Automobil):
        """
        Adauga un automobil la lista de automobile
        :param automobil: Automobilul de adaugat
        :raises: RepositoryError daca automobilul exista deja
        """
        if automobil.id in self.__automobile:
            raise AutomobilAlreadyExists()
        self.__automobile[automobil.id] = automobil

    def remove_automobil(self, key: int):
        """
        Sterge un automobil din lista de automobile in functie de key (id)
        :param key: ID-ul automobilului de sters
        :return: RepositoryError daca automobilul nu exista
        """
        if key not in self.__automobile:
            raise AutomobilDoesNotExists()
        del self.__automobile[key]

    def find_automobil(self, key: int):
        """
        Cauta un automobil in lista de automobile
        :param key: ID-ul automobilului de cautat
        :return: RepositoryError daca automobilul nu exista
        """
        if key not in self.__automobile:
            raise AutomobilDoesNotExists()
        return self.__automobile[key]

    def get_all_automobile(self):
        """
        Returneaza toate automobilele sub forma de lista
        :return: Toate automobilele sub forma de lista
        """
        return list(self.__automobile.values())

    def get_state(self):
        """
        Returneaza state-ul actual al dictionarului de automobile
        """
        return self.__automobile

    def set_state(self, state):
        """
        Seteaza state-ul actual al dictionarului de automobile
        :param state: State-ul cu care va fi setat
        """
        self.__automobile = state

class RepositoryFile(Repository):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        """
        Descarca datele din fisier in aplicatie
        """
        try:
            with open(self.__filename, mode="r", encoding="utf-8") as file:
                lines = file.readlines()
                for line in lines:
                    if line:
                        id, marca, pret, model, data_str = line.split(", ")
                        id = int(id.strip())
                        marca = marca.strip()
                        pret = int(pret.strip())
                        model = model.strip()
                        data_str = data_str.strip()
                        automobil = Automobil(id, marca, pret, model, data_str)
                        super().add_automobil(automobil)

        except IOError:
            print("File not found")

    def __save_to_file(self):
        """
        Salveaza tate automobilele in fisier
        """
        with open(self.__filename, mode="w", encoding="utf-8") as file:
            for automobil in super().get_all_automobile():
                automobil_str = str(automobil.id) + ", " + automobil.marca + ", " + str(automobil.pret) + ", " + automobil.model + ", " + automobil.data_str + "\n"
                file.write(automobil_str)

    def add_automobil(self, automobil):
        """
        Adauga un automobil la lista de automobile
        :param automobil: Automobilul de adaugat
        :raises: RepositoryError daca automobilul exista deja
        """
        super().add_automobil(automobil)
        self.__save_to_file()

    def remove_automobil(self, key):
        super().remove_automobil(key)
        self.__save_to_file()

    def find_automobil(self, key):
        return super().find_automobil(key)

    def get_all_automobile(self):
        return super().get_all_automobile()

    def get_state(self):
        return super().get_state()

    def set_state(self, state):
        super().set_state(state)
        self.__save_to_file()