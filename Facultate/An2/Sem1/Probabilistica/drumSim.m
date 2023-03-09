function retval = drumSim (m=1000, k = 10, p = 1/2)
  
  clf;
  v=[];
  for(i=1:m)
    v = [v, drum(k,p)(end)];
  endfor
  
  h = hist(v, -k:k);
  bar(-k:k, h, 'hist', 'FaceColor', 'k');  
  
  freqMax = max(h);
  depPos = -k:k;
  legend(num2str(depPos(h==freqMax)));
  
endfunction
