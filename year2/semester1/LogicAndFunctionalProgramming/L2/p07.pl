% adauga_final(E:integer, L:list, Rez:list)
adauga_final(E, [], [E]):-!.
adauga_final(E, [H|T], [H|Rez]):-
    adauga_final(E, T, Rez).

% inverseaza(L:list, Rez:list)
inverseaza([], []):-!.
inverseaza([H|T], Rez):-
    inverseaza(T, R1),
    adauga_final(H, R1, Rez).

% produsulList(C:integer, L:list, Rez:list)
produsulList(C, L, Rez):-
    inverseaza(L, L1),
    produsul(C, 0, L1, RezInv),
    inverseaza(RezInv, Rez).

% produsul(C:integer, T:integer, L:list, Rez:list)
produsul(_, 0, [], []):-!.
produsul(_, Tr, [], [Tr]):-!.
produsul(C, Tr, [H|T], [Rest|Rez]):-
    P is H * C + Tr,
    Rest is P mod 10,
    Div is P div 10,
    produsul(C, Div, T, Rez).
