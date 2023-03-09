function output = imprimanta (N=1000)
    
   xSim = distributieContinua(N,1/12);
   xTeo = exprnd(12,1,N);
   
   fprintf("Sim mean : %d\n",mean(xSim));
   fprintf("Teo mean : %d\n",mean(xTeo));
   
   
   fprintf("Sim std : %d\n",std(xSim));
   fprintf("Teo std : %d\n",std(xTeo));
   
   
     
     
endfunction