from repository.repository_automobil import RepositoryFile
from service.service_automobil import ServiceAutomobil
from ui.console import Console

repository = RepositoryFile("data/automobile.txt")
service = ServiceAutomobil(repository)
console = Console(service)
console.run()