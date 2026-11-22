%apare(E:integer, L:list)
apare(E, [E|_]):-!.
apare(E, [_|T]):-
    apare(E, T).

%multime(L:list)
multime([]):-!.
multime([H|T]):-
    not(apare(H, T)),
    multime(T).

%elim(E:integer, Count:integer, L:list, Rez:list)
elim(_, 3, L, L):-!. %daca s-au eliminat 3 aparitii
elim(_, _, [], []):-!. %daca s-a ajuns la finalul listei
elim(E, C, [E|T], Rez):-
    !,
    C1 is C+1,
    elim(E, C1, T, Rez).

elim(E, C, [H|T], [H|Rez]):-
    elim(E, C, T, Rez).

%elimina(E:integer, L:list, Rez:list)
elimina(E, L, Rez):-
    elim(E, 0, L, Rez).
