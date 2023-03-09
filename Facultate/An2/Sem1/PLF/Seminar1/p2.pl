inversAux([],C,C).
inversAux([H|T],C,R):- inversAux(T,[H|C],R).

invers(L,R):- inversAux(L,[],R).
