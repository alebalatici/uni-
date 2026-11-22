% maxim(A:integer, B:integer, R:integer)
maxim(A, B, A):-
    A > B, !.
maxim(_, B, B).

% maximList(L:list, R:integer)
maximList([H], H):-!.
maximList([H|T], R):-
    maximList(T, R1),
    maxim(H, R1, R).

% pozE(E:integer, Ind:integer, L:list, Rez:list)
pozE(_, _, [], []):-!.
pozE(E, Ind, [E|T], [Ind|Rez]):-
    !,
    Ind1 is Ind + 1,
    pozE(E, Ind1, T, Rez).

pozE(E, Ind, [_|T], Rez):-
    Ind1 is Ind + 1,
    pozE(E, Ind1, T, Rez).

% pozMax(L:list, Rez:list)
pozMax(L, Rez):-
    maximList(L, M),
    pozE(M, 1, L, Rez).
