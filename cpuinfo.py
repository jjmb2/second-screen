import datetime
import serial
import threading
import time

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)
# global flag to stop all threads
stop_threads = False

# writes to arduino serial and then returns what the arduino sends back
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(1)
    data = arduino.readline()
    return data

def get_temp():
    with open("/sys/class/thermal/thermal_zone0/temp", "r") as temp:
        return int(temp.read()) / 1000

# target for thread which sends temperature data to the arduino
def send_temp():
    while not stop_threads:
        write_read(str(get_temp()))

# create the thread which sends temperature data (necessary because threads are single-use)
def temp_thread():
    return threading.Thread(target=send_temp)

def send_time():
    while not stop_threads:
        now = datetime.datetime.now()
        time_str = now.strftime("%H:%M")
        write_read(time_str)

def clock_thread():
    return threading.Thread(target=send_time)

def send_all():
    while not stop_threads:
        all = str(get_temp())
        all += '\n';
        now = datetime.datetime.now()
        all += now.strftime("%H:%M")
        write_read(all)

def all_thread():
    return threading.Thread(target=send_all)

help_string = "['t': temperature info, 'g': temperature graph, 'c': clock, 'a': all, 'q': quit]"
print(help_string)

while True:
    cmd = input("> ")

    match cmd:
        case 't':
            write_read('q')
            stop_threads = True
            write_read('t')
            stop_threads = False
            temp_thread().start()
        case 'g':
            write_read('q')
            stop_threads = True
            write_read('g')
            stop_threads = False
            temp_thread().start()
        case 'c':
            write_read('q')
            stop_threads = True
            write_read('c')
            stop_threads = False
            clock_thread().start()
        case 'a':
            write_read('q')
            stop_threads = True
            write_read('a')
            stop_threads = False
            all_thread().start()
        case 'q':
            write_read('q')
            stop_threads = True
            break
        case _:
            print(help_string)
