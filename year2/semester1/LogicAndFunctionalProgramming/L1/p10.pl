%intercalare(E:integer, N:integer, L:list, Rez:list)
intercalare(E, 1, L, [E|L]):-!.
intercalare(E, N, [H|T], [H|Rez]):-
    N > 0,
    N1 is N-1,
    intercalare(E, N1, T, Rez).

%cmmdc(A:integer, B:integer, Rez:integer)
cmmdc(A, 0, A):-!.
cmmdc(A, B, Rez):-
    B > 0,
    R is A mod B,
    cmmdc(B, R, Rez).

%cmmdcList(L:list)
cmmdcList([E], E):-!.
cmmdcList([H|T], Rez):-
    cmmdcList(T, R1),
    cmmdc(H, R1, Rez).
