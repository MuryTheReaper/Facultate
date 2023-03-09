function retval = modelTest ()
  
  clf; hold on; grid on;
  #X ~ N(100,20)
  
  values = normrnd(100,20,1,1000);
  
  #A: 80<X<140
  disp("A: ")
  disp(sum(values > 80 & values < 140)/1000)
  
  #teoretic pt A
  disp("A teoretic: ")
  disp(normcdf(140,100,20)-normcdf(80,100,20))
  
  #hist
  hist(values,13)
  
  for j = values
    y = normpdf(j,100,20);
    y = y * 10000;
    plot(j,y,'r')
  endfor
 

endfunction
