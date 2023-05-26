import serial
import time
import os

GPSDataFolder = "/home/stevenchurro/Projects/Testloops/gpsData/"

ser = serial.Serial('/dev/ttyACM0', 9600)

gpsDataFilename = GPSDataFolder + "GPS-" + str(int(time.time())) + ".txt"

position = None  # Define position before the loop

while True:
    if ser.in_waiting > 0:
        gpsRAW = ser.read_all().decode("utf-8")
        gpsSeparate = gpsRAW.split("\r\n")
        for i in gpsSeparate:
            if "GNGGA" in i:
                gpsParsed = i.split(",")
                position = {
                    "latitude": gpsParsed[2],
                    "N": gpsParsed[3],
                    "longitude": gpsParsed[4],
                    "W": gpsParsed[5],
                    "altitude": gpsParsed[8],
                }
            if position is not None:  # Check if position is defined
                with open(gpsDataFilename, "a") as f:
                    f.write("Time:" + str(time.time()) + "\r\n" + gpsRAW)
                    position = None  # Reset position after writing to the file

    time.sleep(1)

