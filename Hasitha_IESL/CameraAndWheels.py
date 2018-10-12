'''
Update 10-10-2018 21:01
'''

import cv2
import numpy as np
import RPi.GPIO as GPIO
import sys
from time import sleep  # Importing sleep from time library

#Motor driver pins
left_pwm = 17
left_plus = 27
left_minus = 22

right_pwm=25
right_plus=23
right_minus=24

LEFT_FREQ=100
RIGHT_FREQ=100



TURNING_PARAM=-0 #Tune this parameter to decide when to turn
FORWARD_PARAM=5 #Tune this parameter for the tolerance in mis-alignment


WHITE_PARAM=0.5 #What intensity qualifies as white?
FULL_BLACK_PARAM=0.05 #When to go back
COMPLICATED_PARAM=0.8 #When to start looking for arrows


TOP_OFFSET=10 #Window size param
FRAME_HEIGHT=400 #Window size param
LEFT_OFFSET=25 #Window size param
FRAME_WIDTH=500 #Window size param

cap=cv2.VideoCapture(0)
'''cap.set(3, 640)
cap.set(4, 480)'''




def turnRight():
    print("Turning right")
    RIGHT_TURN_LeftMotor_DUTY_CYCLE=10
    RIGHT_TURN_RightMotor_DUTY_CYCLE=20
    left_pwm_drive.ChangeDutyCycle(RIGHT_TURN_LeftMotor_DUTY_CYCLE)
    right_pwm_drive.ChangeDutyCycle(RIGHT_TURN_RightMotor_DUTY_CYCLE)

    GPIO.output(left_plus, True)
    GPIO.output(left_minus, False)
    GPIO.output(right_plus, True)
    GPIO.output(right_minus, False)

def turnLeft():
    print("Turning left")
    LEFT_TURN_LeftMotor_DUTY_CYCLE=10
    LEFT_TURN_RightMotor_DUTY_CYCLE=20
    left_pwm_drive.ChangeDutyCycle(LEFT_TURN_LeftMotor_DUTY_CYCLE)
    right_pwm_drive.ChangeDutyCycle(LEFT_TURN_LeftMotor_DUTY_CYCLE)

    GPIO.output(left_plus, True)
    GPIO.output(left_minus, False)
    GPIO.output(right_plus, True)
    GPIO.output(right_minus, False)

def goForward():
    print("Going forward")
    GO_FORWARD_LeftMotor_DUTY_CYCLE=10
    GO_FORWARD_RightMotor_DUTY_CYCLE=20
    left_pwm_drive.ChangeDutyCycle(GO_FORWARD_LeftMotor_DUTY_CYCLE)
    right_pwm_drive.ChangeDutyCycle(GO_FORWARD_RightMotor_DUTY_CYCLE)

    GPIO.output(left_plus, True)
    GPIO.output(left_minus, False)
    GPIO.output(right_plus, True)
    GPIO.output(right_minus, False)

def goBACK():
    print("Going back")
    GO_BACK_LeftMotor_DUTY_CYCLE=10
    GO_BACK_RightMotor_DUTY_CYCLE=20
    left_pwm_drive.ChangeDutyCycle(GO_BACK_LeftMotor_DUTY_CYCLE)
    right_pwm_drive.ChangeDutyCycle(GO_BACK_RightMotor_DUTY_CYCLE)

    GPIO.output(left_plus, False)
    GPIO.output(left_minus, True)
    GPIO.output(right_plus, False)
    GPIO.output(right_minus, True)


def stopMotors():
    print("Stopping motors")
    left_pwm_drive.ChangeDutyCycle(0)
    right_pwm_drive.ChangeDutyCycle(0)

    GPIO.output(left_plus, False)
    GPIO.output(left_minus, False)
    GPIO.output(right_plus, False)
    GPIO.output(right_minus, False)


if __name__== "__main__":
    '''
     BEGIN MOTORS
    '''
    GPIO.setmode(GPIO.BCM)  # We are using the BCM pin numbering
    GPIO.setup(left_pwm, GPIO.OUT)  # Declaring pins on left as output pin
    GPIO.setup(left_plus, GPIO.OUT)
    GPIO.setup(left_minus, GPIO.OUT)

    GPIO.setup(right_pwm, GPIO.OUT)  # Declaring pins on right as output pin
    GPIO.setup(right_plus, GPIO.OUT)
    GPIO.setup(right_minus, GPIO.OUT)

    left_pwm_drive = GPIO.PWM(left_pwm, LEFT_FREQ)
    right_pwm_drive = GPIO.PWM(right_pwm, RIGHT_FREQ)
    left_pwm_drive.start(0)
    right_pwm_drive.start(0)
    '''
     BEGIN MOTORS over
    '''


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
            cv2.imshow('Frame',th1)
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

            whiteSum = np.sum(
                np.sum(gray[TOP_OFFSET:H + TOP_OFFSET, LEFT_OFFSET:W + LEFT_OFFSET] > int(255 * WHITE_PARAM)))
            whiteRatio = whiteSum / (H * W * 1.0)







            print("White ratio= ",whiteRatio)
            if whiteRatio<FULL_BLACK_PARAM or whiteRatio>COMPLICATED_PARAM:
                if whiteRatio<FULL_BLACK_PARAM:
                    if PREV_STEP=="FORWARD":
                        goBACK()
                    elif PREV_STEP=="RIGHT-Forward":
                        goBACK()
                    elif PREV_STEP=="LEFT-Forward":
                        goBACK()
                    else:
                        goForward()

                elif whiteRatio>COMPLICATED_PARAM:
                    print("Start looking for arrows")

                cv2.imshow('Frame',gray[TOP_OFFSET:H+TOP_OFFSET,LEFT_OFFSET:W+LEFT_OFFSET])
                cv2.waitKey(10)

            else:

                for y in range(H):
                    M[y] = 0
                    COG[y] = 0

                    # print(COG[y],M[y])

                    M[y] = np.sum(fr[y, :])
                    COG[y] = np.dot(fr[y, :], np.arange(0, W))

                    if M[y] > 0:
                        COG[y] = COG[y] / M[y]
                    else:
                        COG[y] = W / 2

                    cogFrame[y, COG[y]] = 1
                COG2 = COG - W / 2
                np.flip(COG2, 0)
                dir = np.dot(COG2, np.exp(TURNING_PARAM * np.arange(H, 0, -1))) / np.sum(
                    np.exp(TURNING_PARAM * np.arange(H, 0, -1)))

                cogFrame[:, int(dir + W / 2)] = 1

                if(np.abs(dir)<FORWARD_PARAM):
                    PREV_STEP="FORWARD"
                    goForward()
                else:
                    if(dir>0):
                        PREV_STEP="RIGHT-Forward"
                        turnRight()
                    else:
                        PREV_STEP="LEFT-Forward"
                        turnLeft()

                cv2.imshow('Frame',fr)
                cv2.waitKey(10)

                cv2.imshow('cog',cogFrame)
                cv2.waitKey(10)




cap.release()
cv2.destroyAllWindows()
