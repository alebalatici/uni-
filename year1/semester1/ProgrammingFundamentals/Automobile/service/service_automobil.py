from domain.automobil import Automobil
from repository.repository_automobil import RepositoryError
import copy
import datetime
class ServiceError(Exception):
    def __init__(self, message):
        self.message = message

class ServiceAutomobil:
    def __init__(self, repo):
        self.__repo = repo
        self.__undo_stack = []

    def add_automobil(self, id: int, marca: str, pret: int, model: str, data_str: str):
        """
        Adauga un automobil in lista de automobile
        :param id: ID-ul automobilului de adaugat
        :param marca: Marca automobilului de adaugat
        :param pret: Pretul automobilului de adaugat
        :param model: Modelul automobilului de adaugat
        :param data: Data
        :raises: RepositoryError daca exista deja un automobil cu acel id
        """
        try:
            self.__undo_stack.append(copy.deepcopy(self.__repo.get_state()))
            automobil = Automobil(id, marca, pret, model, data_str)
            self.__repo.add_automobil(automobil)
        except RepositoryError as e:
            raise ServiceError(e.message)

    def remove_automobil(self, id: int):
        """
        Sterge un automobil din lista de automobile
        :param id: ID-ul automobilului de sters
        :raises: RepositoryError daca nu exista un automobil cu acel id
        """
        try:
            #self.__undo_stack.append(copy.deepcopy(self.__repo.get_state()))
            self.__repo.remove_automobil(id)

        except RepositoryError as e:
            raise ServiceError(e.message)

    def find_automobil(self, id: int):
        """
        Cauta un automobil cu ID-ul precizat
        :param id: ID-ul de cautat
        :raises: RepositoryError daca exista un automobil cu acel id
        """
        try:
            return self.__repo.find_automobil(id)

        except RepositoryError as e:
            raise ServiceError(e.message)

    def get_all_automobile(self):
        return self.__repo.get_all_automobile()

    def digit_in_number(self, digit: int, number: int):
        """
        Verifica daca o cifra este intr-un numar
        :param digit: Cifra
        :param number: Numarul
        :return: True/False daca este/nu este in numar
        """
        if digit == 0 and number == 0:
            return True
        if number < 0:
            number = -number

        while number > 0:
            cif = number % 10
            if cif == digit:
                return True
            number //= 10

        return False

    def delete_all_autos_with_digit_in_price(self, cifra, list):
        """
        Sterge toate automobilele care contin in pretul lor cifra data
        :param cifra: Cifra dupa care se fac stergerile
        :param list: Lista de automobil
        :return:
        """
        self.__undo_stack.append(copy.deepcopy(self.__repo.get_state()))
        nr_automobile_sterse = 0
        for masina in list:
            if self.digit_in_number(cifra, masina.pret) == True:
                self.remove_automobil(masina.id)
                nr_automobile_sterse += 1
        return nr_automobile_sterse

    def undo(self):
        """
        Se face undo la ultima operatie efectuata
        :return: ServiceError daca nu exista operatii la care sa se faca undo
        """
        if not self.__undo_stack:
            raise ServiceError("Nu exista operatii la care sa se faca undo")
        else:
            self.__repo.set_state(self.__undo_stack.pop())

    def filter_by_text(self, text: str, lista: list):
        """
        Returneaza masinile din lista care contin in denumirea marcii textul dat
        :param text: Un sir de caractere dupa care se va face cautarea
        :param lista: Lista in care se va face cautarea
        :return: Lista filtrata
        """
        if text == "":
            return lista
        else:
            lista_filtrata = []
            for masina in lista:
                if text in masina.marca:
                    lista_filtrata.append(masina)
            return lista_filtrata

    def filter_by_price(self, price: int, lista: list):
        """
        Filtreaza lista dupa pret (Adauga doar masinile care au pretul mai mic decat price)
        :param price: Pretul dupa care se filtreaza
        :param lista: Lista in care se face filtrarea
        :return: Lista filtrata
        """
        if price == -1:
            return lista
        else:
            lista_filtrata = []
            for masina in lista:
                if price > masina.pret:
                    lista_filtrata.append(masina)
            return lista_filtrata

    def verify_if_expired(self, masina: Automobil):
        """
        Verifica daca data in care trebuia sa aibe inspectia tehnica a expirat sau nu
        :param masina: Masina pentru care se verifica daca inspectia tehnica a expirat sau nu
        :return: True/False daca inspectia tehnica a expirat sau nu a expirat
        """
        date_today = datetime.date.today()
        return masina.data < date_today