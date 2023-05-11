import serial
import time

# Replace with the serial port your XBee is connected to
ser = serial.Serial('/dev/ttyUSB0', 9600)

while True:
    # Read data from file1
    with open('file1.txt', 'r') as f:
        data1 = f.read().strip()

    # Read data from file2
    with open('file2.txt', 'r') as f:
        data2 = f.read().strip()

    # Read data from file3
    with open('file3.txt', 'r') as f:
        data3 = f.read().strip()

    # Format the data as a string
    message = f"{data1},{data2},{data3}"

    # Send the message over XBee
    ser.write(message.encode())

    # Wait for some time before sending the next message
    time.sleep(1)
