%Dandu-se o lista(multime), sa se genereze toate submultimile cu k elemente ale listei.
%subm(l1...ln, k) = 1. [l1], k = 1, n>=1
%                   2. l1 + subm(l2...ln, k-1), n>=1, k>1
%                   3. subm(l2...ln, k), n>=1, k>=1
%

%subm(L: Lista, K: Intreg, R:Lista)
%Model de flux (i,i,o) nedet, (i,i,i) det
subm([H|_], 1, [H]).
subm([H|T], K, [H|[H1|R]]):- K > 1,
                             K2 is K - 1,
                             subm(T, K2, [H1|R]),
                             H < H1.
subm([_|T], K, R):- K >= 1,
                    subm(T, K, R).
