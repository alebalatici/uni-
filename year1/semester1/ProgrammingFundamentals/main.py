from domain.validator import Validator
from repository.repository_jucatori import *
from service.service_jucatori import *
from ui.console import Console

repo = RepositoryJucatorFile("data/jucatori.txt")
val = Validator()
srv = ServiceJucatori(repo, val)
console = Console(srv)
console.run()
