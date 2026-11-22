%true, daca M = [], N = []
%false daca m1 != n1
test_egal([], []):-!.
test_egal([H|T1], [H|T2]):-
    test_egal(T1, T2).

%model matematic
%nth_element(N, L, Rez)
%l1, N = 1
%nth_element(N - 1, l2...l3, Rez), altfel
nth_element(1, [H|_], H):-!.
nth_element(N, [_|T], Rez):-
    N1 is N-1,
    nth_element(N1, T, Rez).
