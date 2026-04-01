from repository.repository_vacanta import *
from service.service_vacanta import ServiceVacanta
from ui.consola import Consola
from domain.validator import Validator

repo = RepositoryVacantaFile("data/vacante.txt")
val = Validator()
srv = ServiceVacanta(repo, val)
consola = Consola(srv)
consola.run()