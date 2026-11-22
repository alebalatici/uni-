%apare(E:integer, L:list)
apare(E, [E|_]):-!.
apare(E, [_|T]):-
    apare(E, T).

%intersectia(M1:list, M2:list, Rez)
intersectia([], _, []).
intersectia([H|T], M2, [H|Rez]):-
    apare(H, M2),
    !,
    intersectia(T, M2, Rez).

intersectia([_|T], M2, Rez):-
    intersectia(T, M2, Rez).

%lista(N:integer, M:integer, Rez:list)
lista(M, M, [M]):-!.
lista(N, M, [N|Rez]):-
    N < M,
    N1 is N+1,
    lista(N1, M, Rez).
