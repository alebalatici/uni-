%cmmdc(A:integer, B:integer)
cmmdc(A, 0, A).
cmmdc(A, B, R):-
    B>0,
    Rest is A mod B,
    cmmdc(B, Rest, R).

cmmdcList([E], E).
cmmdcList([H|T], R):-
    cmmdcList(T, R1),
    cmmdc(H, R1, R), !.

power2(1):-!.
power2(E):-
    E > 0,
    E mod 2 =:= 0,
    E1 is E div 2,
    power2(E1).

%adauga(Val:integer, Count:integer, L:list, Rez:list)
adauga(_, _, [], []).
adauga(E, C, [H|T], [H, E|Rez]):-
    power2(C),
    C1 is C+1,
    adauga(E, C1, T, Rez), !.
adauga(E, C, [H|T], [H|Rez]):-
    C1 is C+1,
    adauga(E, C1, T, Rez).
