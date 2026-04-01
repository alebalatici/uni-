from domain.specie import Specie
import datetime

class ValidationError(Exception):
    def __init__(self, message):
        self.message = message

class Validator():
    def validate(self, specie):
        errors = []

        if not isinstance(specie, Specie):
            errors.append("Nu este o specie")

        if not isinstance(specie.id, int):
            errors.append("Id-ul trebuie sa fie un numar natural")
        else:
            if specie.id < 0:
                errors.append("Id-ul trebuie sa fie un numar natural")

        if not isinstance(specie.nume, str):
            errors.append("Numele trebuie sa fie un string")

        if not isinstance(specie.data_str, str):
            errors.append("Va rugam introduceti o data valida")

        if not isinstance(specie.data, datetime.date):
            errors.append("Va rugam introduceti o data valida")

        if not isinstance(specie.locatia, str):
            errors.append("Va rugam introduceti o locatia valida")

        if not isinstance(specie.tip, str):
            errors.append("Va rugam introduceti un tip valid")

        if not isinstance(specie.lifespan, int):
            errors.append("Lifespan-ul trebuie sa fie un numar natural")

        else:
            if specie.lifespan < 0:
                errors.append("Lifespan-ul trebuie sa fie un numar natural")

        if errors:
            errors_msg = "\n ".join(errors)
            raise ValidationError(errors_msg)