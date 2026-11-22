% sterg(L:list, F:integer, Rez:list)
sterg([], _, []):-!.
sterg([_], 1, []):-!.
sterg([H], 0, [H]):-!.
sterg([H1, H2|L], _, Rez):-
    Dif is H2 - H1,
    Dif =:= 1,
    !,
    sterg([H2|L], 1, Rez).

sterg([_, H2|L], 1, Rez):-
    !,
    sterg([H2|L], 0, Rez).

sterg([H1, H2|L], 0, [H1|Rez]):-
    sterg([H2|L], 0, Rez).

% stergList(L:list, Rez:list)
stergList(L, Rez):-
    sterg(L, 0, Rez).
