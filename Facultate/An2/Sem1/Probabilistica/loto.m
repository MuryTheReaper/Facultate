function retval = loto (m = 1000)
  
  p = sum(hygepdf(3:6, 49, 6, 6));
  x = geornd(p, 1, m);  #i
  
  v = sum(x>=10) / m #ii sau mean(x>=10)
  
  w = 1 - sum(geopdf(0:9, p))
  
endfunction
