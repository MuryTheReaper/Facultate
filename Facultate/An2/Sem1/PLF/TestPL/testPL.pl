%Test Prolog
%17. Sa se scrie un predicat care, primind o lista, intoarce multimea
%tuturor perechiilor din lista. 
%De exemplu: [1,2,3,4] -> [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]].

%perechi(e, l1...ln) = [], n = 0
%                      [e, l1] + perechi(e, l2...ln), n>0

%perechi(E: Intrg, L: Lista, R: Lista)
%Model de flux: (i,i,o), (i,i,i), deterministe
%E -> elementul cu care se fac perechiile
%L -> lista de elemente cu care se din care se fac perechiile [E, Lm]
%R -> lista cu perechiile formate din [E, Lm]

perechi(_, [], []).
perechi(E, [H|T], [[E,H]|R]):- perechi(E, T, R).



%concatenare(l1...ln, z) = [], l si z sunt vide
%                          z, l este vid
%                          l1 + concatenare(l2...ln, z)

%concatenare(L: Lista, Z: Lista, R: Lista)
%Model de flux (i, i, o), (i, i, i), deterministe
%L -> lista de concatenat
%Z -> lista de concatenat
%R -> concatenarea listelor L is Z

concatenare([], [], []).
concatenare([], L, L).
concatenare([H|T], L, [H|R]):- concatenare(T, L, R).



%multime(l1...ln) = [], n = 1
%                   conactenare(perechi(l1, l2...ln),multime(l2...ln)),  n > 1

%multime(L: Lista, R: Lista)
%Model de flux: (i,o), (i,i), deterministe
%L -> lista din care se formeaza perechiile
%R -> lista cu toate perechiile din L

multime([_], []).
multime([H1, H2], R):- !, perechi(H1, [H2], R).
multime([H|T], RR):- perechi(H, T, RT), multime(T, R), !, concatenare(RT, R, RR).
