nrAparitii(_,[],0).
%nrAparitii(_,[],N):-N is 0.
%nrApraitii(E,[E|T],N)
nrAparitii(E,[H|T],N):- E=H,
                        nrAparitii(E,T,NT),
                        N is NT+1.
nrAparitii(E,[H|T],N):- E\=H,
                        nrAparitii(E,T,N).

stergeAux([],_,[]).
stergeAux([H|T],C,R):- nrAparitii(H,C,N),
                       N = 1,
                       stergeAux(T,C,R).
stergeAux([H|T],C,[H|R1]):- nrAparitii(H,C,N),
                            N\=1,
                            stergeAux(T,C,R1).

stergeAp(L,R):- stergeAux(L,L,R).

