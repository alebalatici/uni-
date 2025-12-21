class Jucator:
    def __init__(self, id_jucator, nume, echipa, pozitie, numar_puncte):
        self.__id_jucator = id_jucator
        self.__nume = nume
        self.__echipa = echipa
        self.__pozitie = pozitie
        self.__numar_puncte = numar_puncte

    @property
    def id_jucator(self):
        return self.__id_jucator

    @property
    def nume(self):
        return self.__nume

    @property
    def echipa(self):
        return self.__echipa

    @property
    def pozitie(self):
        return self.__pozitie

    @property
    def numar_puncte(self):
        return self.__numar_puncte

    @nume.setter
    def nume(self, nume):
        self.__nume = nume

    @echipa.setter
    def echipa(self, echipa):
        self.__echipa = echipa

    @pozitie.setter
    def pozitie(self, pozitie):
        self.__pozitie = pozitie

    @numar_puncte.setter
    def numar_puncte(self, numar_puncte):
        self.__numar_puncte = numar_puncte

    def __eq__(self, other):
        return self.__id_jucator == other.id_jucator and self.__nume == other.nume and self.__echipa == other.echipa and self.__pozitie == other.pozitie and self.__numar_puncte == other.numar_puncte

    def __str__(self):
        return f"{self.__id_jucator}, {self.__nume}, {self.__echipa}, {self.__pozitie}, {self.__numar_puncte}"

# j1 = Jucator(103, "adsfdg", "danisfdv", "wemoisdf", 132435)
# j2 = Jucator(103, "adsfdg", "danisfdv", "wemoisdf", 132435)
# print(j1 == j2)
# print(j1)