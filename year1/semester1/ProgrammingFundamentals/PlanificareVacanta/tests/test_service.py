from service.service_vacanta import ServiceVacanta
from domain.validator import Validator
from repository.repository_vacanta import *
import unittest
from domain.rezervare import *
class TestServiceVacanta(unittest.TestCase):
    def setUp(self):
        val = Validator()
        repo = RepositoryVacantaFile("tests/test_vacante.txt")
        self.__srv_vacante = ServiceVacanta(repo, val)

    def tearDown(self):
        print("tearDown")
        with open("tests/test_vacante.txt", "w") as file:
            fisier_default = open("tests/vacante_default.txt", "r")
            continut = fisier_default.read()
            fisier_default.close()
            file.write(continut)

    def test_add_vacanta(self):
        n = len(self.__srv_vacante.get_all_vacante())
        self.__srv_vacante.add_vacanta(n + 1, "Hotel Belvedere", "mare all-inclusive", 500)
        self.assertEqual(len(self.__srv_vacante.get_all_vacante()), n + 1)

        self.__srv_vacante.add_vacanta(n + 2, "Casa Dunarea", "mare all-inclusive", 200)
        self.assertEqual(len(self.__srv_vacante.get_all_vacante()), n + 2)

        self.__srv_vacante.add_vacanta(n + 3, "Hotel Belvedere", "munte drumetie", 400)
        self.assertEqual(len(self.__srv_vacante.get_all_vacante()), n + 3)

        with self.assertRaises(VacantaAlreadyExists):
             self.__srv_vacante.add_vacanta(1, "sjklf", "adsjf", 700)

    def test_find_vacanta(self):
        vacanta = self.__srv_vacante.find_vacanta(1)
        vacanta1 = Vacanta(1, "Hotel Blue Wave", "mare all-inclusive", 450)
        self.assertEqual(vacanta, vacanta1)
        with self.assertRaises(VacantaDoesNotExist):
            self.__srv_vacante.find_vacanta(200)

    def test_get_all_vacante(self):
        n = len(self.__srv_vacante.get_all_vacante())
        self.assertEqual(n, 10)

    def test_cautare_vacante_dupa_tip(self):
        sir = self.__srv_vacante.cautare_vacante_dupa_tip("mare", self.__srv_vacante.get_all_vacante())
        # for s in sir:
        #     print(s)
        self.assertEqual(len(sir), 3)
        sir1 = self.__srv_vacante.cautare_vacante_dupa_tip("mare munte", self.__srv_vacante.get_all_vacante())
        self.assertEqual(len(sir1), 5)
        sir3 =  self.__srv_vacante.cautare_vacante_dupa_tip("mare munte oras", self.__srv_vacante.get_all_vacante())
        self.assertEqual(len(sir3), 6)

    def test_get_number_of_days(self):
        #vacanta = self.__srv_vacante.find_vacanta(1)
        #result = BookingInquiry(vacanta, 1000)
        result = self.__srv_vacante.get_number_of_days_service(1, 1000)
        self.assertEqual(result.get_number_of_days(), 2)
        result = self.__srv_vacante.get_number_of_days_service(1, 1500)
        self.assertEqual(result.get_number_of_days(), 3)
        result = self.__srv_vacante.get_number_of_days_service(2, 1000)
        self.assertEqual(result.get_number_of_days(), 3)

if __name__ == '__main__':
    unittest.main()