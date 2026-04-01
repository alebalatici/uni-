import unittest
from repository.repository_automobil import RepositoryFile
from service.service_automobil import ServiceAutomobil
from domain.automobil import Automobil
class TestService(unittest.TestCase):
    def setUp(self):
        print("setUp")
        repo = RepositoryFile("tests/test_automobile.txt")
        self.__srv = ServiceAutomobil(repo)

    def tearDown(self):
        with open("tests/test_automobile.txt", mode="w", encoding="utf-8") as file:
            fisier_default = open("tests/default_automobile.txt", mode="r", encoding="utf-8")
            content = fisier_default.read()
            file.write(content)
            fisier_default.close()

    def test_add_automobil(self):
        n = len(self.__srv.get_all_automobile())
        self.__srv.add_automobil(n + 1, "Renault", 20000, "dsnoidn", "14/05/2025")
        list = self.__srv.get_all_automobile()
        self.assertEqual(len(list), n + 1)

    def test_remove_automobil(self):
        n = len(self.__srv.get_all_automobile())
        self.__srv.remove_automobil(1)
        self.assertEqual(len(self.__srv.get_all_automobile()), n - 1)

    def test_find_automobil(self):
        automobil = self.__srv.find_automobil(1)
        self.assertEqual(automobil.id, 1)
        self.assertEqual(automobil.marca, "Lamborghini")
        self.assertEqual(automobil.pret, 100000)
        self.assertEqual(automobil.model, "Urus")
        self.assertEqual(automobil.data_str, "10/10/2020")

    def test_get_all_automobile(self):
        n = len(self.__srv.get_all_automobile())
        self.assertEqual(n, 10)
        self.__srv.remove_automobil(1)
        self.assertEqual(len(self.__srv.get_all_automobile()), 9)

    def test_digit_in_number(self):
        self.assertEqual(self.__srv.digit_in_number(1, 1), True)
        self.assertEqual(self.__srv.digit_in_number(1, 3454651), True)
        self.assertEqual(self.__srv.digit_in_number(1, 234567), False)
        self.assertEqual(self.__srv.digit_in_number(0, 0), True)
        self.assertEqual(self.__srv.digit_in_number(1, 0), False)
        self.assertEqual(self.__srv.digit_in_number(1, -12), True)

    def test_delete_all_autos_with_digit_in_price(self):
        n = len(self.__srv.get_all_automobile())
        numere = self.__srv.delete_all_autos_with_digit_in_price(1, self.__srv.get_all_automobile())
        self.assertEqual(numere, 4)
        self.assertEqual(len(self.__srv.get_all_automobile()), n - 4)

    def test_undo(self):
        n = len(self.__srv.get_all_automobile())
        numere = self.__srv.delete_all_autos_with_digit_in_price(1, self.__srv.get_all_automobile())
        self.assertEqual(len(self.__srv.get_all_automobile()), n - 4)
        self.__srv.undo()
        self.assertEqual(len(self.__srv.get_all_automobile()), n)
        n = len(self.__srv.get_all_automobile())
        self.__srv.add_automobil(n + 1, "Renault", 20000, "dsnoidn", "14/05/2025")
        self.assertEqual(len(self.__srv.get_all_automobile()), n + 1)
        self.__srv.undo()
        self.assertEqual(len(self.__srv.get_all_automobile()), n)

    def test_filter_by_text(self):
        list = self.__srv.filter_by_text("B", self.__srv.get_all_automobile())
        self.assertEqual(len(list), 3)

    def test_filter_by_price(self):
        list = self.__srv.filter_by_price(40000, self.__srv.get_all_automobile())
        self.assertEqual(len(list), 3)

    def test_verify_if_expired(self):
        n = len(self.__srv.get_all_automobile())
        masina = Automobil(n + 2, "Renault", 20000, "dsnoidn", "14/05/2026")
        self.assertEqual(self.__srv.verify_if_expired(masina), False)
        masina1 = Automobil(n + 3, "Renault", 20000, "dsnoidn", "14/05/2020")
        self.assertEqual(self.__srv.verify_if_expired(masina1), True)

if __name__ == '__main__':
    unittest.main()