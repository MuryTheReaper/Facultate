;9 a) Sa se scrie o functie care intoarce diferenta a doua multimi.
;Ex: [1, 2, 3], [2, 3, 4] -> [1]

;Model matematic
;isMember(e, l1...ln) = false, n = 0
;                       true, n > 0, e = l1
;                       member(e, l2...ln), n > 0, e != l1 

;e -> elementul care trebuie cautat in l
;l -> lista in care se cauta elementul e
(defun isMember (e l)
    (cond
        ((null l) nil)
        ((eq e (car l)) t)
        (t (isMember e (cdr l)))
    )
)

;Model matematic
;diff(l1...ln, k1...km) = [], n = 0
;                         diff(l2...ln, k1...km), n > 0, isMember(l1, k1...kn) = true
;                         l1 + diff(l2...ln, k1...km), n>0, isMember(l1, k1...kn) = false 

;l -> prima multime
;k -> a doua multime
(defun diff (l k)
    (cond
        ((null l) nil)
        ((isMember (car l) k) (diff (cdr l) k))
        (t (cons (car l) (diff (cdr l) k)))
    )
)

;b) Definiti o functie care inverseaza o lista 
;       impreuna cu toate sublistele sale de pe orice nivel.
;Ex: ((1 2 3) 4 (5 6)) -> ((6 5) 4 (3 2 1)) 


;Model matematic
;inverse(l1...ln) = [inverse(l2...ln)], n = 1, l1 = lista
;                 = [l1], n = 1, l1 != lista
;                 = inverse(l2...ln) + [inverse(l1)], n>1, l1 = lista
;                 = inverse(l2...ln) + [l1], n>1, l1 != lista

;l -> lista de inversat
(defun inverse (l)
     (cond
          ((AND (null (cdr l)) (listp (car l))) (list (inverse (car l))))
          ((null (cdr l)) (list (car l)))
          ((listp (car l)) (append (inverse (cdr l)) (list (inverse (car l)))))
          (t (append (inverse (cdr l)) (list (car l))))
      )
)

;c) Dandu-se o lista, sa se construiasca lista primelor elemente 
;    ale tuturor elementelor lista ce au un numar impar de elemente
;       la nivel superficial. Exemplu: (1 2 (3 (4 5) (6 7)) 8 (9 10 11)) => (1 3 9)


;Model matematic
;lenght(l1...ln) = 0, n = 0
;                  1 + lenght(l2...ln), n > 0

;l -> lista pentru care se calculeaza lungimea
(defun lenght (l)
    (cond
        ((null l) 0)
        (t (+ 1 (lenght (cdr l))))
    )
)

;Model matematic
;nextList(l1...ln) = vid, n = 0
;                    nextList(l2...ln), n>0, l1 = atom
;                    l, n>0, l1 = list

;l -> lista din care se 'sterg' primele elemente care nu sunt lista
(defun nextList (l)
    (cond
        ((null l) nil)
        ((atom (car l)) (nextList (cdr l)))
        (t l)
    )
)

;Model matematic
;oddFirstElements(l1...ln) = vid, n = 0
;                            oddFirstElements(l1) + oddFirstElements(nextList(l2...ln)),
;                                       n>0, l1 = lista
;                            l1 + oddFirstElements(nextList(l1...ln)),
;                                       n>0, l1 != lista, lenght(l1...ln) % 2 = 1
;                            oddFirstElements(nextList(l1...ln)), altfel
(defun oddFirstElements (l)
    (cond
        ((null l) nil)
        ((listp (car l)) 
            (append (oddFirstElements (car l)) (oddFirstElements(nextList (cdr l)))))
        ((oddp (length l)) (cons (car l) (oddFirstElements (nextList l))))
        (t (oddFirstElements (nextList l)))
    )
)
;Model matematic
;oddFirstElements2(l1...ln) = vid, n = 0
;                             first(l1) + oddFirstElements2(nextList(l2...ln)),
;                                       n>0, l1 = lista
;                             l1 + oddFirstElements2(nextList(l1...ln)),
;                                       lenght(l1...ln) % 2 = 1
;                             oddFirstElements2(nextList(l1...ln)), altfel

;l -> lista din care se extrag elementele cunform cerintei
(defun oddFirstElements2 (l)
    (cond
         ((null l) nil)
         ((AND (listp (car l)) (oddp (lenght (car l)))) 
              (cons (car (car l)) (oddFirstElements2(nextList (cdr l)))))
          ((oddp (length l)) (cons (car l) (oddFirstElements2 (nextList l))))
          (t (oddFirstElements2 (nextList l)))
    )
)

;d) Sa se construiasca o functie care intoarce suma 
;       atomilor numerici dintr-o lista, de la nivelul superficial.

;Model matematic
;sum(l1...ln) = 0, n = 0
;               l1 + sum(l2...ln), n>0, l1 = numar
;               sum(l2...ln), n>0, l1 != numar

;l -> lista din care se calculeaza suma atomulor numerici
(defun sum (l)
    (cond
        ((null l) 0)
        ((numberp (car l)) (+ (car l) (sum (cdr l))))
        (t (sum (cdr l)))
    )
)



