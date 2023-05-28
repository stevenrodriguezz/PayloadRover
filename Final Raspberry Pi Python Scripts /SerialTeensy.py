import serial
import time
import os

teensyDataFolder = "/home/seds/SEDS/SEDS-PayloadRover2023/teensyData/"
teensyErrorFolder = "/home/seds/SEDS/SEDS-PayloadRover2023/teensyError/"

# Replace the port and baudrate with the values used in your Teensy code
ser = serial.Serial('/dev/ttyACM0', 9600)

#os.listdir(teensyDataFolder)

teensyDataFilename = teensyDataFolder + "teensyData-" + str(int(time.time())) + ".txt"
teensyErrorFilename = teensyErrorFloder + "teensyError-" + str(int(time.time())) + ".txt"


while True:
    try:
        if ser.in_waiting > 0:
            data = ser.readline().decode()
            with open(teensyDataFilename, 'a') as f:
                f.write(str(time.time()) + "," + data)
    except Exception as e:
        with open(teensyErrorFilename, 'a') as f:
            f.write(str(time.time()) + "," + str(e))
    time.sleep(1)

