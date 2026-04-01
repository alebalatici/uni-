from repository.repository_vacanta import *
from domain.rezervare import *
class ServiceVacanta:
    def __init__(self, repo, val):
        self.__repo = repo
        self.__val = val

    def add_vacanta(self, id: int, denumire: str, tip: str, pret: int):
        """
        Adauga o noua vacanta
        :param id: ID-ul vacantei de adaugat
        :param denumire: Denumirea vacantei
        :param tip: Tipul vacantei
        :param pret: Pretul Vacantei
        """
        vacanta = Vacanta(id, denumire, tip, pret)
        self.__val.validate(vacanta)
        self.__repo.add_vacanta(vacanta)

    def find_vacanta(self, id: int) -> Vacanta:
        """
        Cauta o vacanta in lista de vacante
        :param id: ID-ul vacantei de cautat
        :return: Vacanta gasita
        """
        return self.__repo.find_vacanta(id)

    def get_all_vacante(self):
        """
        :return: intreaga lista de vacante
        """
        return self.__repo.get_all_vacante()

    def cautare_vacante_dupa_tip(self, string_cautare: str, lista: dict):
        """
        Cauta in lista de vacante toate vacantele care contine in tip un cuvant din stringu-ul de cautare
        :param string_cautare: stringul pe care il vom cauta
        :return: lista de vacante
        """
        sir = []
        cuvinte = string_cautare.split()
        for cuvant in cuvinte:
            for vacanta in lista:
                if cuvant in vacanta.tip:
                    sir.append(vacanta)
        return sir

    def get_number_of_days_service(self, id_locatie, buget: int):
        """
        Returneaza numarul de zile pentru care un utilizator poate sta la o locatie
        :return: numarul de zile
        """
        vacanta = self.find_vacanta(id_locatie)
        result = BookingInquiry(vacanta, buget)
        return result

