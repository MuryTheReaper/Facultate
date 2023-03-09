%Lista eterogena. Sa numaram sublistele care au aspect de munte(1,2,3,2,1)
%ex: [5,[2,6,3],4,9,7,[1,6,8,7],[1,3,2,4],[1,2,3],11,[7,6,5]] => 2
%
%munteAux(L:Lista, D:Intreg)
%Lista = Intreg*
%L: lista pe care verificam proprietatea de munte
%D: flag directional(0- creste, 1-descreste)
%Model de flux: (i,i) determinist
munteAux([_], 1).
munteAux([H1,H2|T], 0):- H1<H2,!,
                         munteAux([H2|T], 0).
munteAux([H1,H2|T], _):- H1>H2,
                         munteAux([H2|T], 1).

munte([H1,H2|T]):- H1<H2,
                   munteAux([H1,H2|T], 0). 
                    
%munteSublist(L, R)                    
munteSublist([], 0).
munteSublist([H|T], R):- is_list(H),
                         munte(H),!,
                         munteSublist(T, R1),
                         R is R1+1.
munteSublist([_|T], R):- munteSublist(T, R).
                         

