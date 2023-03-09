%Dundu-se o lista liniara sa se elimine elementele de pe pozitiile 1, 3, 7...
%
%elimina(L: Lista, PC: Intreg, PR: Intreg, R: Lista)
%Model de flux (i,i,i,o)

elimina([], _, _, []).
elimina([H|T], PC, PR, R):- PC =:= PR, !,
                            elimina(T, PC+1, PR*2+1, R).
elimina([H|T], PC, PR, [H|R]):- elimina(T, PC+1, PR, R).
