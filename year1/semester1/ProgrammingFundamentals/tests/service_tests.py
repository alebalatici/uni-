import unittest
from service.service_jucatori import ServiceJucatori
from domain.validator import Validator
from repository.repository_jucatori import *

class TestServiceJucatori(unittest.TestCase):
    def setUp(self):
        print("setUp")
        val = Validator()
        repo = RepositoryJucatorFile("tests/jucatori_test.txt")
        self.test_service = ServiceJucatori(repo, val)

    def tearDown(self):
        print("tearDown")
        with open("tests/jucatori_test.txt", "w") as file:
            fisier_default = open("tests/jucatori_default.txt", "r")
            continut = fisier_default.read()
            fisier_default.close()
            file.write(continut)

    def test_add_jucatori(self):
        n = len(self.test_service.get_all_jucatori())
        self.test_service.add_jucator("NYURTC", "LeBron James", "Lakers", "Forward", 112)
        self.assertEqual(len(self.test_service.get_all_jucatori()), n + 1)
        self.test_service.add_jucator("NYRTC", "LeBron James", "Lakers", "Forward", 112)
        self.assertEqual(len(self.test_service.get_all_jucatori()), n + 2)
        self.test_service.add_jucator("DIWMFK", "LeBron James", "Lakers", "Forward", 112)
        self.assertEqual(len(self.test_service.get_all_jucatori()), n + 3)

    def test_find_jucatori(self):
        j1 = self.test_service.find_jucator("B11")
        self.assertIsNotNone(j1)

    def test_cautare_jucator_pozitie_echipa(self):
        jucatori = self.test_service.get_all_jucatori()
        ans = self.test_service.cautare_jucator_pozitie_echipa("Forward", "Lakers", jucatori)
        #assert len(ans) == 1
        j = Jucator("B01", "LeBron James", "Lakers", "Forward", 112)
        j1 = ans[0]
        self.assertEqual(j, j1)

if __name__ == '__main__':
    unittest.main()