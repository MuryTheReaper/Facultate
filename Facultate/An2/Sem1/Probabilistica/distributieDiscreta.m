
#val = vector val posibile
#prob = vector probabilitati corespunzatoare
#N = numarul de valori de generat
function output = distributieDiscreta (val, prob, N)
    #metoda inversei
    
    #0  x1  p1  x2  p1+p2  x3 p1+p2+p3=1
    
    q = cumsum(prob);
    output = zeros(1,N);
    
    for(i = 1:N)
      u = rand;
      j = 1;
      while(u > q(j))
        j++;
      endwhile
      
      output(i) = val(j);
      
    endfor
    
endfunction
