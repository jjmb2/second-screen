import serial
import threading
import time

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)
# global flag to stop all threads
stop_threads = False

# writes to arduino serial and then returns what the arduino sends back
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(2)
    data = arduino.readline()
    return data

def get_temp():
    with open("/sys/class/thermal/thermal_zone0/temp", "r") as temp:
        return int(temp.read()) / 1000

# target for thread which sends temperature data to the arduino
def send_temp():
    while not stop_threads:
        write_read(str(get_temp()))

txt_temp_thread = threading.Thread(target=send_temp)

while True:
    cmd = input("['t': temperature info, 'q': quit]" )

    match cmd:
        case 't':
            txt_temp_thread.start()
        case 'q':
            stop_threads = True
            break
