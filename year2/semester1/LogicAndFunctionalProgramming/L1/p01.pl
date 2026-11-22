apare(E, [E|_]):-!.
apare(E, [_|T]):-
    apare(E, T).

%model matematic
%diferenta(M1, M2)
%[] daca M1 este vida
%l1 + diferenta(l2l3...ln, M2), daca l1 nu apare in M2
%diferenta(l2l3...ln, M2), daca l1 apare in M2
diferenta([], _, []).

diferenta([H|T], M2, [H|Rez]):-
    not(apare(H, M2)),
    !,
    diferenta(T, M2, Rez).

diferenta([_|T], M2, Rez):-
    diferenta(T, M2, Rez).

%model matematic
%adauga(L, Rez)
%[] daca L este vida
%l1 + 1 + adauga(l2...ln), daca l1 este par
%adauga(l2...ln), altfel
adauga([], []).
adauga([H|T], [H, 1 | Rez]):-
    H mod 2 =:= 0,
    !,
    adauga(T, Rez).
adauga([H|T], [H|Rez]):-
    adauga(T, Rez).
