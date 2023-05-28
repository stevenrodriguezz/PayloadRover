import serial

# Replace the port and baudrate with the values used in your Teensy code
ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    if ser.in_waiting > 0:
        data = ser.readline().decode()
        with open('TransmitterData.txt', 'a') as f:
            f.write(data + '\n')
