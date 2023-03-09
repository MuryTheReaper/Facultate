function out = squarePoints (numberOfPoints)
  
  hold on;
  rectangle('Position', [0 0 1 1])
  cf=0;
  
  for(i=1:numberOfPoints)
    x = rand();
    y = rand();
    dc = pdist([x y; 0.5 0.5]);
    d1 = pdist([x y; 0 0]);
    d2 = pdist([x y; 1 1]);
    d3 = pdist([x y; 1 0]);
    d4 = pdist([x y; 0 1]);
    %mini = min(dc,d1);
    %mini = min(mini,d2);
    %mini = min(mini,d3); 
    %mini = min(mini,d4);
    ok=0;
    if(pdist([x y; 0 0.5])<1/2)
      ok++;
    endif
    
    if(pdist([x y; 1 0.5])<1/2)
      ok++;
    endif
    
    if(pdist([x y; 0.5 0])<1/2)
      ok++;
    endif
    
    if(pdist([x y; 0.5 1])<1/2)
      ok++;
    endif
    
    if(ok==2)
    %if(mini == dc)
    %if(pdist([x y;0.5 0.5])<0.5)
      cf++;
      plot(x,y,'r')
    endif
  endfor
  
  out = cf/numberOfPoints;

endfunction
