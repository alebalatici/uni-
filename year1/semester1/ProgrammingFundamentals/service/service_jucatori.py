from domain.evolutie_jucator import *
from repository.repository_jucatori import *
class ServiceJucatori():
    def __init__(self, repo, val):
        self.__repo = repo
        self.__val = val

    def add_jucator(self, id_jucator, nume, echipa, pozitie, numar_puncte):
        jucator = Jucator(id_jucator, nume, echipa, pozitie, numar_puncte)
        self.__val.validate(jucator)
        self.__repo.add_jucator(jucator)

    def find_jucator(self, id_jucator):
        return self.__repo.find_jucator(id_jucator)

    def get_all_jucatori(self):
        return self.__repo.get_all_jucatori()

    def cautare_jucator_pozitie_echipa(self, pozitie, echipa, lista: list):
        ans = []
        for jucator in lista:
            if jucator.echipa == echipa and jucator.pozitie == pozitie:
                ans.append(jucator)
        return ans

    def get_average(self, id_jucator, nr_meciuri):
        jucator = self.__repo.find_jucator(id_jucator)
        return MVPCandidate(jucator, nr_meciuri)

