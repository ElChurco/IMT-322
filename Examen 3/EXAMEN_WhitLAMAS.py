import RPi.GPIO as GPIO
import time
import serial

led1_pin = 18
led2_pin = 23
button1_pin = 17
button2_pin = 27
button3_pin = 22

class DoorState:
    OPEN = 1
    CLOSED = 2
    LOCKED = 3

# Conf GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(led1_pin, GPIO.OUT)
GPIO.setup(led2_pin, GPIO.OUT)
GPIO.setup(button1_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(button2_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(button3_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

ser = serial.Serial('/dev/ttyS0', 9600)  # Cambia '/dev/ttyS0' al puerto serial correcto y la velocidad de baudios según sea necesario

#fun
def debounce_callback(channel):
    time.sleep(0.05)
    if GPIO.input(channel) == 0:
        door_state = get_door_state(channel)
        if door_state == DoorState.OPEN:
            ser.write('La puerta está abierta\n'.encode('utf-8'))
        elif door_state == DoorState.CLOSED:
            ser.write('La puerta está cerrada\n'.encode('utf-8'))
        elif door_state == DoorState.LOCKED:
            ser.write('La puerta está bloqueada\n'.encode('utf-8'))

# Función para determinar el estado de la puerta
def get_door_state(channel):
    if channel == button1_pin:
        return DoorState.OPEN
    elif channel == button2_pin:
        return DoorState.CLOSED
    elif channel == button3_pin:
        return DoorState.LOCKED

GPIO.add_event_detect(button1_pin, GPIO.FALLING, callback=debounce_callback, bouncetime=200)
GPIO.add_event_detect(button2_pin, GPIO.FALLING, callback=debounce_callback, bouncetime=200)
GPIO.add_event_detect(button3_pin, GPIO.FALLING, callback=debounce_callback, bouncetime=200)

try:
    while True:
        pass

except KeyboardInterrupt:
    GPIO.cleanup()
