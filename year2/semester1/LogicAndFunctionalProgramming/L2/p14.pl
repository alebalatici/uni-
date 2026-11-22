%adauga_final(E:integer, L:list, Rez:list)
adauga_final(E, [], [E]).
adauga_final(E, [H|T], [H|Rez]):-
    adauga_final(E, T, Rez).

%reverse(L:list)
inversa([], []).
inversa([E], [E]).
inversa([H|T], Rez):-
    reverse(T, R1),
    adauga_final(H, R1, Rez).

%predecesor_reverse(L:list, T:integer, Rez:list)
predecesor_reverse([], _, []):-!.
predecesor_reverse(L, 0, L):-!.

predecesor_reverse([0|T], Tr, [9|Rez]):-
    predecesor_reverse(T, Tr, Rez), !.

predecesor_reverse([H|T], _, [R|Rez]):-
    H > 0,
    R is H-1,
    predecesor_reverse(T, 0, Rez), !.

%predecesor(L:list, Rez:integer)
predecesor([E], Rez):-
    E < 10,
    Rez is E - 1, !.

predecesor(L, Rez):-
    inversa(L, R1),
    predecesor_reverse(R1, 1, R2),
     inversa(R2, Rez).

%predecesorList(L:list of lists, Rez:list of lists)
predecesorList([], []).
predecesorList([H|T], [R|Rez]):-
    is_list(H),
    !,
    predecesor(H, R),
    predecesorList(T, Rez).

predecesorList([H|T], [H|Rez]):-
    predecesorList(T, Rez).
