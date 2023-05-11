import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    if ser.in_waiting > 0:
        gpsRAW = ser.read_all().decode("utf-8")
        with open("TransmitterData.txt", "a") as f:
            f.write(gpsRAW + "\r\n")
		#f.close()
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
               #latitude = gpsData[2]
               # longitude = gpsData[4]
    time.sleep(2)
