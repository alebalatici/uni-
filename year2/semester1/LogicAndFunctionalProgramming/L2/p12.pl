% inlocuieste(E:integer, V:integer, L:list, Rez:list)
inlocuieste(_, _, [], []):-!.
inlocuieste(E, V, [E|T], [V|Rez]):-
    !,
    inlocuieste(E, V, T, Rez).

inlocuieste(E, V, [H|T], [H|Rez]):-
    inlocuieste(E, V, T, Rez).
