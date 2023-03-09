%Dandu-se o lista liniara, sa se eleimine toate elementele care se repeta.
%Ex: [1, 2, 3, 2, 1, 4, 1] -> [3, 4]

%exista(L: Lista, E: Element)
%Model de flux: (i, i), (i, o)

exista([H|_], E):- H = E,!.
exista([_|T], E):- exista(T, E).

%sterge(L: Lista, E: Element, R: Lista)
%Model de flux: (i,i,o), (i,i,i)

sterge([], _, []).
sterge([H|T], E, R):- H = E,!,
                      sterge(T, E, R1),
                      R = R1.
sterge([H|T], E, [H|R1]):- sterge(T, E, R1).

%rezolva(L: Lista, R: Lista)
%Model de flux: (i,o)

rezolva([], []).
rezolva([H|T], R):- exista(T, H),
                    sterge(T, H, S),!,
                    rezolva(S, R).
rezolva([H|T], [H|R]):- rezolva(T, R).
