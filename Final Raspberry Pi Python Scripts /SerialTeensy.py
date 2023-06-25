import serial
import time

# Assign string value representing path to teh Teensy Data Folder and the Teensy Error Folder to variables called teensyDataFolder and teensyErrorFolder.  
teensyDataFolder = "/home/seds/SEDS/SEDS-PayloadRover2023/teensyData/"
teensyErrorFolder = "/home/seds/SEDS/SEDS-PayloadRover2023/teensyError/"

# Initialize variable as a Serial object to allow communication with the Teensy via USB located at either '/dev/ttyACM0' or  '/dev/ttyACM1' 
ser = serial.Serial('/dev/ttyACM0', 9600)

#This line creates a variable where the 'teensyDataFolder' and 'teensyErrorFolder' path concatenates with their own corresponding strings, matching times converted to integers, and '.txt' file extensions. 
teensyDataFilename = teensyDataFolder + "teensyData-" + str(int(time.time())) + ".txt"
teensyErrorFilename = teensyErrorFolder + "teensyError-" + str(int(time.time())) + ".txt"

#Initialize an infinite loop that reads data from the serial connection. 
while True:
    try: 
        if ser.in_waiting > 0: #if data is received from a serial connection then code in the if block will execute. 
            data = ser.readline().decode() #Reads line from serial port and decodes it from bytes to a string. 
            with open(teensyDataFilename, 'a') as f: #Appends serial data to the file specified under the'teensyDataFilename' variable.
                f.write(str(time.time()) + "," + data)
    except Exception as e: #If there is an error encountered in the try block, it writes the current time and an exception message to the file in the 'teensyErroFilename' file. 
        with open(teensyErrorFilename, 'a') as f:
            f.write(str(time.time()) + "," + str(e))
    time.sleep(1) #Delays the iteration of the loop by 1 second before allowing it execute again. 

