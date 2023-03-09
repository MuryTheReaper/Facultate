function retval = testPS ()
  
  #albe, rosii, albastre, verzi
  
  a = 0;
  b = 0;
  c = 0;
  
  for k = 1:1000
    X = [10, 7, 6, 7];
    Y = [8, 9, 5, 8];
    
    albastre = 0;
    fullRosu = 0;
    alba = 0;
  
    for i = 1:8
      j = randi(sum(X));
      
      j
      
      if(j <= X(1))
        j = 1;
      endif
      if(j > X(1) && j <= X(1) + X(2))
        j = 2;
      endif
      if(j > X(1) + X(2) &&  j <= X(1) + X(2) + X(3))
        j = 3;
      endif
      if(j > X(1) + X(2) + Y(3) && j <= X(1) + X(2) + X(3) + X(4))
        j = 4;
      endif
      
      X(j) --;
      Y(j) ++;
    endfor
  
  for i = 1:3
    j = randi(sum(Y));
    
     if(j <= Y(1))
      j = 1;
    endif
    if(j > Y(1) && j <= Y(1) + Y(2))
      j = 2;
    endif
    if(j > Y(1) + Y(2) &&  j <= Y(1) + Y(2) + Y(3))
      j = 3;
    endif
    if(j > Y(1) + Y(2) + Y(3) && j <= Y(1) + Y(2) + Y(3) + Y(4))
      j = 4;
    endif
    
    if(j == 3)
      albastre ++;
    endif
    
    if(j == 1)
      alba ++;
    endif
    
    if(j == 2)
      fullRosu ++;
   endif
   
  endfor
  
  
  if(albastre > 0)
    a++;
  endif
  
  if(fullRosu == 3)
    b++;
  endif
  
  if(alba == 0)
    c++;
  endif
 
  
endfor

  disp("A: ")
  disp(a/1000)
  disp("B: ")
  disp(b/1000)
  disp("C: ")
  disp(c/1000)

endfunction
