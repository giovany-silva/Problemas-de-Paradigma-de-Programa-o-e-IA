mover(estado(embaixo,nacaixa,embaixo,naotem),
     bastao,
     estado(embaixo,nacaixa,embaixo,tem)).
mover(estado(X,nochao,X,T),
    sobe,
    estado(X,nacaixa,X,T)).
mover(estado(X1,nochao,X1,T),
     empurrar(X1,X2),
     estado(X2,nochao,X2,T)).
mover(estado(X1,nochao,C,T),
    anda(X1,X2),
    estado(X2,nochao,C,T)).
podepegar(estado(_,_,_,tem)).
podepegar(Estado1) :-
    mover(Estado1,_,Estado2),
    podepegar(Estado2).
