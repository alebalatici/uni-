% adauga_final(E:integer, L:list, Rez:list)
adauga_final(E, [], [E]):-!.
adauga_final(E, [H|T], [H|Rez]):-
    adauga_final(E, T, Rez).

% inversa(L:list, Rez:list)
inversa([], []):-!.
inversa([H|T], Rez):-
    inversa(T, R1),
    adauga_final(H, R1, Rez).

% predecesorList(L:list, Rez:list)
predecesorList(L, Rez):-
    inversa(L, L1),
    predecesor(L1, 1, RezInv),
    inversa(RezInv, Rez).

% predecesor(L:list, Tr:integer, Rez:list)
predecesor([0], 1, [-1]):-!.
predecesor([], 0, []):-!.
predecesor([H|T], 0, [H|Rez]):-
    !,
    predecesor(T, 0, Rez).

predecesor([0|T], 1, [9|Rez]):-
    !,
    predecesor(T, 1, Rez).

predecesor([H|T], 1, [R|Rez]):-
    R is H - 1,
    predecesor(T, 0, Rez).
