from domain.vacanta import Vacanta

class BookingInquiry:
    def __init__(self, locatie, buget):
        self.__locatie = locatie
        self.__buget = buget

    @property
    def locatie(self):
        return self.__locatie

    @property
    def buget(self):
        return self.__buget

    def get_number_of_days(self):
        return self.__buget // self.locatie.pret_pe_zi

    def __str__(self):
        #return f"Pentru supa de {self.__buget} poti sta la {self.__locatie.id_locatie} | {self.__locatie.denumire} | {self.__locatie.tip} | {self.__locatie.pret_pe_zi} pentru {self.get_number_of_days()} zile"
        return f"Poti sta la  {self.__locatie.denumire} | {self.__locatie.tip} pentru {self.get_number_of_days()} zile"