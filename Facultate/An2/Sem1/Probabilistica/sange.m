function retval = sange (n = 1000)
  
  clf; grid on; hold on;
  
  dis = distributieDiscreta([0,1,2,3],[46/100, 40/100, 10/100, 4/100], n);
  disT = randsample([0,1,2,3], n, true, [46/100, 40/100, 10/100, 4/100]);
  
  bar(0:3,hist(dis,0:3),'hist','FaceColor','b');
  bar(0:3,hist(disT,0:3),'hist','FaceColor','y');
  set(findobj('type','patch'),'facealpha',0.5);


endfunction
