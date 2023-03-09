;Sa se elimine toate aparitiile unui atom din lista
;Ex: `(2 (A (1 3 (1)) 4 1) 5 D 1) 1 -> `(2 (A (3 ()) 4) 5 D)
;Model matematic
;elim(l1...ln, e) = vid, n = 0
;                   l1 + elim(l2...ln, e), l1 = atom, l1!=e, n>0                          
;                   elim(l2...ln, e), l1=e, n>0
;                   elim(l1, e) + elim(l2...ln, e), l1 != atom, n>0

; = numere
; eq atomi
; equal tot
; numberp -> verifica daca e numar
; listp
; oddp
; evenp
; atom -> verifica daca e atom

(defun elim (l e)
  (cond 
        ((null l) nil)
        ((equal (car l) e) (elim (cdr l) e))
        ((atom (car l)) (cons (car l) (elim (cdr l) e)))
        (t (cons (elim (car l) e) (elim (cdr l) e)))
  )
)



