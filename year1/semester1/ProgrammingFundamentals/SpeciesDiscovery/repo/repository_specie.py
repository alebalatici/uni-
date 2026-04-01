from domain.specie import Specie

class RepositoryException(Exception):
    def __init__(self, message):
        self.message = message

class SpecieDoesNotExist(RepositoryException):
    def __init__(self):
        self.message = "Specia nu exista"

class SpecieAlreadyExists(RepositoryException):
    def __init__(self):
        self.message = "Specia exista deja"

class Repository(object):
    def __init__(self):
        self.__specii = {}

    def add_specie(self, specie):
        if specie.id in self.__specii:
            raise SpecieAlreadyExists
        self.__specii[specie.id] = specie

    def remove_specie(self, specie):
        if specie.id not in self.__specii:
            raise SpecieDoesNotExist
        self.__specii.pop(specie.id)

    def find_specie(self, specie_id):
        if specie_id not in self.__specii:
            raise SpecieDoesNotExist
        return self.__specii[specie_id]

    def get_all_species(self):
        return list(self.__specii.values())

class RepositoryFile(Repository):
    def __init__(self, filename):
        self.__filename = filename
        super().__init__()
        self.__load_from_file()

    def __load_from_file(self):
        try:
            with open(self.__filename, mode="r", encoding="utf-8") as file:
                lines = file.readlines()
                for line in lines:
                    if line != "":
                        id, nume, data, locatia, tip, lifespan = line.split(", ")
                        id = int(id.strip())
                        nume = nume.strip()
                        data = data.strip()
                        locatia = locatia.strip()
                        tip = tip.strip()
                        lifespan = int(lifespan.strip())
                        specie = Specie(id, nume, data, locatia, tip, lifespan)
                        super().add_specie(specie)

        except IOError:
            print("File not found")

    def __save_to_file(self):
        with open(self.__filename, mode="w", encoding="utf-8") as file:
            for specie in super().get_all_species():
                specie_str = str(specie.id) + ", " + specie.nume + ", " + specie.data_str + ", " + specie.locatia + ", " + specie.tip + ", " + str(specie.lifespan) + "\n"
                file.write(specie_str)

    def add_specie(self, specie):
        super().add_specie(specie)
        self.__save_to_file()

    def remove_specie(self, specie):
        super().remove_specie(specie)
        self.__save_to_file()

    def find_specie(self, specie_id):
        return super().find_specie(specie_id)

    def get_all_species(self):
        return super().get_all_species()