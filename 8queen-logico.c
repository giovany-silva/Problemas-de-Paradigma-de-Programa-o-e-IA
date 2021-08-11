  :- style_check(-singleton).

  solucao([]).

  solucao([X/Y | Outras]) :-
    solucao(Outras),
    member(Y, [1, 2, 3, 4, 5, 6, 7, 8]),
    naoataca(X/Y, Outras).


  naoataca(_, []).

  naoataca( X/Y,[X1/Y1 | Outras]) :-
    Y =\= Y1,
    Y1 - Y =\= X1 - X,
    Y1 - Y =\= X - X1,
    naoataca(X/Y, Outras).


  member(X,[X | L]).

  member(X,[Y | L]) :-
    member(X, L).

  template([1/Y1, 2/Y2, 3/Y3, 4/Y4, 5/Y5, 6/Y6, 7/Y7, 8/Y8]).


