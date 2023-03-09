;Se da un arbore de tipul (1). 
;Sa se precizeze nivelul pe care apare un nod x in arbore. 
;Nivelul radacii se considera a fi 0.
;Ex: nivel(E, (A 2 B 2 C 1 I 0 F 1 G 0 D 2 E 0 H 0)) -> 2


;splitS(l1...ln, nv, nm) = vid, n = 0
;                        = vid, n > 0, nv = 1 + nm
;                        = l1 + l2 + splitS(l3...ln, nv+1, nm+l2), n > 0, nv != 1 + nm
;arb -> arborele
;nv -> numar varfuri curente
;nm -> numar muchii curente
(defun splitS (arb nv nm)
    (cond
        ((null arb) nil)
        ((= nv (+ 1 nm)) nil)
        (t (append (list (car arb) (cadr arb)) 
                 (splitS (cddr arb) (+ 1 nv) (+ (cadr arb) nm))))
    )
)

;splitD(l1...ln, nv, nm) = vid, n = 0
;                        = l, n > 0, nv = 1 + nm
;                        = splitD(l3...ln, nv+1, nm+l2), n > 0, nv != 1 + nm
;arb -> arborele
;nv -> numar varfuri curente
;nm -> numar muchii curente
(defun splitD (arb nv nm)
    (cond
        ((null arb) nil)
        ((= nv (+ 1 nm)) arb)
        (t (splitD (cddr arb) (+ 1 nv) (+ (cadr arb) nm)))
    )
)

;splitSD(l1...ln, st, nv, nm) = [st, []], n = 0
;                             = [st, arb], nv = 1 + nm
;                             = splitSD(l3...ln, st+l1+l2, nv+1, nm+l2, n>0, nv != 1 +nm
;arb -> arborele
;st -> subarborle stang
;nv -> numar de varfuri curente
;nm -> numar de muchii curente
(defun splitSD (arb st nv nm)
    (cond
        ((null arb) (list st nil))
        ((= nv (+ 1 nm)) (list st arb))
        (t (splitSD (cddr arb) (append st (list (car arb) (cadr arb))) 
                    (+ 1 nv) (+ (cadr arb) nm)))
    )
)

;subarbori(l1...ln) = splitSD(l3...ln, [], 0, 0)
;arb -> arborele
(defun subarbori (arb)
    (splitSD (cddr arb) () 0 0)
)

;subarbori2(l1...ln) = [splitS(l3...ln, 0, 0)] + [splitD(l3...ln, 0, 0)]
;arb -> arborele
(defun subarbori2 (arb)
    (list (splitS (cddr arb) 0 0) (splitD (cddr arb) 0 0))
)

;isMember(e, l1...ln) = false, n = 0
;                     = true, n > 0, l1 = e
;                     = isMember(e, l3...ln), n > 0, l1 != e
;e -> nodul cautat
;l -> arborele in care se cauta nodul e
(defun isMember (e l)
    (cond
        ((null l) nil)
        ((eq (car l) e) t)
        (t (isMember e (cddr l)))
    )
)

;nivelAux(e, l1...ln, niv) = vid, n = 0
;                          = niv, n > 0, l1 = e
;                          = nivelAux(e, z1, niv+1), n>0, l1!=e, 
;                                           z = subarbori(l1...ln), isMember(e, z1) = true
;                          = nivelAux(e, z2, niv+2), n>0, l1!=e.
;                                           z = subarbori(l1...ln), isMember(e, z1)=false
;e -> nodul cautat
;arb -> arborele
;niv -> nivelul la care se afla nodul e, nil daca nu exista
(defun nivelAux (e arb niv)
    (cond
        ((null arb) nil)
        ((eq e (car arb)) niv)
        ((isMember e (car (subarbori arb))) (nivelAux e (car (subarbori arb)) (+ 1 niv)))
        (t (nivelAux e (cadr (subarbori arb)) (+ 1 niv)))
    )
)

;nivel(e, l1...ln) = nivelAux(e, l1...ln, 0)
;e -> nodul cautat
;arb -> arborele
(defun nivel (e arb)
    (nivelAux e arb 0)
)

