X=[32.8,34.4,34.4,33.5,32.9,29.3];
Y=[17.83,16.38,15.68,14.66,14.16,12.83];

mMin=min(Y./X);
mMax=max(Y./X);

mBest=0;
leastError=inf;

for m = linspace(mMin,mMax,200)
    error=sum((Y-X*m).^2);
    if error < leastError
        leastError=error;
        mBest=m;
    end
end

mBest
leastError

plot(linspace(0,max(X)),linspace(0,max(X))*mBest,'b- ');
hold on;
plot(X,Y,'r *');
title(['y = ',num2str(mBest),'x'])

figure
plot(linspace(min(X),max(X)),linspace(min(X),max(X))*mBest,'b- ');
hold on;
plot(X,Y,'r *');
title(['y = ',num2str(mBest),'x'])