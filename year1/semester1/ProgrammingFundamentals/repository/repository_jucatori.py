from domain.jucator import Jucator
class RepositroryException(Exception):
    def __innit__(self, message):
        super().__init__(message)

class JucatorulNuExista(RepositroryException):
    def __init__(self):
        super().__init__("Jucatorul nu exista")

class JucatorulExistaDeja(RepositroryException):
    def __init__(self):
        super().__init__("Jucatorul exista deja")

class RepositoryJucatorMemory:
    def __init__(self):
        self.__jucatori = {}

    def add_jucator(self, jucator: Jucator):
        if jucator.id_jucator in self.__jucatori:
            raise JucatorulExistaDeja()
        self.__jucatori[jucator.id_jucator] = jucator

    def find_jucator(self, id):
        if id not in self.__jucatori:
            raise JucatorulNuExista()
        return self.__jucatori[id]

    def get_all_jucatori(self):
        return self.__jucatori.values()

class RepositoryJucatorFile(RepositoryJucatorMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        try:
            with open(self.__filename, mode="r", encoding="utf8") as file:
                lines = file.readlines()
                for line in lines:
                    if line:
                        id_jucator, nume, echipa, pozitie, numar_puncte = line.split(',')
                        id_jucator = id_jucator.strip()
                        nume = nume.strip()
                        echipa = echipa.strip()
                        pozitie = pozitie.strip()
                        numar_puncte = int(numar_puncte.strip())
                        jucator = Jucator(id_jucator, nume, echipa, pozitie, numar_puncte)
                        super().add_jucator(jucator)
        except IOError:
            print("File not found")

    def __save_to_file(self):
        try:
            with open(self.__filename, mode="w", encoding="utf8") as file:
                jucatori = super().get_all_jucatori()
                for jucator in jucatori:
                    jucator_str = jucator.id_jucator + ', ' + jucator.nume + ', ' + jucator.echipa + ', ' + jucator.pozitie + ', ' + str(jucator.numar_puncte) + '\n'
                    file.write(jucator_str)
        except IOError:
            print("File not found")

    def add_jucator(self, jucator: Jucator):
        super().add_jucator(jucator)
        self.__save_to_file()

    def find_jucator(self, id):
        return super().find_jucator(id)

    def get_all_jucatori(self):
        return super().get_all_jucatori()