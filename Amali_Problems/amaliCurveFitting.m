%acutal values
x=[8.75,8.67,7.54,6.90,6.41,5.51,4.69];
y=[3.6     3.8    3.8    4.0    4.2    4.2    4.2    ]

cur=polyfit(x,y,2); %This is to say it is a quadratic polynomial
xxx=linspace(x(1),x(length(x))); 
yyy=polyval(cur,xxx);

figure;
hold on;
plot(x,y,'*b ');
plot( xxx ,yyy,' b-');
title('Amalis graph');
xlabel('x unit');
ylabel('yunit');