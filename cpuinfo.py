import serial
import time

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)

def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(2)
    data = arduino.readline()
    return data

while True:
    with open("/sys/class/thermal/thermal_zone0/temp", "r") as temp:
        write_read(str(int(temp.read()) / 1000))
