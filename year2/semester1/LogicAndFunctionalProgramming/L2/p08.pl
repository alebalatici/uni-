% adauga_final(E:integer, L:list, Rez:list)
adauga_final(E, [], [E]):-!.
adauga_final(E, [H|T], [H|Rez]):-
    adauga_final(E, T, Rez).

% inverseaza(L:list, Rez:list)
inverseaza([], []):-!.
inverseaza([H|T], Rez):-
    inverseaza(T, R1),
    adauga_final(H, R1, Rez).

% succesorul(L:list, T:integer, Rez:list)
succesorul([], 1, [1]):-!.
succesorul([], _, []):-!.
succesorul([H|T], Tr, [Rest|Rez]):-
    S is H + Tr,
    Rest is S mod 10,
    Div is S div 10,
    succesorul(T, Div, Rez).

% succsesorulList(L:list, Rez:list)
succesorulList(L, Rez):-
    inverseaza(L, L1),
    succesorul(L1, 1, RezInv),
    inverseaza(RezInv, Rez).
