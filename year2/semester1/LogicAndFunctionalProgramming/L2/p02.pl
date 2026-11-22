% bucla_sortare(L:list, Rez:list)
bucla_sortare([], []):-!.
bucla_sortare([H], [H]):-!.
bucla_sortare([H1, H2|T], [H1|Rez]):-
    H1 =< H2,
    !,
    bucla_sortare([H2|T], Rez).

bucla_sortare([H1, H2|T], [H2|Rez]):-
    H1 > H2,
    bucla_sortare([H1|T], Rez).

% sortat(L:list)
sortat([]):-!.
sortat([_]):-!.
sortat([H1, H2|T]):-
    H1 =< H2,
    sortat([H2|T]).


% sortare(L:list, Rez:list):-
sortare(L, L):-
    sortat(L), !.

sortare(L, Rez):-
    not(sortat(L)),
    bucla_sortare(L, Rez1),
    sortare(Rez1, Rez).
