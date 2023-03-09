function out=aranjamente(v,n,k)
  a=nchoosek(v(1:n),k);
  for(i=1:rows(a))
    disp(perms(a(i,:)))
  endfor
end  
  