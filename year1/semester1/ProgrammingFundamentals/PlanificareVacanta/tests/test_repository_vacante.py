import unittest
from repository.repository_vacanta import *

class TestRepositoryVacanta(unittest.TestCase):
    def setUp(self):
        print("setUp")
        self.__repo_vacante = RepositoryVacantaMemory()

    def tearDown(self):
        print("tearDown")

    def test_add_vacanta(self):
        n = len(self.__repo_vacante.get_all_vacante())
        vacanta1 = Vacanta(1, "Hotel Belvedere", "mare all-inclusive", 500)
        self.__repo_vacante.add_vacanta(vacanta1)
        self.assertEqual(len(self.__repo_vacante.get_all_vacante()), n + 1)

        vacanta2 = Vacanta(2, "Casa Dunarea", "mare all-inclusive", 200)
        self.__repo_vacante.add_vacanta(vacanta2)
        self.assertEqual(len(self.__repo_vacante.get_all_vacante()), n + 2)

        vacanta3 = Vacanta(3, "Hotel Belvedere", "munte drumetie", 400)
        self.__repo_vacante.add_vacanta(vacanta3)
        self.assertEqual(len(self.__repo_vacante.get_all_vacante()), n + 3)

        vacanta4 = Vacanta(1, "sjklf", "adsjf", 700)
        with self.assertRaises(VacantaAlreadyExists):
            self.__repo_vacante.add_vacanta(vacanta4)

    def test_get_all_vacante(self):
        vacanta1 = Vacanta(1, "Hotel Belvedere", "mare all-inclusive", 500)
        self.__repo_vacante.add_vacanta(vacanta1)
        vacanta2 = Vacanta(2, "Casa Dunarea", "mare all-inclusive", 200)
        self.__repo_vacante.add_vacanta(vacanta2)
        vacanta3 = Vacanta(3, "Hotel Belvedere", "munte drumetie", 400)
        self.__repo_vacante.add_vacanta(vacanta3)
        self.assertEqual(len(self.__repo_vacante.get_all_vacante()), 3)

    def test_find_vacanta(self):
        vacanta1 = Vacanta(1, "Hotel Belvedere", "mare all-inclusive", 500)
        self.__repo_vacante.add_vacanta(vacanta1)
        vacanta2 = Vacanta(2, "Casa Dunarea", "mare all-inclusive", 200)
        self.__repo_vacante.add_vacanta(vacanta2)
        vacanta3 = Vacanta(3, "Hotel Belvedere", "munte drumetie", 400)
        self.__repo_vacante.add_vacanta(vacanta3)

        vacanta = self.__repo_vacante.find_vacanta(1)
        self.assertEqual(vacanta, vacanta1)
        with self.assertRaises(VacantaDoesNotExist):
            self.__repo_vacante.find_vacanta(4)

class TestRepositoryVacantaFile(unittest.TestCase):
    def setUp(self):
        print("setUp")
        self.__repo_vacante = RepositoryVacantaFile("tests/test_vacante.txt")

    def tearDown(self):
        print("tearDown")
        with open("tests/test_vacante.txt", "w") as file:
            fisier_default = open("tests/vacante_default.txt", "r")
            continut = fisier_default.read()
            fisier_default.close()
            file.write(continut)

    def test_add_vacanta(self):
        n = len(self.__repo_vacante.get_all_vacante())
        vacanta1 = Vacanta(n + 1, "Hotel Belvedere", "mare all-inclusive", 500)
        self.__repo_vacante.add_vacanta(vacanta1)
        self.assertEqual(len(self.__repo_vacante.get_all_vacante()), n + 1)

        vacanta2 = Vacanta(n + 2, "Casa Dunarea", "mare all-inclusive", 200)
        self.__repo_vacante.add_vacanta(vacanta2)
        self.assertEqual(len(self.__repo_vacante.get_all_vacante()), n + 2)

        vacanta3 = Vacanta(n + 3, "Hotel Belvedere", "munte drumetie", 400)
        self.__repo_vacante.add_vacanta(vacanta3)
        self.assertEqual(len(self.__repo_vacante.get_all_vacante()), n + 3)

        vacanta4 = Vacanta(1, "sjklf", "adsjf", 700)
        with self.assertRaises(VacantaAlreadyExists):
             self.__repo_vacante.add_vacanta(vacanta4)

    def test_find_vacanta(self):
        vacanta = self.__repo_vacante.find_vacanta(1)
        vacanta1 = Vacanta(1,  "Hotel Blue Wave", "mare all-inclusive", 450)
        self.assertEqual(vacanta, vacanta1)
        with self.assertRaises(VacantaDoesNotExist):
            self.__repo_vacante.find_vacanta(200)

    def test_get_all_vacante(self):
        n = len(self.__repo_vacante.get_all_vacante())
        self.assertEqual(n, 10)

if __name__ == '__main__':
    unittest.main()
