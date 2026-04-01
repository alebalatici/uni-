import unittest
from repo.repository_specie import *
from domain.specie import Specie
class TestRepository(unittest.TestCase):
    def setUp(self):
        print("setUp")
        self.__repo = Repository()

    def tearDown(self):
        print("tearDown")

    def test_add_specie(self):
        s1 = Specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__repo.add_specie(s1)
        s2 = Specie(2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__repo.add_specie(s2)
        s3 = Specie(3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)
        self.__repo.add_specie(s3)

        self.assertEqual(len(self.__repo.get_all_species()), 3)
        self.assertEqual(self.__repo.get_all_species()[0].nume, "Bober")
        self.assertEqual(self.__repo.get_all_species()[1].nume, "Taxictis lumeus")
        self.assertEqual(self.__repo.get_all_species()[2].nume, "Amazonica impennis")

        s4 = Specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)

        with self.assertRaises(SpecieAlreadyExists):
            self.__repo.add_specie(s4)

    def test_remove_specie(self):
        s1 = Specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__repo.add_specie(s1)
        s2 = Specie(2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__repo.add_specie(s2)
        s3 = Specie(3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)
        self.__repo.add_specie(s3)

        self.assertEqual(len(self.__repo.get_all_species()), 3)
        self.__repo.remove_specie(s3)
        self.assertEqual(len(self.__repo.get_all_species()), 2)
        self.__repo.remove_specie(s2)
        self.assertEqual(len(self.__repo.get_all_species()), 1)
        self.__repo.remove_specie(s1)
        self.assertEqual(len(self.__repo.get_all_species()), 0)

    def test_find_specie(self):
        s1 = Specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__repo.add_specie(s1)
        s2 = Specie(2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__repo.add_specie(s2)
        s3 = Specie(3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)
        self.__repo.add_specie(s3)

        s4 = self.__repo.find_specie(1)
        self.assertEqual(s4.nume, "Bober")
        self.assertEqual(s4.data_str, "2023/12/12")
        self.assertEqual(s4.locatia, "Poland")
        self.assertEqual(s4.tip, "mammal")
        self.assertEqual(s4.lifespan, 10)
        self.assertEqual(s4, s1)

    def test_get_all_species(self):
        s1 = Specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__repo.add_specie(s1)
        s2 = Specie(2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__repo.add_specie(s2)
        s3 = Specie(3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)
        self.__repo.add_specie(s3)

        self.assertEqual(len(self.__repo.get_all_species()), 3)

class TestRepositoryFile(unittest.TestCase):
    def setUp(self):
        print("setUp")
        self.__repo = RepositoryFile("tests/test_specii.txt")

    def tearDown(self):
        print("tearDown")
        with open("tests/test_specii.txt", "w") as file:
            fisier_default = open("tests/template_specii.txt", "r")
            content = fisier_default.read()
            file.write(content)
            fisier_default.close()

    def test_add_specie(self):
        n = len(self.__repo.get_all_species())
        s1 = Specie(n + 1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__repo.add_specie(s1)
        s2 = Specie(n + 2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__repo.add_specie(s2)
        s3 = Specie(n + 3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)
        self.__repo.add_specie(s3)
        self.assertEqual(len(self.__repo.get_all_species()), n + 3)

        s4 = Specie(n + 1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        with self.assertRaises(SpecieAlreadyExists):
            self.__repo.add_specie(s4)

    def test_remove_specie(self):
        s1 = Specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        s2 = Specie(2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        s3 = Specie(3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)

        n = len(self.__repo.get_all_species())
        self.__repo.remove_specie(s3)
        self.assertEqual(len(self.__repo.get_all_species()), n - 1)
        self.__repo.remove_specie(s2)
        self.assertEqual(len(self.__repo.get_all_species()), n - 2)
        self.__repo.remove_specie(s1)
        self.assertEqual(len(self.__repo.get_all_species()), n - 3)

    def test_find_specie(self):
        s1 = self.__repo.find_specie(11)
        s2 = Specie(11, "Ursus minimus", "1975/10/05", "Russia", "mammal", 2)
        self.assertEqual(s1, s2)

if __name__ == '__main__':
    unittest.main()