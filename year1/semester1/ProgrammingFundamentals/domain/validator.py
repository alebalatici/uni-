from domain.jucator import Jucator
class ValidationError(Exception):
    def __init__(self, message):
        super().__init__(message)

class Validator:
    def validate(self, jucator: Jucator):
        errors = []
        # if not isinstance(jucator.id_jucator, int):
        #     errors.append("ID-ul trebuie sa fie un numar natural")
        # else:
        #     if jucator.id_jucator < 0:
        #         errors.append("ID-ul trebuie sa fie un numar natural")
        if jucator.nume == "":
            errors.append("Numele nu poate fi vid")
        if jucator.echipa == "":
            errors.append("Echipa nu poate fi vida")
        if jucator.pozitie == "":
            errors.append("Pozitia nu poate fi vida")
        if not isinstance(jucator.numar_puncte, int):
            errors.append("Punctele trebuie sa fie un numar natural")
        else:
            if jucator.numar_puncte < 0:
                errors.append("Punctele trebuie sa fie un numar natural")
        if len(errors) > 0:
            error_msg = "\n".join(errors)
            raise ValidationError(error_msg)

# val = Validator()
# j1 = Jucator(1324, "diwofd", "aiofsd", "adiosfp", 3124)
# val.validate(j1)
# j2 = Jucator("adoisf", "","", "", -1324)
# val.validate(j2)