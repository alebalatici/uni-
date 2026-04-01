import datetime
class Automobil:
    def __init__(self, id, marca, pret, model, data):
        self.__id = id
        self.__marca = marca
        self.__pret = pret
        self.__model = model
        self.__data = data

    @property
    def id(self):
        return self.__id

    @property
    def marca(self):
        return self.__marca

    @property
    def pret(self):
        return self.__pret

    @property
    def model(self):
        return self.__model

    @property
    def data_str(self):
        return self.__data

    @property
    def data(self):
        return datetime.datetime.strptime(self.__data, "%d/%m/%Y").date()

    def __str__(self):
        return f"ID: {self.id} | Marca: {self.marca} | Pret: {self.pret} | Model: {self.model} | Data: {self.data_str}"

    def __eq__(self, other):
        return self.id == other.id and self.marca == other.marca and self.pret == other.pret and self.model == other.model and self.data_str == other.data_str