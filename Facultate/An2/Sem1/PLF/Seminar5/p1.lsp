;1. Se dau 2 liste liniare, numerice, distincte, sortate crescator.
;Se cere sa se interclaseze listele, fara pastrare dubluri.
;Ex: [1, 3, 5, 9], [2, 3, 4, 6, 8] -> [1, 2, 3, 4, 5, 6, 8, 9]

;Model matematic
;interclasare(l1..ln, k1...km) = k, n = 0 si m>0
;                                l, m = 0
;                                l1 + interclasare(l2...ln, k1...kn), l1 < k1, n>0, m>0
;                                k1 + interclasare(l1...ln, k2...kn), k1 < l1, m>0, n>0
;                                l1 + intercasare(l2...ln, k2...kn), l1 = k1, n>0, m>0

;cons -> constructor de lista
;car -> primul element
;cdr -> sublista fara primul elem
;t -> true

(defun interclasare (l k)
  (cond 
        ((AND (null l) (not (null k))) k)
        ((null k) l)
        ((< (car l) (car k)) (cons (car l) (interclasare (cdr l) k)))
        ((> (car l) (car k)) (cons (car k) (interclasare l (cdr k))))
        (t (cons (car l) (interclasare (cdr l) (cdr k))))
  )
)


; arg               CONS           LIST           APPEND
; `A `B             (cons `A `B)   (A B)          ERROR
;                   (A.B)
; `A `(B C)         (A B C)        (A (B C)       ERROR
; `(A B) `C         ((A B).C)      ((A B) C       (A B.C)
; `(A B) `(C D)     ((A B) C D)    ((A B) (C D))  (A B C D)
; `A `B `C          ERROR          (A B C)        ERROR
; `(A) `(B) `C      ERROR          (A B C)        (A B.C)
