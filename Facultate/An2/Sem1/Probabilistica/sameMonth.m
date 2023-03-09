function out = sameMonth (ppl)
  cf = 0;
  ct = 10000;
  for(i=1:ct)
    dates = randi(365,1,ppl);
    if(length(unique(dates))<length(dates))
      cf++;
    endif
  endfor
  out = cf/ct;
  
endfunction
