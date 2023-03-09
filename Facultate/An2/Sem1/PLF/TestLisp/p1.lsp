;



;aparitii(x, e) = 1, x = numar, x = e
;                 0, x = atom, x != e
;                 SUM i=1,n (aparitii (xi,e)) , x = x1...xn, x = lista

;aparitii(element, intreg)
(defun aparitii (x e)
    (cond
        ((and (numberp x) (= x e)) 1)
        ((atom x) 0)
        (t (apply #'+ (mapcar #'(lambda (a) (aparitii a e)) x)))
    )
)

;schimba(x, c1...cn) = x + 1, x = numar, aparitii(c, x)>1
;                    = x, x = atom nenumeric sau (x = numar si aparitii(c, x)<=1) 
;                    = schimba(x1, c) + schimba(x2, c) + ... + schimba(xn, c), x = x1...xn
;                                                                              x = lista

;schimba(element, lista)

(defun schimba (x l)
    (cond
        ((and (numberp x) (< 1 (aparitii l x))) (+ 1 x))
        ((atom x) x)
        (t (apply #'list (mapcar #'(lambda (a) (schimba a l)) x)))
    )
)

;f(x1...xn) = schimba(x1...xn, x1...xn)

;f(lista)

(defun f (x)
    (schimba x x)
)
