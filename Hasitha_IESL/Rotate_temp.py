import RPi.GPIO as GPIO     # Importing RPi library to use the GPIO pins
from time import sleep  # Importing sleep from time library

left_pwm=17
left_plus=27
left_minus=22

right_pwm=25
right_plus=23
right_minus=24
          

def tempFunc():
    PARAM_LFREQ=10
    PARAM_RFEFQ=20

    L=PARAM_L_FORWARD_DUTY_RATIO=20
    R=PARAM_R_FORWARD_DUTY_RATIO=10

    left_pwm_drive.ChangeDutyCycle(L)
    right_pwm_drive.ChangeDutyCycle(R)
    GPIO.output(left_plus,True)
    GPIO.output(left_minus,False)
    GPIO.output(right_plus,True)
    GPIO.output(right_minus,False)



GPIO.setmode(GPIO.BCM)          # We are using the BCM pin numbering
GPIO.setup(left_pwm, GPIO.OUT)   # Declaring pins on left as output pin
GPIO.setup(left_plus, GPIO.OUT)
GPIO.setup(left_minus, GPIO.OUT)

GPIO.setup(right_pwm, GPIO.OUT)   # Declaring pins on right as output pin
GPIO.setup(right_plus, GPIO.OUT)
GPIO.setup(right_minus, GPIO.OUT)

left_pwm_drive=GPIO.PWM(left_pwm,100)
right_pwm_drive=GPIO.PWM(right_pwm,100)
left_pwm_drive.start(0)
left_pwm_drive.start(0)


left_pwm_drive.ChangeDutyCycle(10)
GPIO.output(left_plus,True)
GPIO.output(left_minus,False)


left_pwm_drive.ChangeDutyCycle(10)
GPIO.output(right_plus,True)
GPIO.output(right_minus,False)


GPIO.output(left_pwm,True)
GPIO.output(right_pwm,True)

sleep(5)

GPIO.output(left_pwm,False)
GPIO.output(right_pwm,False)

left_pwm_drive.stop()
right_pwm_drive.stop()

GPIO.cleanup()

