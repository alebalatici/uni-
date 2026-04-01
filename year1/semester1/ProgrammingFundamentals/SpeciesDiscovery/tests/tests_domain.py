import unittest
from domain.validator import *

class TestsDomain(unittest.TestCase):
    def setUp(self):
        print("setUp")

    def tearDown(self):
        print("tearDown")

    def test_domain(self):
        s1 = Specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.assertEqual(s1.id, 1)
        self.assertEqual(s1.nume, "Bober")
        self.assertEqual(s1.data_str, "2023/12/12")
        self.assertEqual(s1.locatia, "Poland")
        self.assertEqual(s1.tip, "mammal")
        self.assertEqual(s1.lifespan, 10)

        s2 = Specie(1, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.assertEqual(s1, s2)

        s3 = Specie(2, "Bober", "2023/12/12", "Poland", "mammal", 10)
        self.assertNotEqual(s1, s3)

    def test_validator(self):
        val = Validator()
        s1 = Specie("1", "Bober", "2023/12/12", "Poland", "mammal", 10)
        s2 = Specie(1, 32943, "2023/12/12", "Poland", "mammal", 10)
        s3 = Specie(1, "Bober", -2435409, "Poland", "mammal", 10)
        s4 = Specie(1, "Bober", "2023/12/12/12", "Poland", "mammal", 10)
        s5 = Specie(1, "Bober", "2023/12/12", -913243, "mammal", 10)
        s6 = Specie(1, "Bober", "2023/12/12", "Poland", 13092, 10)
        s7 = Specie(1, "Bober", "2023/12/12", "Poland", "mammal", "10")
        s8 = Specie(1, "Bober", "2023/12/12", "Poland", "mammal", -10)
        with self.assertRaises(ValidationError):
            val.validate(s1)

        with self.assertRaises(ValidationError):
            val.validate(s2)

        with self.assertRaises(TypeError):
            val.validate(s3)

        with self.assertRaises(ValueError):
            val.validate(s4)

        with self.assertRaises(ValidationError):
            val.validate(s5)

        with self.assertRaises(ValidationError):
            val.validate(s6)

        with self.assertRaises(ValidationError):
            val.validate(s7)

        with self.assertRaises(ValidationError):
            val.validate(s8)

if __name__ == '__main__':
    unittest.main()