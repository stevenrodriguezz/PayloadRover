import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 9600) # set the serial port and baud rate

# read the data from the file
with open("TransmitterData.txt", "r") as f:
    data = f.read()

# send the data over the Xbee network
ser.write(data.encode())

# wait for a response from the receiver
response = ser.readline().decode().strip()

# print the response
print(response)

# close the serial connection
ser.close()
