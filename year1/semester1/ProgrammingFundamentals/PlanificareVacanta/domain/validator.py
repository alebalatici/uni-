from domain.vacanta import Vacanta
class ValidationException(Exception):
    def __init__(self, message):
        self.message = message

class Validator:
    def validate(self, vacanta: Vacanta):
        errors = []

        if not isinstance(vacanta.id_locatie, int):
            errors.append("ID-ul locatiei trebuie sa fie un numar")

        else:
            if vacanta.id_locatie < 0:
                errors.append("ID-ul locatiei trebuie sa fie un numar natural")

        if vacanta.denumire == "":
            errors.append("Denumirea nu poate fi vida")

        if vacanta.tip == "":
            errors.append("Tip nu poate fi vid")

        if not isinstance(vacanta.pret_pe_zi, int):
            errors.append("Pret pe zi trebuie sa fie un numar")

        else:
            if vacanta.pret_pe_zi < 0:
                errors.append("Pret pe zi trebuie sa fie un numar natural")

        if len(errors) > 0:
            errors_str = '\n'.join(errors)
            raise ValidationException(errors_str)