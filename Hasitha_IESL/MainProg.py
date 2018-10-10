'''
Update 10-10-2018 19:35
'''

import cv2
import numpy as np
#import RPi.GPIO as GPIO

TURNING_PARAM=-0 #Tune this parameter to decide when to turn
FORWARD_PARAM=5 #Tune this parameter for the tolerance in mis-alignment

FULL_BLACK_PARAM=0.05 #When to go back
COMPLICATED_PARAM=0.8 #When to start looking for arrows


TOP_OFFSET=10 #Window size param
FRAME_HEIGHT=400 #Window size param
LEFT_OFFSET=25 #Window size param
FRAME_WIDTH=500 #Window size param

cap=cv2.VideoCapture(0)
'''cap.set(3, 640)
cap.set(4, 480)'''

if __name__== "__main__":
    STATE="BEGIN"
    PREV_STEP=""
    while True:
        if STATE=="BEGIN":
            H=FRAME_HEIGHT
            W=FRAME_WIDTH
            ret,frame=cap.read()
            while(ret==False):
                ret,frame=cap.read()
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            blur=cv2.GaussianBlur(gray,(5,5),0)
            ret,th1 = cv2.threshold(blur,35,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
            fr=th1[TOP_OFFSET:H+TOP_OFFSET,LEFT_OFFSET:W+LEFT_OFFSET]
            cv2.imshow('otsu',th1)
            cv2.waitKey(10)
            COG=np.zeros(shape=(H),dtype=np.int)
            M=np.zeros(shape=(H),dtype=np.int)
            STATE="LINE-FOLLOW"


        if STATE=="LINE-FOLLOW":
            ret,frame=cap.read()
            while(ret==False):
                ret,frame=cap.read()
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            blur=cv2.GaussianBlur(gray,(5,5),0)
            ret,th1 = cv2.threshold(blur,35,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
            fr=th1[TOP_OFFSET:H+TOP_OFFSET,LEFT_OFFSET:W+LEFT_OFFSET]
            #print(th1.shape,TOP_OFFSET,H+TOP_OFFSET,LEFT_OFFSET,W+LEFT_OFFSET,fr.shape)
            cogFrame=np.zeros(fr.shape)


            for y in range(H):
                M[y]=0
                COG[y]=0

                #print(COG[y],M[y])


                M[y]=np.sum(fr[y,:])
                COG[y]=np.dot(fr[y,:],np.arange(0,W))



                if M[y]>0:
                        COG[y]=COG[y]/M[y]
                else:
                    COG[y]=W/2

                cogFrame[y,COG[y]]=1



            COG2=COG-W/2
            np.flip(COG2,0)
            dir=np.dot(COG2,np.exp(TURNING_PARAM*np.arange(H,0,-1)))/np.sum(np.exp(TURNING_PARAM*np.arange(H,0,-1)))

            cogFrame[:,int(dir+W/2)]=1

            whiteSum=np.sum(gray[TOP_OFFSET:H+TOP_OFFSET,LEFT_OFFSET:W+LEFT_OFFSET]>125.0)

            print(whiteSum,H*W)
            if whiteSum<FULL_BLACK_PARAM*H*W:
                if PREV_STEP=="FORWARD":
                    print("BACKWARD")
                elif PREV_STEP=="RIGHT-Forward":
                    print("LEFT-Backward")
                elif PREV_STEP=="LEFT-Forward":
                    print("RIGHT-Backward")
                else:
                    print("FORWARD")
            elif whiteSum>COMPLICATED_PARAM*H*W:
                print("Start looking for arrows")
            else:
                if(np.abs(dir)<FORWARD_PARAM):
                    PREV_STEP="FORWARD"
                    print(dir,"FORWARD")
                else:
                    if(dir>0):
                        PREV_STEP="RIGHT-Forward"
                        print(dir,"RIGHT-Forward")
                    else:
                        PREV_STEP="LEFT-Forward"
                        print(dir,"LEFT-Forward")

                cv2.imshow('otsu',fr)
                cv2.waitKey(10)

                cv2.imshow('cog',cogFrame)
                cv2.waitKey(10)




cap.release()
cv2.destroyAllWindows()
