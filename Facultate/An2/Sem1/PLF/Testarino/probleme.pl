%1. a) Sa se scrie un predicat care intoarce diferenta a doua multimi
%   b) Sa se scrie un predicat care adauga intr-o lista dupa fiecare element parvaloarea 1.

%a) Implementare:
%diff(L1, L2, R) = 1. R, daca L1 = L2
%                  2. diff(L1, L2, R), L1 = [H|T], not(member(H, L2)), R = [H|R1]
%                  3. diff(L1, L2, R), L1 = [H|T], member(H, L2), R = R1
%                  4. diff(L1, L2, R), L1 = [], R = []
%b) Implementare:
%add(L, R) = 1. R, daca L = []
%            2. add(L, R), L = [H|T], H mod 2 = 0, R = [H, 1|R1]
%            3. add(L, R), L = [H|T], H mod 2 = 1, R = [H|R1]

%diff(L1: Lista, L2: Lista, R: Lista)
%Model de flux: (i,i,o) - nedeterminist
%               (i,i,i) - determinist
%L1 - prima lista
%L2 - a doua lista
%R - rezultatul

diff([], _, []).
diff([H|T], L2, [H|R]):- not(member(H, L2)), diff(T, L2, R).
diff([H|T], L2, R):- member(H, L2), diff(T, L2, R).

%add(L: Lista, R: Lista)
%Model de flux: (i,o) - nedeterminist
%               (i,i) - determinist
%L - lista
%R - rezultatul

add([], []).
add([H|T], [H, 1|R]):- H mod 2 =:= 0, add(T, R).
add([H|T], [H|R]):- H mod 2 =:= 1, add(T, R).

%2. a) Sa se scrie un predicat care determina cel mai mic multiplu comun alelementelor unei liste formate din numere intregi
%   b) Sa se scrie un predicat care adauga dupa 1-ul, al 2-lea, al 4-lea, al8-lea ...element al unei liste o valoare vdata.

%a) Implementare:
%cmmdc(A, B, R) = 1. R, daca A = B
%                 2. cmmdc(A, B, R), A > B, R = cmmdc(A-B, B)
%                 3. cmmdc(A, B, R), A < B, R = cmmdc(A, B-A)
%                 4. cmmdc(A, B, R), A = 0, R = B
%                 5. cmmdc(A, B, R), B = 0, R = A
%cmmc(A, B, R) = 1. R, daca A = 0 sau B = 0
%                 2. cmmc(A, B, R), R = A*B/cmmdc(A, B)
%b) Implementare:
%add(L, V, R) = 1. R, daca L = []
%                2. add(L, V, R), L = [H|T], R = [H, V|R1], add(T, V, R1, 2)
%                3. add(L, V, R), L = [H|T], R = [H|R1], add(T, V, R1, 1)
%                4. add(L, V, R), L = [], R = []

%cmmdc(A: Numar, B: Numar, R: Numar)
%Model de flux: (i,i,o) - nedeterminist
%               (i,i,i) - determinist
%A - primul numar
%B - al doilea numar
%R - rezultatul

cmmdc(A, A, A).
cmmdc(A, B, R):- A > B, A1 is A-B, cmmdc(A1, B, R).
cmmdc(A, B, R):- A < B, B1 is B-A, cmmdc(A, B1, R).
cmmdc(0, B, B).
cmmdc(A, 0, A).

%cmmc(A: Numar, B: Numar, R: Numar)
%Model de flux: (i,i,o) - nedeterminist
%               (i,i,i) - determinist
%A - primul numar
%B - al doilea numar
%R - rezultatul

cmmc(A, _, R):- A =:= 0, R = 0.
cmmc(_, B, R):- B =:= 0, R = 0.
cmmc(A, B, R):- R is A*B/cmmdc(A, B).

%add(L: Lista, V: Numar, R: Lista, I: Numar)
%Model de flux: (i,i,o,i) - nedeterminist
%               (i,i,i,i) - determinist
%L - lista
%V - valoarea
%R - rezultatul
%I - contor

add([], _, [], _).
add([H|T], V, [H, V|R], I):- I mod 2 =:= 0, I1 is I+1, add(T, V, R, I1).
add([H|T], V, [H|R], I):- I mod 2 =:= 1, I1 is I+1, add(T, V, R, I1).

%3. Sa se scrie un predicat care transforma o listaintr-o multime, in ordinea primei aparitii. Exemplu: [1,2,3,1,2] e transformat in [1,2,3].

%Implementare:
%multime(L, R) = 1. R, daca L = []
%                2. multime(L, R), L = [H|T], not(member(H, R)), R = [H|R1]
%                3. multime(L, R), L = [H|T], member(H, R), R = R1

%multime(L: Lista, R: Lista)
%Model de flux: (i,o) - nedeterminist
%               (i,i) - determinist
%L - lista
%R - rezultatul

multime([], []).
multime([H|T], [H|R]):- not(member(H, R)), multime(T, R).
multime([H|T], R):- member(H, R), multime(T, R).

%4. Sa se scrie un predicat care determina daca un element se afla in lista.

%Implementare:
%member(E, L) = 1. E, daca L = []
%               2. member(E, L), L = [H|T], E = H
%               3. member(E, L), L = [H|T], E = E1

%member(E: Numar, L: Lista)
%Model de flux: (i,i) - nedeterminist
%               (i,i) - determinist
%E - elementul
%L - lista

memberM(E, [E|_]).
memberM(E, [_|T]):- memberM(E, T).

%5. Sa se scrie un predicat care inverseaza elementele unei liste.

%Implementare:
%reverse(L, R) = 1. R, daca L = []
%                2. reverse(L, R), L = [H|T], R = R1, R1 = [H|R2]

%reverse(L: Lista, R: Lista)
%Model de flux: (i,o) - nedeterminist
%               (i,i) - determinist
%L - lista
%R - rezultatul

reverse(L, R):- reverse(L, [], R).
reverse([], C, C).
reverse([H|T], C, R):- reverse(T, [H|C], R).

%6. Definiti un predicat care determina suma a doua numere scrise in reprezentare de lista.

%sumAux(A, B, C, R)
sumAux([], [], 0, []):-!.
sumAux([], [], C, [C]):-!.
sumAux([], [H|T], C, [H2|R]):- NH is H+C, H2 is NH mod 10, NC is NH div 10, sumAux(T, [], NC, R).
sumAux([H|T], [], C, [H2|R]):- NH is H+C, H2 is NH mod 10, NC is NH div 10, sumAux(T, [], NC, R).
sumAux([H|T], [H1|T1], C, [H2|R]):- NH is H + H1 + C, H2 is NH mod 10, NC is NH div 10, sumAux(T, T1, NC, R).

sum(A, B, R):- reverse(A, A1), reverse(B, B1), sumAux(A1, B1, 0, R1), reverse(R1, R).

%7. Definiti un predicat care determina diferenta a doua numere scrise in reprezentare de lista.

%subAux(A, B, C, R)
subAux([], [], 0, []):-!.
subAux([], [], C, [C]):-!.
subAux([], [H|T], C, [H2|R]):- NH is H-C, H2 is NH mod 10, NH < 0, !, NC is 1, subAux(T, [], NC, R).
subAux([], [H|T], C, [H2|R]):- NH is H-C, H2 is NH mod 10, NC is NH div 10, subAux(T, [], NC, R).
subAux([H|T], [], C, [H2|R]):- NH is H-C, H2 is NH mod 10, NH < 0, !, NC is 1, subAux(T, [], NC, R).
subAux([H|T], [], C, [H2|R]):- NH is H-C, H2 is NH mod 10, NC is NH div 10, subAux(T, [], NC, R).
subAux([H|T], [H1|T1], C, [H2|R]):- NH is H - H1 - C, H2 is NH mod 10, NH < 0, !, NC is 1, subAux(T, T1, NC, R).
subAux([H|T], [H1|T1], C, [H2|R]):- NH is H - H1 - C, H2 is NH mod 10, NC is NH div 10, subAux(T, T1, NC, R).


sub(A, B, R):- reverse(A, A1), reverse(B, B1), subAux(A1, B1, 0, R1), reverse(R1, R).







