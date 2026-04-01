import datetime
class Specie:
    def __init__(self, id, nume, data, locatia, tip, lifespan):
        self.__id = id
        self.__nume = nume
        self.__data = data
        self.__locatia = locatia
        self.__tip = tip
        self.__lifespan = lifespan

    @property
    def id(self):
        return self.__id

    @property
    def nume(self):
        return self.__nume

    @property
    def data_str(self):
        return self.__data

    @property
    def data(self):
        return datetime.datetime.strptime(self.__data, "%Y/%m/%d").date()

    @property
    def locatia(self):
        return self.__locatia

    @property
    def tip(self):
        return self.__tip

    @property
    def lifespan(self):
        return self.__lifespan

    def __str__(self):
        return f"ID: {self.id} | Nume: {self.nume} | Data: {self.data} | Locatia: {self.locatia} | Tip: {self.tip} | Lifespan: {self.lifespan}"

    def __eq__(self, other):
        return self.id == other.id and self.nume == other.nume and self.data == other.data and self.locatia == other.locatia and self.tip == other.tip and self.lifespan == other.lifespan