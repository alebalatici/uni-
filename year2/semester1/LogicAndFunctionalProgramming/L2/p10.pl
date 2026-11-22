% pow2(N:integer)
pow2(1):-!.
pow2(N):-
    N > 0,
    N mod 2 =:= 0,
    N1 is N div 2,
    pow2(N1).

% valid(N:integer)
valid(1):-!.
valid(N):-
    not(pow2(N)),
    N1 is N div 2,
    N2 is N1 + 1,
    pow2(N2).

% adauga(E:integer, Ind:integer, L:list, Rez:list)
adauga(_, _, [], []):-!.
adauga(E, Ind, [H|T], [H, E|Rez]):-
    valid(Ind),
    !,
    Ind1 is Ind + 1,
    adauga(E, Ind1, T, Rez).

adauga(E, Ind, [H|T], [H|Rez]):-
    Ind1 is Ind + 1,
    adauga(E, Ind1, T, Rez).

% adaugaList(E:integer, L:list, Rez:list)
adaugaList(E, L, Rez):-
    adauga(E, 1, L, Rez).
