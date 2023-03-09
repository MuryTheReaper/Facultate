
%13. "Colorarea hartilor".
%Se dau n tari. Se cer toate modalitatile de colorarea celor n tari cu m culori,
%astfel inca doua tari vecine sa nu fie colorate la fel.

%candidat(N) = 1. N
%              2. candidat(N-1), N>1

%candidat(N: Intreg, X: Intreg)
%Model de flux: (i,o) - nedeterminist
%               (i,i) - determinist
%N - numarul de la care pornim generarea numerelor descrescatoare
%X - numarul generat

candidat(N, N).
candidat(N, X):- N>1, NN is N-1, candidat(NN, X).


%vecini(X, Y, L) = true, [X,Y] sau [Y,X] apartine lui L
%                  false, altfel

%vecini(X: Intreg, Y: Intreg, L: Lista)
%Model de flux: (i,i,i) - determinist
%X - numarul unui nod
%Y - numarul unui nod
%L - lista de muchii

vecini(X, Y, L) :- member([X, Y], L).
vecini(X, Y, L) :- member([Y, X], L).

%valid(C, X, L, COL1(A,B)...COLn) = true, COL = vid (nu are vecini colorati cu aceeasi culoare)
%                                   valid(C, X, L, COL2...COLn), vecini(X, COL1.A, L) = true, C != COL1.B
%                                   valid(C, X, L, COL2...COLn), vecini(X, COL1.A, L) = false
%                                   false, altfel

%valid(C: Intreg, X: Intreg, L: Lista, COL: Lista)
%Lista COL contine perechi de forma (A, B), unde A este numarul unui nod si B este culoarea acestuia
%Model de flux: (i,i,i,i) - determinist
%C - culoarea unui nod
%X - numarul unui nod
%L - lista de muchii
%COL - lista de perechi (nod, culoare) curenta

valid(_, _, _, []):- true.
valid(C, X, L, [[A,B]|T]):- vecini(X, A, L), C \= B, valid(C, X, L, T).
valid(C, X, L, [[A,_]|T]):- not(vecini(X, A, L)), valid(C, X, L, T).

%solutie(N, M, L, C) = 1. C, daca lungimea lui C este N
%                      2. solutie(N, M, L, [E,X] + C), X = candidat(M),
%                           valid(X, N, L, C) = true, E = N - lungime(C)

%solutie(N: Intreg, M: Intreg, L: Lista, C: Lista, S: Lista)
%Model de flux: (i,i,i,i,o) - nedeterminist
%               (i,i,i,i,i) - determinist
%N - numarul de noduri
%M - numarul de culori
%L - lista de muchii
%C - lista de perechi (nod, culoare) curenta (solutie partiala)
%S - solutia, lista de perechi (nod, culoare)

solutie(N, _, _, C, C):- length(C, N).
solutie(N, M, L, C, S):- candidat(M, X), length(C, LEN), E is N-LEN, E >= 0, valid(X, E, L, C),
                         solutie(N, M, L, [[E, X]|C], S).

%map(N, M, L, S) = solutie(N, M, L, [], S)

%map(N: Intreg, M: Intreg, L: Lista, S: Lista)
%Model de flux: (i,i,i,o) - nedeterminist
%               (i,i,i,i) - determinist
%N - numarul de noduri
%M - numarul de culori
%L - lista de muchii
%S - solutia, lista de perechi (nod, culoare)

map(N, M, L, S):- solutie(N, M, L, [], S).
