(defun G (l)
    (MAPCON #'list l)
)

(defun isMember (l e)
    (cond
        ((null l) nil)
        ((eq (car l) e) t)
        ((listp (car l)) (or (isMember (car l) e) (isMember (cdr l) e)))
        (t (isMember (cdr l) e))
    )
)
