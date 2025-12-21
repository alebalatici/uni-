from repository.repository_jucatori import *
import unittest

class TestRepositoryMemory(unittest.TestCase):
    def setUp(self):
        print("setUp")
        self.test_repo = RepositoryJucatorMemory()

    def tearDown(self):
        print("tearDown")

    def test_add_jucator(self):
        j1 = Jucator("NYURTC", "LeBron James", "Lakers", "Forward", 112)
        self.test_repo.add_jucator(j1)
        self.assertEqual(len(self.test_repo.get_all_jucatori()), 1)
        j2 = Jucator("NYTC", "  dowsfmk", "danfsov", "Forward", 112)
        self.test_repo.add_jucator(j2)
        self.assertEqual(len(self.test_repo.get_all_jucatori()), 2)
        j3 = Jucator("adiospf", "qdpowfemg", "dcoifmvdbr", "dfomeig", 1324)
        self.test_repo.add_jucator(j3)
        self.assertEqual(len(self.test_repo.get_all_jucatori()), 3)

    def test_find_jucator(self):
        j1 = Jucator("NYURTC", "LeBron James", "Lakers", "Forward", 112)
        self.test_repo.add_jucator(j1)
        j2 = Jucator("NYTC", "  dowsfmk", "danfsov", "Forward", 112)
        self.test_repo.add_jucator(j2)
        j3 = Jucator("adiospf", "qdpowfemg", "dcoifmvdbr", "dfomeig", 1324)
        self.test_repo.add_jucator(j3)
        jf1 = self.test_repo.find_jucator(j1.id_jucator)
        jf2 = self.test_repo.find_jucator(j2.id_jucator)
        jf3 = self.test_repo.find_jucator(j3.id_jucator)
        self.assertEqual(j1, jf1)
        self.assertEqual(j2, jf2)
        self.assertEqual(j3, jf3)

    def test_get_all_jucatori(self):
        j1 = Jucator("NYURTC", "LeBron James", "Lakers", "Forward", 112)
        self.test_repo.add_jucator(j1)
        j2 = Jucator("NYTC", "  dowsfmk", "danfsov", "Forward", 112)
        self.test_repo.add_jucator(j2)
        j3 = Jucator("adiospf", "qdpowfemg", "dcoifmvdbr", "dfomeig", 1324)
        self.test_repo.add_jucator(j3)
        self.assertEqual(len(self.test_repo.get_all_jucatori()), 3)

class TestRepositoryFile(unittest.TestCase):
    def setUp(self):
        print("setUp")
        self.test_repo = RepositoryJucatorFile("tests/jucatori_test.txt")

    def test_add_jucator(self):
        n = len(self.test_repo.get_all_jucatori())
        j1 = Jucator("NYURTC", "LeBron James", "Lakers", "Forward", 112)
        self.test_repo.add_jucator(j1)
        self.assertEqual(len(self.test_repo.get_all_jucatori()), n + 1)
        j2 = Jucator("NYTC", "  dowsfmk", "danfsov", "Forward", 112)
        self.test_repo.add_jucator(j2)
        self.assertEqual(len(self.test_repo.get_all_jucatori()), n + 2)
        j3 = Jucator("adiospf", "qdpowfemg", "dcoifmvdbr", "dfomeig", 1324)
        self.test_repo.add_jucator(j3)
        self.assertEqual(len(self.test_repo.get_all_jucatori()), n + 3)

    def test_find_jucator(self):
        j1 = Jucator("NYURTC", "LeBron James", "Lakers", "Forward", 112)
        self.test_repo.add_jucator(j1)
        j2 = Jucator("NYTC", "  dowsfmk", "danfsov", "Forward", 112)
        self.test_repo.add_jucator(j2)
        j3 = Jucator("adiospf", "qdpowfemg", "dcoifmvdbr", "dfomeig", 1324)
        self.test_repo.add_jucator(j3)
        jf1 = self.test_repo.find_jucator(j1.id_jucator)
        jf2 = self.test_repo.find_jucator(j2.id_jucator)
        jf3 = self.test_repo.find_jucator(j3.id_jucator)
        self.assertEqual(j1, jf1)
        self.assertEqual(j2, jf2)
        self.assertEqual(j3, jf3)

    def test_get_all_jucatori(self):
        n = len(self.test_repo.get_all_jucatori())
        j1 = Jucator("NYURTC", "LeBron James", "Lakers", "Forward", 112)
        self.test_repo.add_jucator(j1)
        j2 = Jucator("NYTC", "  dowsfmk", "danfsov", "Forward", 112)
        self.test_repo.add_jucator(j2)
        j3 = Jucator("adiospf", "qdpowfemg", "dcoifmvdbr", "dfomeig", 1324)
        self.test_repo.add_jucator(j3)
        self.assertEqual(len(self.test_repo.get_all_jucatori()), n + 3)

    def tearDown(self):
        print("tearDown")
        with open("tests/jucatori_test.txt", "w") as file:
            default_file = open("tests/jucatori_default.txt")
            default_date = default_file.read()
            default_file.close()
            file.write(default_date)

if __name__ == '__main__':
    unittest.main()
