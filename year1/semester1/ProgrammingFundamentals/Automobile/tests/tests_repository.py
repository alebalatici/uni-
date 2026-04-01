import unittest
from repository.repository_automobil import Repository, RepositoryFile
from domain.automobil import Automobil
class TestRepository(unittest.TestCase):
    def setUp(self):
        print("setUp")
        self.__repo = Repository()

    def tearDown(self):
        print("tearDown")

    def test_add_automobil(self):
        n = len(self.__repo.get_all_automobile())
        automobil = Automobil(n, "Renault", 20000, "dsnoidn", "14/05/2025")
        self.__repo.add_automobil(automobil)
        list = self.__repo.get_all_automobile()
        self.assertEqual(len(list), n + 1)

    def test_remove_automobil(self):
        n = len(self.__repo.get_all_automobile())
        automobil = Automobil(n, "Renault", 20000, "dsnoidn", "14/05/2025")
        self.__repo.add_automobil(automobil)
        list = self.__repo.get_all_automobile()
        self.assertEqual(len(list), n + 1)
        self.__repo.remove_automobil(automobil.id)
        list = self.__repo.get_all_automobile()
        self.assertEqual(len(list), n)

    def test_find_automobil(self):
        n = len(self.__repo.get_all_automobile())
        automobil = Automobil(n, "Renault", 20000, "dsnoidn", "14/05/2025")
        self.__repo.add_automobil(automobil)
        auto = self.__repo.find_automobil(n)
        self.assertEqual(auto.id, n)
        self.assertEqual(auto.marca, "Renault")
        self.assertEqual(auto.pret, 20000)
        self.assertEqual(auto.model, "dsnoidn")
        self.assertEqual(auto.data_str, "14/05/2025")

    def test_get_all_automobile(self):
        n = len(self.__repo.get_all_automobile())
        automobil = Automobil(n, "Renault", 20000, "dsnoidn", "14/05/2025")
        self.__repo.add_automobil(automobil)
        m = len(self.__repo.get_all_automobile())
        self.assertEqual(m, n + 1)

class TestRepositoryFile(unittest.TestCase):
    def setUp(self):
        print("setUp")
        self.__repo = RepositoryFile("tests/test_automobile.txt")

    def tearDown(self):
        with open("tests/test_automobile.txt", mode="w", encoding="utf-8") as file:
            fisier_default = open("tests/default_automobile.txt", mode="r", encoding="utf-8")
            content = fisier_default.read()
            file.write(content)
            fisier_default.close()

    def test_add_automobil(self):
        n = len(self.__repo.get_all_automobile())
        automobil = Automobil(n + 1, "Renault", 20000, "dsnoidn", "14/05/2025")
        self.__repo.add_automobil(automobil)
        list = self.__repo.get_all_automobile()
        self.assertEqual(len(list), n + 1)

    def test_remove_automobil(self):
        n = len(self.__repo.get_all_automobile())
        self.__repo.remove_automobil(1)
        self.assertEqual(len(self.__repo.get_all_automobile()), n - 1)

    def test_find_automobil(self):
        automobil = self.__repo.find_automobil(1)
        self.assertEqual(automobil.id, 1)
        self.assertEqual(automobil.marca, "Lamborghini")
        self.assertEqual(automobil.pret, 100000)
        self.assertEqual(automobil.model, "Urus")
        self.assertEqual(automobil.data_str, "10/10/2020")

    def test_get_all_automobile(self):
        n = len(self.__repo.get_all_automobile())
        self.assertEqual(n, 10)
        self.__repo.remove_automobil(1)
        self.assertEqual(len(self.__repo.get_all_automobile()), 9)

if __name__ == '__main__':
    unittest.main()