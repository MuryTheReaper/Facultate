par(2).
par(4).
impar(1).
impar(3).
parImpar(X,Y):- impar(X),par(Y).
parImpar(X,Y):- par(X), impar(Y).
