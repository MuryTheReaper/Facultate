function output = darts (N=1000)
    
    clf;
    t = linspace(0,2*pi,360);
    polar(t,4*ones(1,360), 'w');
    hold on;
    [X, Y] = distributieNormalaStandard(N);
    plot(X,Y, 'r*');
    polar(t,0.5*ones(1,360), 'b');
    m1 = mean(sqrt(X.^2 + Y.^2)<0.5);
    fprintf("m1: %d\n", m1);
    
    rel = 1-exp(-1/8);
    Z = normrnd(0,1,2,N);
    plot(Z(1,:),Z(2,:),'c*');
    
    m2 = mean(sqrt(Z(1,:).^2 + Z(2,:).^2)<0.5);
   
    polar(t, 0.5*ones(1,360), 'b'); 
    fprintf("m2: %d\n", m2);
    
    
endfunction
