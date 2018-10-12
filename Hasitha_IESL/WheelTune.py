'''
Updated 12-10-2018 16:38
'''
import RPi.GPIO as GPIO     # Importing RPi library to use the GPIO pins
import sys
from time import sleep  # Importing sleep from time library

left_pwm=17
left_plus=27
left_minus=22

right_pwm=25
right_plus=23
right_minus=24




if __name__== "__main__":
    LEFT_FREQ=int(sys.argv[1])
    RIGHT_FREQ=int(sys.argv[2])
    LEFT_DUTY_CYCLE = int(sys.argv[3])
    RIGHT_DUTY_CYCLE = int(sys.argv[4])


    print("Left freq: ",LEFT_FREQ)
    print("Right freq: ",RIGHT_FREQ)
    print("Left Duty Cylce: ",LEFT_DUTY_CYCLE)
    print("Right Duty Cylce: ", RIGHT_DUTY_CYCLE)

    GPIO.setmode(GPIO.BCM)          # We are using the BCM pin numbering
    GPIO.setup(left_pwm, GPIO.OUT)   # Declaring pins on left as output pin
    GPIO.setup(left_plus, GPIO.OUT)
    GPIO.setup(left_minus, GPIO.OUT)

    GPIO.setup(right_pwm, GPIO.OUT)   # Declaring pins on right as output pin
    GPIO.setup(right_plus, GPIO.OUT)
    GPIO.setup(right_minus, GPIO.OUT)

    left_pwm_drive=GPIO.PWM(left_pwm,LEFT_FREQ)
    right_pwm_drive=GPIO.PWM(right_pwm,RIGHT_FREQ)
    left_pwm_drive.start(0)
    right_pwm_drive.start(0)

    left_pwm_drive.ChangeDutyCycle(LEFT_DUTY_CYCLE)
    right_pwm_drive.ChangeDutyCycle(RIGHT_DUTY_CYCLE)

    GPIO.output(left_plus,True)
    GPIO.output(left_minus,False)
    GPIO.output(right_plus,True)
    GPIO.output(right_minus,False)

    left_pwm_drive.ChangeDutyCycle(0)
    right_pwm_drive.ChangeDutyCycle(0)


    sleep(15)
    exit(0)
