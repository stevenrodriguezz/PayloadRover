import serial
import time
import os

GPSDataFolder = "/home/seds/SEDS/SEDS-PayloadRover2023/gpsData/"

ser = serial.Serial('/dev/ttyACM0', 9600) #try either ACM0 or ACM1 & plug into middle 2 usb ports of Pi 4

gpsDataFilename = GPSDataFolder + "GPS-" + str(int(time.time())) + ".txt"

#position = None  # Define position before the loop

while True:
    if ser.in_waiting > 0:
        gpsRAW = ser.read_all().decode("utf-8")
        with open(gpsDataFilename, "a") as f:
                    f.write("Time:" + str(time.time()) + "\r\n" + gpsRAW)
                    #position = None  # Reset position after writing to the file
    time.sleep(1)
sleep(1)

