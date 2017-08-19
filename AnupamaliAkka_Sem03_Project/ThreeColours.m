                %redLED greenLED blueLED 
threeColours=[[11.0250 16.5 12.2250];%blue
            [9.7 16.5750 17.875];%green
            [4.6250 17.05 17.15];%red
            ];

RGBmeans=mean(threeColours);



for x=1:3
    diffMatrix(:,x)=threeColours(:,x)-RGBmeans(x);
end

corelationM=(diffMatrix' * diffMatrix);

[V,D]=eig(corelationM);

eigenVec=V(:,3);

unitV=eigenVec/abs(eigenVec);

for x=1:3

    projectedM(x)=(threeColours(x,:) * eigenVec);
end

hold on;
plot(threeColours(:,1),'r*-');
plot(threeColours(:,2),'gd-');
plot(threeColours(:,3),'b+-');
plot(projectedM,'y*-');
hold off;
figure;


hold on;
plot(sort(threeColours(:,1)),'r*-');
plot(sort(threeColours(:,2)),'gd-');
plot(sort(threeColours(:,3)),'b+-');
plot((sort(projectedM)-2)*1.5,'y*-');