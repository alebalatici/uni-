class EvaluationError(Exception):
    def __init__(self, message):
        super().__init__(message)
from domain.jucator import Jucator
class MVPCandidate():
    def __init__(self, jucator, numar_meciuri):
        self.__jucator = jucator
        self.__numar_meciuri = numar_meciuri

    @property
    def jucator(self):
        return self.__jucator

    @property
    def numar_meciuri(self):
        return self.__numar_meciuri

    def get_points_average(self):
        """
        Calculeaza numarul mediu de puncte pe meci
        """
        try:
            average_points = self.__jucator.numar_puncte / self.__numar_meciuri
            return average_points
        except KeyError:
            raise EvaluationError("Points not recognized")

    def __str__(self):
        return f"Jucatorul {self.__jucator.nume} primeste un average de {self.get_points_average()} de puncte pe meci"