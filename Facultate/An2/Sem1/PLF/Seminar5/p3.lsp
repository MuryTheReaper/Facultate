;Sa se determine lista pozitiilor elementului numeric minim dintr-o lista liniara
;Ex: `(A B 3 5 6 C 3) -> (3, 7)
;
;Model matematic
;listPozMin(l1...ln, c1...cn, min, index) 
;            = c, n = 0
;              listPozMin(l2...ln, index + c1...cn, min, index + 1) , l1 = min, n>0
;              listPozMin(l2...ln, c1...cn, min, index + 1), 
;                                           n>0, l1 numar, l1 > min sau l1 atom
;              listPozMin(l2...ln, (index), l1, index + 1), n>0, l1 numar, l1 < min


(defun listPozMin (l c mini index)
    (cond
        ((null l) c)
        ((eq (car l) mini) (listPozMin (cdr l) (cons index c) mini (+ index 1)))
        ((AND (numberp (car l)) (< (car l) mini)) 
            (listPozMin (cdr l) (list index) (car l) (+ index 1)))
        (t (listPozMin (cdr l) c mini (+ index 1)))
    )
)
           
;minList(l1....ln) = listPozMin(l1...ln, (), -inf, 1)

(defun minList (l)
    (listPozMin l nil 9999 1))
