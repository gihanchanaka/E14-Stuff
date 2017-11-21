function [ ] = denseSegment( arr )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
        mi=min(arr);
        ma=max(arr);
        
        denseSegStart=mi;
        denseSegCount=0;
        
        for x=mi:ma
            thisSegCount=sum((arr>=x).*(arr<(x+20)));
            if thisSegCount>denseSegCount
                   denseSegCount=thisSegCount;
                   denseSegStart=x;
            end
        end
        
        denseSeg=nonzeros(arr.*((arr>=denseSegStart).*(arr<denseSegStart+20)));
        
        disp(['The segment ',num2str(min(denseSeg)),'-',num2str(min(denseSeg)+19),' has ',num2str(denseSegCount),' elements :']);
        disp(denseSeg);
        
        


end

