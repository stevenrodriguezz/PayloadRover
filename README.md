# SEDS-PayloadRover2023

#DISCLAIMER 

This code is by no means finished and will still require some tweaks for it all to run smoothly as one unit. There is still code that is pending related to the Xbee Transmitter and Receiver modules that have not been added to this repository yet. 

# PayloadRover2023

Welcome! My name is Steven Rodriguez and I was the 2023 Software Lead for the Student Exploration for the Development of Space Club (SEDS) at FIU. This repository is showcasing the different code that was used in programming the 2023 Payload Rover and is to be used as a reference for future Payload Rover programming. 


# How it Works 

There are 5 files listed in this repository. 

1.) Integrated_Payload.ino 

This is the main file which includes Adafruit libraries and code used for the [BME 688 Temperature, Pressure, Humidity sensor](https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas/arduino-wiring-test) & the [ADXL 345 accelorometer](https://learn.adafruit.com/adxl345-digital-accelerometer/programming). The ADXL 345 requires two library installation as specified on the ADAfruit website. 

2.) BME.h 

This is same BME 688 code that can be found on [GitHub](https://github.com/adafruit/Adafruit_BME680) or installed on the Arduino IDE except that the void Setup and void loop functions were changed to void BME_READ and void BME_START respectively. These newly named functions were declared in the main file called Integrated_Payload.ino. The entire code found in this file was named BME.h and included as a library in the main file called Integrated_Payload.ino. 


3.) ADXL.h 

This is the same ADXL 345 code that can be found on [Github](https://github.com/adafruit/Adafruit_Sensor) or installed on the Arduino IDE except that the void Setup and void loop functions were changed to void ADXL_READ and void ADXL_START respectively. These newly named functions were declared in the main file called Integrated_Payload.ino. The entire code found in this file was named ADXL.h and included as a library in the main file called Integrated_Payload.ino. 

4.) gps_split.py

This Python code was used to parse the [NMEA strings](https://navspark.mybigcommerce.com/content/NMEA_Format_v0.1.pdf) outputted by the GT U7 GPS module. In this code the NMEA string of interest was the GNGGA string which included data on latitude, longitude, altitude, and number of satellites detected, however, our data of interest was reduced to latitude,longitude, and altitude to preserve computer memory. 

5.) servo_rotating.ino 

This code uses the object class "pwm" and the arduino built in function "writeMicroseconds()" to move two [FITEC servos](https://www.pololu.com/file/0J1433/FS5106R-specs.pdf) continuously. 

