#This code is to have the sensor data from the Teensy
#write into a file called TransmitterData.txt
#The Teensy & GPS will both have their own individual code 
#but the final string each prints will save to the same file 
#TransmitterData.txt and then we will an individual code 
#for the Xbee receiver running a loop which gets the txt and 
#sends it over Zigbee Protocol to the receiver. 
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    sensorRaw = ser.readall().decode('utf')
    with open('TransmitterData.txt', 'a') as f:
        f.write(sensorRaw + '\n')
        
    f.close()

#ser.close()? or f.close()?
