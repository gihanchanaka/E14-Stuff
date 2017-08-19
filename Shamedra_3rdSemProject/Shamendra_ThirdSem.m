clear all
A=[ [405	0.9673501739	0.9767995958	1.009769926];
[465	1.005753198	1.031240132	1.025351793];
[475	1.014216503	1.04253963	1.027918164];
[510	1.008402444	1.013118194	1.004688259];
[535	0.9926866383	0.979942255	0.9871739141];
[665	0.9696989447	0.9704847721	1.000808744]];

B=transpose(A);

p(1,1:3)=polyfit(B(1,1:3),B(2,1:3),2);
p(2,1:3)=polyfit(B(1,4:6),B(2,4:6),2);
equations_1(1:6)=p;

x(1:100)=linspace(400,500);
x(101:200)=linspace(500,700);
y(1:100)=polyval(p(1,:),x(1:100));
y(101:200)=polyval(p(2,:),x(101:200));

subplot(3,2,1)
plot(x,y,'-r*')
title('Two quadratic functions approxiamtion')
subplot(3,2,2)
plot(B(1,:),B(2,:),'-r*')
title('Original data')


p(1,1:3)=polyfit(B(1,1:3),B(3,1:3),2);
p(2,1:3)=polyfit(B(1,4:6),B(3,4:6),2)
equations_2(1:6)=p;

x(1:100)=linspace(400,500);
x(101:200)=linspace(500,700);
y(1:100)=polyval(p(1,:),x(1:100));
y(101:200)=polyval(p(2,:),x(101:200));

subplot(3,2,3)
plot(x,y,'-go')
title('Two quadratic functions approxiamtion')
subplot(3,2,4)
plot(B(1,:),B(3,:),'-go')
title('Original data')


p(1,1:3)=polyfit(B(1,1:3),B(4,1:3),2);
p(2,1:3)=polyfit(B(1,4:6),B(4,4:6),2)
equations_3(1:6)=p;

x(1:100)=linspace(400,500);
x(101:200)=linspace(500,700);
y(1:100)=polyval(p(1,:),x(1:100));
y(101:200)=polyval(p(2,:),x(101:200));

subplot(3,2,5)
plot(x,y,'-b.')
title('Two quadratic functions approxiamtion')
subplot(3,2,6)
plot(B(1,:),B(3,:),'-b.')
title('Original data')