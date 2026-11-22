% prim(N:integer)
prim(N, D):-
    D1 is D * D,
    D1 > N, !.
prim(N, D):-
    N mod D =\= 0,
    D1 is D + 2,
    prim(N, D1).

% primN(N:integer)
primN(2):-!.
primN(N):-
    N > 2,
    N mod 2 =\= 0,
    prim(N, 3).

% dubleazaPrime(L:list, Rez:list)
dubleazaPrime([], []):-!.
dubleazaPrime([H|T], [H, H|Rez]):-
    primN(H),
    !,
    dubleazaPrime(T, Rez).

dubleazaPrime([H|T], [H|Rez]):-
    dubleazaPrime(T, Rez).
