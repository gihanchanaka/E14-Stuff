sixColours=[[7.89,4.62,7.75];
            [7.86,5.24,7.58];
            [7.88,5.66,7.60];
            [7.89,6.61,7.64];
            [7.81,5.14,7.64];
            [7.77,4.48,7.65];
            ];
sixColours=(1023/10)*sixColours;
RGBmeans=mean(sixColours);

for x=1:3
    diffMatrix(:,x)=sixColours(:,x)-RGBmeans(x);
end

corelationM=(diffMatrix' * diffMatrix);

[V,D]=eig(corelationM);

eigenVec=V(:,3);

unitV=eigenVec/abs(eigenVec);

for x=1:6

    projectedM(x)=(sixColours(x,:) * eigenVec);
end