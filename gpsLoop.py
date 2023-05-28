import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600)

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
            with open("TransmitterData.txt", "a") as f:
                f.write(str(position) + "\r\n")
                position = None  # Reset position after writing to the file
                
    time.sleep(2)
