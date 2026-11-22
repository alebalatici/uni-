% adauga_final(E:integer, L:list, Rez:list)
adauga_final(E, [], [E]).
adauga_final(E, [H|T], [H|Rez]):-
    adauga_final(E, T, Rez).

% inverseaza(L:list, Rez:list)
inverseaza([], []):-!.
inverseaza([H|T], Rez):-
    inverseaza(T, R1),
    adauga_final(H, R1, Rez).

% sumaIntegerAux(A:list, T:integer, Rez:list)
sumaIntegerAux(A, 0, A):-!.
sumaIntegerAux([], Tr, [Tr]):-!.

sumaIntegerAux([H|T], Tr, [Rest|Rez]):-
    Sum is H + Tr,
    Rest is Sum mod 10,
    Div is Sum div 10,
    sumaIntegerAux(T, Div, Rez).

% sumaInteger(A:list, T:integer, Rez:list)
sumaInteger(A, T, Rez):-
    inverseaza(A, A1),
    sumaIntegerAux(A1, T, RezInv),
    inverseaza(RezInv, Rez).

% sumaAux(A:list, B:list, T:integer, Rez:list)
sumaAux([], B, Tr, Rez):-
    sumaIntegerAux(B, Tr, Rez), !.

sumaAux(A, [], Tr, Rez):-
    sumaIntegerAux(A, Tr, Rez), !.

sumaAux([], [], Tr, [Tr]):-!.

sumaAux([H1|T1], [H2|T2], Tr, [Rest|Rez]):-
    Sum is H1 + H2 + Tr,
    Rest is Sum mod 10,
    Div is Sum div 10,
    sumaAux(T1, T2, Div, Rez).

% suma(A:list, B:list, Rez:list)
suma(A, B, Rez):-
    inverseaza(A, A1),
    inverseaza(B, B1),
    sumaAux(A1, B1, 0, RezInv),
    inverseaza(RezInv, Rez).
