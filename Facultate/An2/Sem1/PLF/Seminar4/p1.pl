%Sir de nr intregi distincte. Generati toate subsirulrile care au aspect 
%de vale (invers fata de munte)
%


%candidat(l1...ln) = 1. l1, n>=1
%                    2. candidat(l2...ln), n>=2
%candidat(L: Lista, E: Intreg)
%Lista de nr intregi
%Model de flux (i,o) - nedet, (i,i) - det
%L -> lista din care se extrage un element candidat
%E -> elementul extras din lista L


candidat([H|_],H).
candidat([_,H2|T], R):- candidat([H2|T],R).

%solutie(l, f, c1...cn) = 1. c, f=0
%                         2. solutie(l, 1, x+c), x=candidat(l), x<c1, f=1
%                         3. solutie(l, 0, x+c), x=candidat(l), x!=candidat(c), x>c1
%
%solutie(L: Lista, F: Binar, C: Lista)
%Lista de nr intregi
%Model de flux (i,i,o) - nedet, (i,i,i) - det
%L -> lista din care extrag elementele care pentru a le pune in C
%F -> flag pt directie 0: elementele descresc, 1:elementele cresc
%C -> lista colectoare in care se construieste solutia

solutie(_, 0, C, C).
solutie(L, 1, [H|T], R):- candidat(L, E),
                          E < H,
                          solutie(L, 1, [E,H|T], R).
solutie(L, _, [H|T], R):- candidat(L, E),
                          E > H,
                          not(candidat([H|T], E)), 
                          solutie(L, 0, [E,H|T], R).


%solutieW(l) = solutie(l, 1, [x1,x2]), x1=candidat(l), x2=candidat(l), x1<x2.
%
%solutieW(L: Lista, R: Lista)
%Model de flux (i,o) - nedet, (i,i) - det

solutieW(L, R):- candidat(L, X1),
                 candidat(L, X2),
                 X1 < X2,
                 solutie(L, 1, [X1,X2], R).

%candidatList(l1..ln) = 1. (l1, []), n>=1
%                       2. (e, l1+r), (e,r) = candidatList(l2..ln), n>=2
%
%candidatList(L: Lista, E: Intreg, R: Lista)
%Model de flux: (i,o,o) - nedet, (i,i,i) - det, (i,i,o) etc

candidatList([H|_], H, []).
candidatList([H|T], E, [H|R]):- candidatList(T, E, R).









