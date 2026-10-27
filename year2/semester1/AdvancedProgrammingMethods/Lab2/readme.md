## Prerequisites
**Java JDK**L 26
**Apache Maven**: 3.8+

## Maven installation
```
mvn clean install
```
## Cloning Instructions
```
git clone --no-checkout https://github.com/alebalatici/uni-.git
cd uni-
git sparse-checkout init --cone
git sparse-checkout set year2/semester1/AdvancedProgrammingMethods/Lab2/toy-social-network
git checkout main
```

# Toy Social Network Application
Aplicatie pentru gestionarea unei retele de socializare.

## Functionalitati:
- Adaugarea unui nou utilizator.
- Stergerea din aplicatie a unui utilizator
- Adaugarea unei prietenii dintre 2 utilizatori existenti
- Stergerea unei prietenii dintre 2 utilizatori
- Afisarea numarului de comunitati
- Afisarea celei mai sociabile comunitati
- Afisarea tuturor utilizatorilor
- Afisarea tuturor prieteniilor dintre utilizatori
- Exit din aplicatie

### Aplicatia este proiectata pe baza principiilor SOLID si a celor mai bune practici de proiectare orientata pe obiect OOP:
  * Strategy Pattern (Stratul de validare)
	--> Interfata generica Validator<E> defineste strategia generala de validare.
	--> Implementarile concrete (UserValidator, FriendshipValidator) incapsuleaza regulile specifice fiecarei entitati.
	--> Permite schimbarea sau extinderea regulilor de validare fara a modifica codul din NetworkService.

  * Repository si Inheritance
	--> Repository<ID, E> abstractizeaza operatiile CRUD
	--> RepositoryInMemory<ID, E> ofera o implementare de baza in memorie folosind 'HashMap'
	--> AbstractJsonRepository<ID, E> extinde repository-ul in memorie folosind modelul Template/Decorator (adaugarea dinamica de responsabilitati)

  * Domain Driven Design
	--> Clasa generica Entity<ID> ofera o baza unica pentru identificarea obiectelor de domeniu.
	
## Structura proiectului:
```
├───data
│       friendships.json
│       users.json
│       
├───src
│   ├───main
│   │   ├───java
│   │   │   │   Main.java
│   │   │   │   
│   │   │   └───org
│   │   │       └───example
│   │   │           ├───console
│   │   │           │       Console.java
│   │   │           │       
│   │   │           ├───domain
│   │   │           │       Entity.java
│   │   │           │       Friendship.java
│   │   │           │       Tuple.java
│   │   │           │       User.java
│   │   │           │       
│   │   │           ├───repo
│   │   │           │       AbstractJsonRepository.java
│   │   │           │       FriendshipRepository.java
│   │   │           │       Repository.java
│   │   │           │       RepositoryException.java
│   │   │           │       RepositoryInMemory.java
│   │   │           │       UserRepository.java
│   │   │           │       
│   │   │           ├───service
│   │   │           │       NetworkService.java
│   │   │           │       ServiceException.java
│   │   │           │       
│   │   │           ├───utils
│   │   │           │       FileUtils.java
│   │   │           │       
│   │   │           └───validator
│   │   │                   FriendshipValidator.java
│   │   │                   UserValidator.java
│   │   │                   ValidationException.java
│   │   │                   Validator.java
│   │   │                   
│   │   └───resources
│   └───test
│       ├───java
│       │   └───org
│       │       └───example
│       │               TestsDomainValidator.java
│       │               TestsRepo.java
│       │               TestsService.java
│       │               
│       └───resources
│               friendships.json
│               users.json
```
- org.example.domain: Entitatile de domeniu (User, Friendship, Entity, Tuple)
- org.example.validator: Logica de validare si exceptiile de domeniu
- org.example.repo: Clasele si interfetele pentru incarcarea datelor in fisiere
- org.example.console: Interfata cu utilizatorul (CLI)
- org.example.utlis: Utilitare ale aplicatiei

## Tehnologii si Biblioteci
- Versiune Java: Java 26
- Build Tool: Maven
- Salvarea datelor in fisiere: JSON
- Testare: JUnit 5
