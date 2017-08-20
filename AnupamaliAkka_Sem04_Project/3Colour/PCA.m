threeColours=[[1019,667,976];
            [1020,655,960];
            [1022,711,994];
            ]
RGBmeans=mean(threeColours)
RGBsdtDev=sqrt(var(threeColours))

normalizedThreeColours=zeros(3,3);

for i=1:3
    for j=1:3
        normalizedThreeColours(i,j)= (threeColours(i,j)-RGBmeans(j)) /RGBsdtDev(j);
    end
end
normalizedThreeColours

corelationM=(normalizedThreeColours' * normalizedThreeColours);

[V,D]=eig(corelationM);

eigenVec=V(:,3)

unitV=eigenVec/abs(eigenVec);

for x=1:3
    projectedM(x)=(normalizedThreeColours(x,:) * eigenVec);
end

projectedM