import unittest
from domain.automobil import Automobil

class Tests(unittest.TestCase):
    def setUp(self):
        print("setUp")

    def tearDown(self):
        print("tearDown")

    def test_domain(self):
        auto = Automobil(1, "Renault", 20000, "dsnoidn", "14/05/2025")
        self.assertEqual(auto.id, 1)
        self.assertEqual(auto.marca, "Renault")
        self.assertEqual(auto.pret, 20000)
        self.assertEqual(auto.model, "dsnoidn")
        self.assertEqual(auto.data_str, "14/05/2025")
        auto1 = Automobil(1, "Renault", 20000, "dsnoidn", "14/05/2025")
        self.assertEqual(auto, auto1)

if __name__ == '__main__':
    unittest.main()