'''
    Lahiru FYP
'''

import sys
import argparse
import numpy as np
import matplotlib.pyplot as pl
import math

def processFile(fileName):
    file=open(fileName,"r")
    file=file.readlines()
    file=file[3:]
    ff=[]
    for f in file:
        ff.append(float(f.strip().split()[1]))

    return np.array(ff)


def interpolate(x,y,xx):
    a=0
    for j in range(len(x) - 1):
        a = j
        if x[j] <= xx and x[j + 1] > xx:
            break
    # print("DEBUG a=",a)
    return y[a] + ((xx-x[a])*(y[a+1]-y[a]))/(x[a+1]-x[a])



if __name__ == '__main__':
    ar=argparse.ArgumentParser()
    ar.add_argument("file1",type=str)
    ar.add_argument("timeScale1",type=float)
    ar.add_argument("file2",type=str)
    ar.add_argument("timeScale2",type=float)
    ar.add_argument("--offset1", "-o1",type=int,default=0)
    ar.add_argument("--offset2", "-o2", type=int, default=0)
    ar=ar.parse_args()

    y1=processFile(ar.file1)
    y2=processFile(ar.file2)
    y1=y1[ar.offset1:]
    y2 = y2[ar.offset2:]

    x1=np.arange(len(y1))*ar.timeScale1
    x2 = np.arange(len(y2)) * ar.timeScale2

    sec1idx=0
    for x in range(len(x1)):
        if x1[x]>=1.0:
            sec1idx=x
            break
    x1=x1[:sec1idx]
    y1=y1[:sec1idx]
    # print(sec1idx)

    for x in range(len(x2)):
        if x2[x] >= 1.0:
            sec1idx = x
            break
    x2=x2[:sec1idx]
    y2=y2[:sec1idx]
    # print(sec1idx)

    y11=[]
    y22=[]
    x11=[]
    absError=[]

    sum_se=0.0
    count_se=0
    for i in range(1,1000):
        ii=i/1000.0
        x11.append(ii)
        y11.append(interpolate(x1,y1,ii))
        y22.append(interpolate(x2,y2,ii))
        absError.append(abs(y11[-1]-y22[-1]))
        sum_se+=math.pow(y11[-1]-y22[-1],2)

        count_se+=1.0

        # print(ii,sum_se)


    rmse=math.sqrt(sum_se/count_se)
    print("RMSE",rmse)
    # print(x1)
    # print(y1)
    # print(x2)
    # print(y2)
    pl.subplot(3, 1, 1)
    pl.plot(x1,y1,x2,y2,x1,[0]*len(x1),"k")
    pl.title("Input values")
    pl.legend(["y1","y2","xAxis"])

    pl.subplot(3, 1, 2)
    pl.plot(x11, y11,"b", x11, y22,"r",x11,absError,"g",x11,[0]*len(x11),"k")
    pl.legend(["y1-interpolated","y2-interpolated","absolute error","xAxis"])
    pl.title("Interpolated values")

    pl.subplot(3,1,3)

    pl.text(0,0,"We are analyzing {} sampled at {} as y1\n".format(ar.file1,ar.timeScale1) \
            + "and {} sampled at {} as y2\n".format(ar.file2,ar.timeScale2) \
            + "y1 is shifted by {} steps = {} sec\n".format(ar.offset1,ar.offset1*ar.timeScale1) \
            + "y2 is shifted by {} steps = {} sec\n".format(ar.offset2, ar.offset2 * ar.timeScale2) \
            + "RMSE = {} (for y1 and y2)".format(rmse))
    pl.show()


