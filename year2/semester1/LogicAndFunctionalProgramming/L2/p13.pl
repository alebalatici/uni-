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

% addSublist(L1:list, L2:list, Rez:list):-
addSublist([], L2, L2):-!.
addSublist([H|T], L2, [H|Rez]):-
    addSublist(T, L2, Rez).

% addDivisors(L:list, I:list, Rez:list)
addDivisors([], [], []):-!.
addDivisors([H|T], [], Rez):-
    !,
    divisorsList(H, R1),
    addDivisors(T, [H|R1], Rez).

addDivisors(L, [H|T], [H|Rez]):-
    addDivisors(L, T, Rez).

% addDivisorsList(L:list, Rez:list)
addDivisorsList(L, Rez):-
    addDivisors(L, [], Rez).
