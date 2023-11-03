import serial
import time

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)

# writes to arduino serial and then returns what the arduino sends back
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(2)
    data = arduino.readline()
    return data

def get_temp():
    with open("/sys/class/thermal/thermal_zone0/temp", "r") as temp:
        return int(temp.read()) / 1000


while True:
    write_read(str(get_temp()))
