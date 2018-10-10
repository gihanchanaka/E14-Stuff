import cv2
import numpy as np
import RPi.GPIO as GPIO

TURNING_PARAM=-0.1
FORWARD_PARAM=20

TOP_OFFSET=100
FRAME_HEIGHT=600-100
LEFT_OFFSET=250
FRAME_WIDTH=900-250

cap=cv2.VideoCapture(1)
cap.set(3, 640)
cap.set(4, 480)

if __name__== "__main__":
    STATE="BEGIN"
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



            if(np.abs(dir)<FORWARD_PARAM):
                print(dir,"FORWARD")
            else:
                if(dir<0):
                    print(dir,"RIGHT-Forward")
                else:
                    print(dir,"LEFT-Forward")

            cv2.imshow('otsu',fr)
            cv2.waitKey(10)

            cv2.imshow('cog',cogFrame)
            cv2.waitKey(10)




cap.release()
cv2.destroyAllWindows()
