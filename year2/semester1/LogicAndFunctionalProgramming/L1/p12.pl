%substituie(E1, E2, L, Rez).
substituie(_,_,[],[]):-!.
substituie(E1, E2, [E1|T], [E2|Rez]):-
    !,
    substituie(E1, E2, T, Rez).
substituie(E1, E2, [H|T], [H|Rez]):-
    substituie(E1, E2, T, Rez).

%sublista(M, N, Count, L, Rez).
sublista(_, N, Count, _, []):-
    Count > N,
    !.

sublista(_, _, _, [], []):-!.

sublista(M, N, Count, [H|T], [H|Rez]):-
    Count >= M,
    Count =< N,
    C1 is Count+1,
    !,
    sublista(M, N, C1, T, Rez).

sublista(M, N, Count, [_|T], Rez):-
    C1 is Count+1,
    sublista(M, N, C1, T, Rez).
