stergeCresc([],[]).
stergeCresc([E],[E]).
stergeCresc([L1,L2],[]):- L1 < L2.
stergeCresc([L1,L2],[L1,L2]):- L1 >= L2.
stergeCresc([L1,L2,L3|T],R):- L1<L2, L2<L3,
                              stergeCresc([L2,L3|T],R).
stergeCresc([L1,L2,L3|T],R):- L1<L2,L2>=L3,
                              stergeCresc([L3|T],R).
stergeCresc([L1,L2|T],R):- L1>=L2, stergeCresc([L2|T],R1),
                           R=[L1|R1].
