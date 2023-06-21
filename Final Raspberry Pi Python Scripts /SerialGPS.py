import serial
import time
import os

# Assign string value representing path to gpsData folder to a variable called GPSDataFolder 
GPSDataFolder = "/home/seds/SEDS/SEDS-PayloadRover2023/gpsData/"

# Initialize variable as a Serial object to allow communication with GPS via USB located at either '/dev/ttyACM0' or  '/dev/ttyACM1' 
ser = serial.Serial('/dev/ttyACM0', 9600) 

#This line creates a string representing the filename for the GPS data file where the GPS data will be appended to inside of the GPSDataFolder.
gpsDataFilename = GPSDataFolder + "GPS-" + str(int(time.time())) + ".txt"

while True:
    if ser.in_waiting > 0:
        gpsRAW = ser.read_all().decode("utf-8")
        with open(gpsDataFilename, "a") as f:
                    f.write("Time:" + str(time.time()) + "\r\n" + gpsRAW)
                    
    time.sleep(1)
sleep(1)
