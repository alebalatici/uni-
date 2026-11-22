reuniunea([], M2, M2):-!.
reuniunea([H|T], M2, [H|Rez]):-
    not(apare(H, M2)),
    !,
    reuniunea(T, M2, Rez).

reuniunea([_|T], M2, Rez):-
    reuniunea(T, M2, Rez).

%concat(M1:list, M2:list)
concat([], M2, M2):-!.
concat([H|T], M2, [H|Rez]):-
    concat(T, M2, Rez).

%cupleaza(E:integer, L:list, Rez:list of lists)
cupleaza(_, [], []):-!.
cupleaza(E, [H|T], [[E, H]|Rez]):-
    cupleaza(E, T, Rez).

%perechi(L:list, Rez:list)
perechi([], []):-!.
perechi([H|T], Rez):-
    cupleaza(H, T, PerechiH),
    perechi(T, PerechiT),
    concat(PerechiH, PerechiT, Rez).
