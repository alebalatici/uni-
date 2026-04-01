from domain.vacanta import Vacanta
from domain.validator import Validator, ValidationException
import unittest
class TestVacanta(unittest.TestCase):
    def setUp(self):
        print("setUp")

    def tearDown(self):
        print("tearDown")

    def test_vacanta(self):
        vacanta = Vacanta(1, "Hotel Belvedere", "mare all-inclusive", 500)
        self.assertEqual(vacanta.id_locatie, 1)
        self.assertEqual(vacanta.denumire, "Hotel Belvedere")
        self.assertEqual(vacanta.tip, "mare all-inclusive")
        self.assertEqual(vacanta.pret_pe_zi, 500)

        vacanta1 = Vacanta(1, "Hotel Belvedere", "mare all-inclusive", 500)
        self.assertEqual(vacanta, vacanta1)

    def test_validator(self):
        validator = Validator()
        vacanta1 = Vacanta("dksfdk", "Hotel Belvedere", "mare all-inclusive", 500)
        vacanta2 = Vacanta(1, "", "mare all-inclusive", 500)
        vacanta3 = Vacanta(1, "Hotel Belvedere", "", 500)
        vacanta4 = Vacanta(1, "Hotel Belvedere", "mare all-inclusive", "adnksf")
        vacanta5 = Vacanta(1, "Hotel Belvedere", "", -500)

        with self.assertRaises(ValidationException):
            validator.validate(vacanta1)
            validator.validate(vacanta2)
            validator.validate(vacanta3)
            validator.validate(vacanta4)
            validator.validate(vacanta5)

if __name__ == '__main__':
    unittest.main()