% adaugaInceput(E:integer, L:list, Rez:list)
adaugaInceput(E, L, [E|L]).

% adaugaFinal(E:integer, L:list, Rez:list)
adaugaFinal(E, [], [E]):-!.
adaugaFinal(E, [H|T], [H|Rez]):-
    adaugaFinal(E, T, Rez).

% secvNrPare(L:list, Current:list, Rez:list)
secvNrPare([], [], []):-!.
secvNrPare([], L, [L]):-!.

secvNrPare([H|T], L, Rez):-
    H mod 2 =:= 0,
    !,
    adaugaFinal(H, L, L1),
    secvNrPare(T, L1, Rez).

secvNrPare([_|T], [], Rez):-
    !,
    secvNrPare(T, [], Rez).

secvNrPare([_|T], L, [L|Rez]):-
    secvNrPare(T, [], Rez).
