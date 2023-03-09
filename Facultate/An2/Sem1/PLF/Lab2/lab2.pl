%Problema 12
%a)
%Sa se inlocuiasca toate aparitiile unui element dintr-o lista cu un alt element.

%swapElemInList(E: ELement, X:Element, L:Lista, R:Lista)
%Lista = Element*
%Model flux: (i,i,i,o),(i,i,i,i) - determinist
%E elementul din lista care va fi inlocuit cu X ori de cate ori apare
%X un element cu care se inlocuiesc fiecare aparitie al lui E
%L lista in care se cauta E ca sa fie inloci cu X
%R lista in care toate aparitiile lui E au fost inlocuite cu X

swapElemInList(_, _, [], []):-!.
swapElemInList(E, X, [H|T], [X|R1]):- H=E,!,
                                      swapElemInList(E, X, T, R1).
swapElemInList(E, X, [H|T], [H|R1]):- H\=E,
                                      swapElemInList(E, X, T, R1).

%Se da o lista eterogena, formata din numere intregi si liste de numere intregi.
%Se cere ca toate aparitiile elementului maxim (dintre valorile intregi ale listei) 
%sa fie inlocuite in fiecare sublista cu maximul sublistei respective. De ex:
%[1, [2, 5, 7], 4, 5, [1, 4], 3, [1, 3, 5, 8, 5, 4], 5, [5, 9, 1], 2] =>
%[1, [2, 7, 7], 4, 5, [1, 4], 3, [1, 3, 8, 8, 8, 4], 5, [9, 9, 1], 2]

%max(X:Intreg, Y:Intreg, R:Intreg)
%Obs: elementul neutru este considerat lista vida
%X si Y: doua elemente care se compara pentru a gasi maximul
%R: maximul dintre cele doua numere X si Y

max(X, [], X):-!.
max([], X, X):-!.
max(X, Y, R):- X>Y,!,
               R is X.
max(X, Y, R):- X=<Y,
               R is Y.

%maxInListEter(L:Lista, R:Intreg)
%Lista poate fi eterogena
%Obs: Daca nu exista niciun element de tip numar in lista L, R va fi lista goala
%Model de flux: (i,o), (i,i) - determinist
%L lista din care se calculeaza elementul maxim R
%R intregul din lista L cu valoare maxima

maxInListEter([],[]).
maxInListEter([H|[]], H):- number(H),!.
maxInListEter([H|[]], []):- is_list(H),!.
maxInListEter([H|T], R):- number(H),!,
                          maxInListEter(T, R1),
                          max(H, R1, RT),
                          R is RT.
maxInListEter([H|T], R):- is_list(H),
                          maxInListEter(T, R1),
                          R = R1.

%swapMaxInSublistAux(E:Intreg, L:Lista, R:Lista)
%Lista poate fi eterogena
%Model de flux: (i,i,o), (i,i,i) - determinist
%E: Intregul care este inlocui in elementele de tip lista din L cu maxiumul din sublista
%L: Lista in care in elementele de tip lista se inlocuieste E cu maximul sublistei
%R: Lista rezultata prin inlocuirea elementului E din subliste cu maximul sublistei

swapMaxInSublistAux(_, [], []):-!.
swapMaxInSublistAux(E, [H|T], R):- is_list(H),!,
                                   maxInListEter(H, MAX),
                                   swapElemInList(E, MAX, H, R1),
                                   swapMaxInSublistAux(E, T, R2),
                                   R = [R1|R2].
swapMaxInSublistAux(E, [H|T], R):- number(H),
                                   swapMaxInSublistAux(E, T, R1),
                                   R = [H|R1].

%swapMaxInSublist(L:Lista, R:Lista)
%Lista poate fi eterogena
%Model de flux: (i,o),(i,i) - determinist
%L lista in care toate aparitiile elementului maxim 
%(dintre valorile intregi ale listei) sunt inlocuite 
%in fiecare sublista cu maximul sublistei respective
%R lista rezultata prin inlocuirea tuturor aparitiilor elementului maxim
%(dintre valorile intregi din L) din sublista cu maximul sublistei respective

swapMaxInSublist(L, R):- maxInListEter(L, MAX), 
                         swapMaxInSublistAux(MAX, L, RT),
                         R = RT.
