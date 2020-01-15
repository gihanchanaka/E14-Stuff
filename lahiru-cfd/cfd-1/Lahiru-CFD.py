import pandas as pd
import sys
import numpy as np
from shapely.geometry import Polygon
import matplotlib.pyplot as plt



if __name__ == '__main__':

    print("python Lahiru-CFD.py xlFile.xlsx")

    fileContent=pd.read_excel(sys.argv[1])




    trueX=fileContent['point']#.values
    trueY=fileContent['Cp Actual']
    predX=fileContent['X [ m ]']
    predY=fileContent['Cp [ Pa ]']

    trueX = trueX[np.logical_not(np.isnan(trueX))]
    trueY = trueY[np.logical_not(np.isnan(trueY))]
    predX = predX[np.logical_not(np.isnan(predX))]
    predY = predY[np.logical_not(np.isnan(predY))]

    trueXY=[]
    predXY=[]

    print(trueX.shape,trueY.shape,predX.shape,predY.shape)
    for i in range(len(trueX)):
        trueXY.append((trueX[i],trueY[i]))

    for i in range(len(predX)):
        predXY.append((predX[i],predY[i]))
    #
    # trueXY.append(trueXY[0])
    # predXY.append(predXY[0])

    # print("True",trueXY[0],trueXY[-1])

    truePoly=Polygon(trueXY)
    truePoly=truePoly.buffer(0)
    predPoly=Polygon(predXY)
    predPoly=predPoly.buffer(0)

    print(truePoly.is_valid)
    print(predPoly.is_valid)

    iou=truePoly.intersection(predPoly).area/truePoly.union(predPoly).area
    textLabel="IoU = {:.8f} for n(ref)={} and n(Pred)={}".format(iou,len(trueXY),len(predXY))

    x, y = truePoly.exterior.xy
    plt.plot(*truePoly.exterior.xy,'r');
    plt.plot(*predPoly.exterior.xy, 'b');
    plt.legend(["Ref","Pred"])
    plt.text(0.1,0.8,textLabel)

    print(textLabel)




    # print(trueXY)
    plt.savefig(sys.argv[1].replace("xlsx","png"))
    plt.show()





