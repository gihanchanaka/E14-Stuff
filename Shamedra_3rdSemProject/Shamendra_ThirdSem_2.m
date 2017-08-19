clear all
A=[ [405	0.9673501739	0.9767995958	1.009769926];
[465	1.005753198	1.031240132	1.025351793];
[475	1.014216503	1.04253963	1.027918164];
[510	1.008402444	1.013118194	1.004688259];
[535	0.9926866383	0.979942255	0.9871739141];
[665	0.9696989447	0.9704847721	1.000808744]];

B=transpose(A);

p(1:4)=polyfit(B(1,1:6),B(2,1:6),3);
x(1:100)=linspace(400,700);
y(1:100)=polyval(p(:),x(1:100));

subplot(2,2,1)
plot(x,y,'-r*')
title('Cubic polynomial approximation')
subplot(2,2,2)
plot(B(1,:),B(2,:),'-r*')
title('Original data')


pp(1:4)=polyfit(B(1,1:6),B(3,1:6),3);
yy(1:100)=polyval(pp(:),x(1:100));

subplot(2,2,3)
plot(x,yy,'-b*')
title('Cubic polynomial approximation')
subplot(2,2,4)
plot(B(1,:),B(3,:),'-b*')
title('Original data')


