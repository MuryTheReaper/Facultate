;Sa se construiascao functie care intoarce suma atomilor numerici dintr-o lista
;de la orice nivel.

;sum(x) = x, x = numar
;       = 0, x = atom nenumeric
;       = SUM i=1,n (sum(x)), x = lista, x1...xn

(defun sum (x)
    (cond
        ((numberp x) x)
        ((atom x) 0)
        (t (APPLY '+ (mapcar #'sum x)))
    )
)
