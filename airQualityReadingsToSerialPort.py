import serial
from datetime import datetime

ser = serial.Serial('/dev/cu.usbmodem11101',115200,timeout=None)
ser.flushInput()
ser.flushOutput()
with open('airquality.log','a') as f:
    while True:
        data_raw = ser.readline()
        curr_time = str(datetime.now())
        f.write(curr_time + " " + str(data_raw) + "\n")
