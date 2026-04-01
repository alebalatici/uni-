from repo.repository_specie import RepositoryFile
from domain.validator import Validator
from service.service_specie import Service
from ui.console import Consola
repo = RepositoryFile("data/specii.txt")
val = Validator()
srv = Service(repo, val)
console = Consola(srv)
console.run()
