%problema 5
%a. Sa se scrie un predicat care sterge toate aparitiile unui anumit atom dintr-o lista.

%deleteAp(E: Element, L: Lista, R: Lista)
%Lista = Element*
%Model de flux: (i,i,o),(i,i,i)
%E elementul care se sterge de cate ori apare in lista L
%L lista in care se cauta elementul E
%R lista L fara aparitiile elementului E

deleteAp(_, [], []).
deleteAp(E, [H|T], R):- H=E,
                        deleteAp(E, T, R).
deleteAp(E, [H|T], [H|R1]):- H\=E,
                             deleteAp(E, T, R1).


%b. Definiti un predicat care, dintr-o lista de atomi, produce o lista de 
% perechi (atom n), unde atom apare in lista initiala de nori. De ex: 
% numar([1, 2, 1, 2, 1, 3, 1], X) va produce X = [[1, 4], [2, 2], [3, 1]].

%deleteApNr(E: Element, L: Lista, R: Lista, N: Intreg)
%Lista = Element*
%Model de flux: (i,i,o,o), (i,i,i,o)
%E elemntul care se sterge de cate ori aprae in lista L
%L lista in care se cauta elemntul E
%N numarul aparitiilor lui E in L
%R lista L fara aparitiile elementului E

deleteApNr(_, [], [], 0).
deleteApNr(E, [H|T], R, N):- H=E,
                             deleteApNr(E, T, R, NT),
                             N is NT+1.
deleteApNr(E, [H|T], [H|R1], N):- H\=E,
                                  deleteApNr(E, T, R1, N).

%nrAparitii(e: Element, L: lista, N: Intreg)
%Lista = Element*
%Model de flux (i,i,o)
%E elementul ale carui aparitii se numara din lista L
%L lista in care cautam numarul aparitiilor lui E
nrAparitii(_,[],0).
nrAparitii(E,[H|T],N):- E=H,
                        nrAparitii(E,T,NT),
                        N is NT+1.
nrAparitii(E,[H|T],N):- E\=H,
                        nrAparitii(E,T,N).




%makePair(L: Lista, R: Lista)
%Model de flux: (i,o), (i,i)
%L lista din care se produc perechiile (atom, n)
%R lista de perechi (atom, n), unde atom apare in lista L de n ori

makePairOne([], []).
makePairOne([H|T], R):- deleteApNr(H, [H|T], R1, N),
                        makePairOne(R1,R2),
                        R = [[H,N]|R2].

makePairTwo([],[]).
makePairTwo([H|T], R):- nrAparitii(H, [H|T], N),
                        deleteAp(H, [H|T], R1),
                        makePairTwo(R1, R2),
                        R = [[H,N]|R2].
                   
