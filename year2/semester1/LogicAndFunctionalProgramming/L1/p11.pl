%suma3(A:integer, B:integer, Rez:integer)
suma2(A, B, Rez):-
    Rez is A + B, !.

%diferenta2(A:integer, B:integer, Rez:integer)
diferenta2(A, B, Rez):-
    Rez is A - B, !.

%sumaAlternanta(L:list, S:integer)
sumaAlternanta([], 0):-!.
sumaAlternanta([E], E):-!.
sumaAlternanta([E1, E2|T], Rez):-
    sumaAlternanta(T, R1),
    diferenta2(E1, E2, RDif),
    suma2(RDif, R1, Rez).

%vale(L:list)
vale([E1, E2|T]):-
    E1 > E2,
    !,
    scade([E2|T]).

scade([E1, E2|T]):-
    E1 > E2,
    !,
    scade([E2|T]).

scade([E1, E2|T]):-
    E1 < E2,
    !,
    creste([E2|T]).

creste([_]):-!.
creste([E1, E2|T]):-
    E1 < E2,
    !,
    creste([E2|T]).
