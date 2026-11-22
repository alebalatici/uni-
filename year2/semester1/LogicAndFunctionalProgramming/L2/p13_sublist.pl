% adauga_final(E:integer, L:list, Rez:list)
adauga_final(E, [], [E]):-!.
adauga_final(E, [H|T], [H|Rez]):-
    adauga_final(E, T, Rez).

% divisors(N:integer, D:integer, L:list)
divisors(N, D, []):-
    D * D > N, !.

divisors(N, D, [D]):-
    D * D =:= N, !.

divisors(N, D, [D|Rez]):-
    N mod D =:= 0,
    !,
    H is N div D,
    D1 is D + 1,
    divisors(N, D1, R1),
    adauga_final(H, R1, Rez).

divisors(N, D, Rez):-
    D1 is D + 1,
    divisors(N, D1, Rez).

% divisorsList(N:integer, Rez:list)
divisorsList(N, Rez):-
    divisors(N, 2, Rez).

% addDivisorsSublist(L:list, Rez:list)
addDivisorsSublist([], []):-!.
addDivisorsSublist([H|T], [H, L|Rez]):-
    divisorsList(H, L),
    addDivisorsSublist(T, Rez).
