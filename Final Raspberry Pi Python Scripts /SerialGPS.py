import serial
import time
import os

# Assign string value representing path to gpsData folder to a variable called GPSDataFolder 
GPSDataFolder = "/home/seds/SEDS/SEDS-PayloadRover2023/gpsData/"

# Initialize variable as a Serial object to allow communication with GPS via USB located at either '/dev/ttyACM0' or  '/dev/ttyACM1' 
ser = serial.Serial('/dev/ttyACM0', 9600) 

#This line creates a variable where the 'GPSDataFolder' path concatenates with the string 'GPS-' , the current time converted to an integer, and a '.txt' file extension. 
gpsDataFilename = GPSDataFolder + "GPS-" + str(int(time.time())) + ".txt"

#Initiate an infinite loop that will run the code inside the loop continously until power on the rapsberry pi is disabled. 
while True:
    if ser.in_waiting > 0:  #Checks if there is data to be read, if there is then the code inside the 'if' block will execute.
        gpsRAW = ser.read_all().decode("utf-8") # Reads all available data from the serial connection and assigns it to a variable called gpsRAW. 
        with open(gpsDataFilename, "a") as f: #This block opens previosuly specified 'gpsDataFilename' in append mode and assigns it to the file object 'f'.
                    f.write("Time:" + str(time.time()) + "\r\n" + gpsRAW) # Writes a string to the file, the current time, a line break, and the received GPS data. 
                    
    time.sleep(1) #Pauses the execution of the code for 1 second allowing for a delay between iterations. 

