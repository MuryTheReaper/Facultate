%Se da o lista eterogena cu numere. Sa se eleimint din subliste elementele pare.
%ex: [1,2,[4,5,6],3,[10]]=>[1,2,[5],3,[]]

elimPar([],[]).
elimPar([H|T], R):- H mod 2 =:= 0,!,
                    elimPar(T, R).
elimPar([H|T], R):- elimPar(T, R1),
                    R = [H|R1].

elimSublist([], []).
elimSublist([H|T], R):- is_list(H),!,
                        elimPar(H, R1),
                        elimSublist(T,RT),
                        R = [R1|RT].
elimSublist([H|T], R):- elimSublist(T, R1),
                        R = [H|R1].

