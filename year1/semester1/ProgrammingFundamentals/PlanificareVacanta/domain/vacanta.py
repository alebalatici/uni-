class Vacanta:
    def __init__(self, id_locatie, denumire, tip, pret_pe_zi):
        self.__id_locatie = id_locatie
        self.__denumire = denumire
        self.__tip = tip
        self.__pret_pe_zi = pret_pe_zi

    @property
    def id_locatie(self):
        return self.__id_locatie

    @property
    def denumire(self):
        return self.__denumire

    @property
    def tip(self):
        return self.__tip

    @property
    def pret_pe_zi(self):
        return self.__pret_pe_zi

    def __eq__(self, other):
        return self.__id_locatie == other.id_locatie and self.__denumire == other.denumire and self.__tip == other.tip and self.__pret_pe_zi == other.pret_pe_zi

    def __str__(self):
        return f"{self.__id_locatie} | {self.__denumire} | {self.__tip} | {self.__pret_pe_zi}"
