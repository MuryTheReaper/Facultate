function [X,Y] = distributieNormalaStandard (N)
  
  u = rand(2,N);
  R = sqrt(-2*log(u(1,:)));
  V = 2 * pi * u(2,:);
  X = R .* cos(V);
  Y = R .* sin(V);

endfunction
