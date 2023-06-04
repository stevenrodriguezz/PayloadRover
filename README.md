# SEDS-PayloadRover2023

Welcome! My name is Steven Rodriguez and I was the 2023 Software Lead for the Student Exploration for the Development of Space Club (SEDS) at FIU. This repository is showcasing the different code that was used in programming the 2023 Payload Rover and is to be used as a reference for future Payload Rover programming. 


# How it Works 

There are 3 folders listed in this repository. 

1.) Teensy Arduino Code & Libraries 

This folder contains the main arduino sketch file called teensyLoop.ino and the header files declared inside of it called BME.h , BNO.h , and payload_servos.h. The code in each header file is an edited version of the original code for the [BME 680](https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas/arduino-wiring-test), [BNO 055](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/arduino-code), and the [FITEC 360 servos](https://www.circuitbasics.com/controlling-servo-motors-with-arduino/#:~:text=For%20a%20servo%20motor%20capable%20of%20a%20range,90%20degrees%2C%20and%202000%20microseconds%20%3D%20180%20degrees.). 

This is the main file which includes Adafruit libraries and code used for the [BME 688 Temperature, Pressure, Humidity sensor](https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas/arduino-wiring-test) & the [ADXL 345 accelorometer](https://learn.adafruit.com/adxl345-digital-accelerometer/programming). The ADXL 345 requires two library installation as specified on the ADAfruit website. 

2.) BME.h 

This is same BME 688 code that can be found on [GitHub](https://github.com/adafruit/Adafruit_BME680) or installed on the Arduino IDE except that the void Setup and void loop functions were changed to void BME_READ and void BME_START respectively. These newly named functions were declared in the main file called Integrated_Payload.ino. The entire code found in this file was named BME.h and included as a library in the main file called Integrated_Payload.ino. 


3.) ADXL.h 

This is the same ADXL 345 code that can be found on [Github](https://github.com/adafruit/Adafruit_Sensor) or installed on the Arduino IDE except that the void Setup and void loop functions were changed to void ADXL_READ and void ADXL_START respectively. These newly named functions were declared in the main file called Integrated_Payload.ino. The entire code found in this file was named ADXL.h and included as a library in the main file called Integrated_Payload.ino. 

4.) gps_split.py

This Python code was used to parse the [NMEA strings](https://navspark.mybigcommerce.com/content/NMEA_Format_v0.1.pdf) outputted by the GT U7 GPS module. In this code the NMEA string of interest was the GNGGA string which included data on latitude, longitude, altitude, and number of satellites detected, however, our data of interest was reduced to latitude,longitude, and altitude to preserve computer memory. 

5.) servo_rotating.ino 

This code uses the object class "pwm" and the arduino built in function "writeMicroseconds()" to move two [FITEC servos](https://www.pololu.com/file/0J1433/FS5106R-specs.pdf) continuously. 

