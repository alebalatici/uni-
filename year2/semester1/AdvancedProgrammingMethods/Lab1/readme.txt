Documentatie Lab1

Aplicatia a fost structurata avand la baza urmatoarele principii SOLID:
1) Single Responsibility Principle (SRP): Fiecare clasa din proiect are un singur scop bine definit:
- ComplexNumber: Incapsuleaza starea si reprezentarea unui numar complex
- ComplexExpressionParser: Validarea si parsarea (transformarea unui string intr-un numar complex) a argumentelor din linia de comanda
- Operation (Addition, Subtraction, Multiplication, Division): Se ocupa fiecare de urmatoarele calcule matematice: adunarea, scaderea, inmultirea, impartirea
- ExpressionEvaluator: Coordoneaza evaluarea expresiei primind toate argumentele liniei de comanda

2) Open/Closed principle (OCP):
- Aplicatia este deschisa pentru extindere, dar inchisa pentru modificare.
- Daca se doreste adaugarea unei noi operatii, nu trebuie modificat codul existent.

3) Liskov Substitution Principle (LSP):
- Oricare dintre operatii (Addition, Subtraction, Multiplication, Division) poate inlocui interfata Operation in clasa ExpressionEvaluator fara a afecta corectitudinea aplicatiei.

4) Interface Segregation Principle (ISP):
- Interfata InputExpressionParser contine doar metodele esentiale pentru parsare (isValid si parseComplex), evitand obligarea claselor derivate sa implementeze metode inutile

5) Dependency Inversion Principle (DIP):
- Clasa ExpressionEvaluator nu este legata direct de un parser fix (ex: ComplexExpressionParser), ci foloseste o interfata (InputExpressionParser). Evaluatorul nu se intereseaza cum se face parsarea in spate, ci doar ca primeste un obiect care stie sa parsing-eze.

Un prim sablon de proiectare folosit este Factory. Clasa OperationFactory se ocupa cu crearea obiectelor de tip Operation pe baza simbolului primit ca parametru (+, -, *, /). Factory-ul returneaza operatia corespunzatoare.
Al doilea sablon de proiectare folosit este Strategy. Pentru ca aplicatia trebuie sa efectueze operatii aritmetice diferite (+, -, *, /) in functie de operatorul primit in linia de comanda, fiecare algoritm de calcul are propria sa clasa. Toate clasele de calcul implementeaza interfata comuna Operation, iar clasa ExpressionEvaluator nu stie ce tip de operatie executa, doar apeleaza execute() din Operation, acest lucru permitant schimbarea dinamica a strategiei de calcul.

Reflectarea in diagrama UML
1) Interfete:
- InputExpressionParser
- Operation

2) Relatii de realizare (Interface Realization):
- Addition, Subtraction, Multiplication, Division implementeaza interfata Operation
- ComplexExpressionParser implementeaza InputExpressionParser

3) Relatii de Agregare:
- ExpressionEvaluator are o relatie de Agregare cu InputExpressionParser deoarece parstreaza parserul ca atribut privat

4) Relatii de dependenta:
- OperationFactory are o relatie de dependenta catre Operation deoarece creeaza instante ale operatiilor
- ComplexExpressionParser si Operation au o relatie de dependenta catre ComplexNumber deoarece instantiaza si creeaza numere complexe.