sixColours=[[7.7998 5.9417 1.4767];
            [7.5617 5.2167 1.3433];
            [7.2800 4.1267 1.3400];
            [7.0083 2.9983 1.3300];
            [6.6483 2.3 1.3150];
            [7.3333 2.8150 2.0067];
            [7.7433 3.9783 3.6833];
            [5.8750 3.0267 2.4633];
            [5.3950 4.2467 4.1267]
            [5.8850 4.9300 3.6283]
            [6.4700 5.8067 3.3550];
            [7.2850 6.4267 1.9367];
            ];

RGBmeans=mean(sixColours);



for x=1:3
    diffMatrix(:,x)=sixColours(:,x)-RGBmeans(x);
end

corelationM=(diffMatrix' * diffMatrix);

[V,D]=eig(corelationM);

eigenVec=V(:,3);

unitV=eigenVec/abs(eigenVec);

for x=1:12

    projectedM(x)=(sixColours(x,:) * eigenVec);
end

hold on;
plot(sixColours(:,1),'b*-');
plot(sixColours(:,2),'gd-');
plot(sixColours(:,3),'r+-');
plot(projectedM,'y*-');
hold off;
figure; 


hold on;
plot(sort(sixColours(:,1)),'b*-');
plot(sort(sixColours(:,2)),'gd-');
plot(sort(sixColours(:,3)),'r+-');
plot((sort(projectedM)-2)*1.5,'y*-');