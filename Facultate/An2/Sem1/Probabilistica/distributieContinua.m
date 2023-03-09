function output = distributieContinua (N, lambda)
  #randexp
  
  output = -log(1-rand(1,N))/lambda;
  
  #x1 = distributieContinua(1000,1/12)
  #x2 = exprnd(12,1,1000) 
  
endfunction
