import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)  # change the port and baud rate as needed

while True:
    if ser.in_waiting > 0:
        incoming_data = ser.readline().decode().strip()  # read the incoming data and decode it
        print(incoming_data)  # do something with the incoming data

