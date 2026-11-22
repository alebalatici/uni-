% interclasare(A:list, B:list, Rez:list)
interclasare(A, [], A):-!.
interclasare([], B, B):-!.
interclasare([], [], []):-!.
interclasare([H1|T1], [H2|T2], [H1|Rez]):-
    H1 < H2,
    !,
    interclasare(T1, [H2|T2], Rez).

interclasare(A, [H2|T2], [H2|Rez]):-
    interclasare(A, T2, Rez).

% sterge(E:integer, L:list, Rez:list)
sterge(_, [], []):-!.
sterge(E, [E|T], Rez):-
    !,
    sterge(E, T, Rez).

sterge(E, [H|T], [H|Rez]):-
    sterge(E, T, Rez).

% multime(L:list, Rez:list)
multime([], []):-!.
multime([H|T], [H|Rez]):-
    sterge(H, T, T1),
    multime(T1, Rez).

% interclasareList(A:list, B:list, Rez:list)
interclasareList(A, B, Rez):-
    interclasare(A, B, R1),
    multime(R1, Rez).
