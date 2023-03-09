;Functii MAP
(defun tripleaza (x)
  (cond
       ((numberp x) (* x 3))
       ((atom x) x)
       (t (mapcar `tripleaza x))
  )
)

;mapcar `function `list
;apeleaza function pe toate elementele listei


;Sa se calculeze produsul tuturor atomilor numerici dintr-o lista.
;
; produs(x) = x, x=numar
;             1, x=atom nenumeric
;             PI i=1,n (produs(x)), x=lista, x1...xn

(defun produs (x)
    (cond
        ((numberp x) x)
        ((atom x) 1)
        (t (APPLY '* (mapcar #'produs x)))
    )
)


;Sa se determine numarul total de noduri de pe nivelele pare dintr-un arbore
;n-ar reprezentat sub forma (radacina (subarbore 1) (subarbore2) ...)
;Ex: (A (B (D (E) (F))) (C))

;nr_nod(x, n) = n, x atom
;               SUM i=1,m nr_nod(x,1-n), x lista, x = x1...xm

(defun nr_nod (x n)
    (cond
        ((null x) 0)
        ((atom x) n)
        (t (APPLY '+ (mapcar #'(lambda (a) (nr_nod a (- 1 n))) x)))
    )
)

;Numarati sublistele unuei liste (inclusiv ea insasi) pentru care 
;primul atom numeric este 5
;Ex: (A B 5 (C D (5 A 1)) 3 5)

(defun linie (l)
  (cond
        ((numberp l) (list l))
        ((atom l) nil)
        (t (mapcan #'linie l))
  )
)

(defun verifica (x)
    (cond
        ((eq (car (linie x)) 5) t)
        (t nil)
    )
)


;numara(x) = 0, x atom
;            1 + SUM i=1,n numar(xi), x=x1...xn, verifica(x)=true
;            SUM i=1,n numar(x1), x=x1...xn, verifica(x)=false
(defun numara (x)
    (cond
        ((atom x) 0)
        ((verifica x) (+ 1 (APPLY '+ (mapcar #'numara x))))
        (t (APPLY '+ (mapcar #'numara x)))
    )
)











