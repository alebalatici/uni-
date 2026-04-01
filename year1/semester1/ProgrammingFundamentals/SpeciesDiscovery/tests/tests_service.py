import unittest
from repo.repository_specie import *
from domain.validator import Validator
from service.service_specie import Service
class TestService(unittest.TestCase):
    def setUp(self):
        print("setUp")
        repo = Repository()
        val = Validator()
        self.__srv = Service(repo, val)

    def tearDown(self):
        print("tearDown")

    def test_add_specie(self):

        self.__srv.add_specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__srv.add_specie(2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__srv.add_specie(3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)

        self.assertEqual(len(self.__srv.get_all_species()), 3)
        self.assertEqual(self.__srv.get_all_species()[0].nume, "Bober")
        self.assertEqual(self.__srv.get_all_species()[1].nume, "Taxictis lumeus")
        self.assertEqual(self.__srv.get_all_species()[2].nume, "Amazonica impennis")

        with self.assertRaises(SpecieAlreadyExists):
            self.__srv.add_specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)

    def test_remove_specie(self):
        self.__srv.add_specie  (1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__srv.add_specie (2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__srv.add_specie (3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)

        self.assertEqual(len(self.__srv.get_all_species()), 3)
        self.__srv.remove_specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.assertEqual(len(self.__srv.get_all_species()), 2)
        self.__srv.remove_specie(2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.assertEqual(len(self.__srv.get_all_species()), 1)
        self.__srv.remove_specie(3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)
        self.assertEqual(len(self.__srv.get_all_species()), 0)

    def test_find_specie(self):
        self.__srv.add_specie (1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__srv.add_specie(2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__srv.add_specie(3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)

        s4 = self.__srv.find_specie(1)
        self.assertEqual(self.__srv.get_all_species()[0].nume, "Bober")
        self.assertEqual(self.__srv.get_all_species()[0].data_str, "2023/12/12")
        self.assertEqual(self.__srv.get_all_species()[0].locatia, "Poland")
        self.assertEqual(self.__srv.get_all_species()[0].tip, "mammal")
        self.assertEqual(self.__srv.get_all_species()[0].lifespan, 10)

    def test_get_all_species(self):
        self.__srv.add_specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__srv.add_specie(2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__srv.add_specie(3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)
        self.assertEqual(len(self.__srv.get_all_species()), 3)

class TestServiceFile(unittest.TestCase):
    def setUp(self):
        print("setUp")
        repo = RepositoryFile("tests/test_specii.txt")
        val = Validator()
        self.__srv = Service(repo, val)

    def tearDown(self):
        print("tearDown")
        with open("tests/test_specii.txt", "w") as file:
            fisier_defaul = open("tests/template_specii.txt", "r")
            content = fisier_defaul.read()
            file.write(content)
            fisier_defaul.close()

    def test_add_specie(self):
        n = len(self.__srv.get_all_species())
        self.__srv.add_specie(n + 1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__srv.add_specie(n + 2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__srv.add_specie(n + 3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)

        self.assertEqual(len(self.__srv.get_all_species()), n + 3)
        self.assertEqual(self.__srv.get_all_species()[n].nume, "Bober")
        self.assertEqual(self.__srv.get_all_species()[n + 1].nume, "Taxictis lumeus")
        self.assertEqual(self.__srv.get_all_species()[n + 2].nume, "Amazonica impennis")

        with self.assertRaises(SpecieAlreadyExists):
            self.__srv.add_specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)

    def test_remove_specie(self):
        n = len(self.__srv.get_all_species())
        self.__srv.add_specie(n + 1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__srv.add_specie(n + 2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__srv.add_specie(n + 3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)

        self.assertEqual(len(self.__srv.get_all_species()), n + 3)
        self.__srv.remove_specie(n + 1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.assertEqual(len(self.__srv.get_all_species()), n + 2)
        self.__srv.remove_specie(n + 2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.assertEqual(len(self.__srv.get_all_species()), n + 1)
        self.__srv.remove_specie(n + 3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)
        self.assertEqual(len(self.__srv.get_all_species()), n)

    def test_find_specie(self):
        n = len(self.__srv.get_all_species())
        self.__srv.add_specie(n + 1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.__srv.add_specie(n + 2, "Taxictis lumeus", "1994/11/01", "Antarctica", "reptile", 4)
        self.__srv.add_specie(n + 3, "Amazonica impennis", "2011/04/12", "Brazil", "reptile", 60)

        s4 = self.__srv.find_specie(n + 1)
        self.assertEqual(self.__srv.get_all_species()[n].nume, "Bober")
        self.assertEqual(self.__srv.get_all_species()[n].data_str, "2023/12/12")
        self.assertEqual(self.__srv.get_all_species()[n].locatia, "Poland")
        self.assertEqual(self.__srv.get_all_species()[n].tip, "mammal")
        self.assertEqual(self.__srv.get_all_species()[n].lifespan, 10)

    def test_find_discoveries_by_date(self):
        species = self.__srv.find_discoveries_by_date("1979/11/22")
        self.assertEqual(len(species), 29)
        species = self.__srv.find_discoveries_by_date("2011/12/12")
        self.assertEqual(len(species), 42)
        species = self.__srv.find_discoveries_by_date("2000/11/11")
        self.assertEqual(len(species), 35)

    def test_statistics_by_type(self):
        specie, media = self.__srv.statistics_by_type("mammal")
        self.assertEqual(specie.id, 1)
        self.assertEqual(specie.nume, "Bober")
        self.assertEqual(specie.data_str, "2023/12/12")
        self.assertEqual(specie.locatia, "Poland")
        self.assertEqual(specie.lifespan, 10)
        self.assertEqual(media, 6.647058823529412)

if __name__ == '__main__':
    unittest.main()