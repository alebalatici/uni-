from domain.specie import Specie
import datetime
class Service():
    def __init__(self, repo, val):
        self.__repo = repo
        self.__val = val

    def add_specie(self, id: int, nume: str, data: str, locatia: str, tip: str, lifespan: int):
        specie = Specie(id, nume, data, locatia, tip, lifespan)
        self.__val.validate(specie)
        self.__repo.add_specie(specie)

    def remove_specie(self, id: int, nume: str, data: str, locatia: str, tip: str, lifespan: int):
        specie = Specie(id, nume, data, locatia, tip, lifespan)
        self.__val.validate(specie)
        self.__repo.remove_specie(specie)

    def get_all_species(self):
        return self.__repo.get_all_species()

    def find_specie(self, id: int):
        return self.__repo.find_specie(id)

    def find_discoveries_by_date(self, data_str: str):
        species = []
        date = datetime.datetime.strptime(data_str, "%Y/%m/%d").date()
        for specie in self.get_all_species():
            if date > specie.data:
                species.append(specie)
        return species

    def statistics_by_type(self, tip: str):
        sum = 0
        total = 0
        species = []
        for specie in self.get_all_species():
            if specie.tip == tip:
                sum += specie.lifespan
                total += 1
                species.append(specie)

        species.sort(key= lambda specie: specie.data, reverse=True)
        media = sum / total
        return species[0], media
