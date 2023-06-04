# SEDS-PayloadRover2023

Welcome! My name is Steven Rodriguez and I was the 2023 Software Lead for the Student Exploration for the Development of Space Club (SEDS) at FIU. This repository is showcasing the different code that was used in programming the 2023 Payload Rover and is to be used as a reference for future Payload Rover programming. 


# How it Works 

There are 3 folders listed in this repository. 

# 1.) Teensy Arduino Code & Libraries 

This folder contains the main arduino sketch file called teensyLoop.ino and the header files declared inside of it called BME.h , BNO.h , and payload_servos.h. The code in each header file is an edited version of the original code for the [BME 680](https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas/arduino-wiring-test), [BNO 055](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/arduino-code), and the [FITEC 360 servos](https://www.circuitbasics.com/controlling-servo-motors-with-arduino/#:~:text=For%20a%20servo%20motor%20capable%20of%20a%20range,90%20degrees%2C%20and%202000%20microseconds%20%3D%20180%20degrees.). 

The code in the BME.h and BNO.h header files was formatted in a way in which the data collected from the sensors would be printed to the serial monitor in an easily parsable format similar to the [NMEA strings](https://navspark.mybigcommerce.com/content/NMEA_Format_v0.1.pdf) GPS format. 

# 2.) Initial Python Scripts 

This folder contains the original Python scripts called [gpsLoop.py](https://github.com/stevenrodriguezz/SEDS-PayloadRover2023/blob/main/Initial%20Test%20Python%20Scripts%20/gpsLoop.py) and [teensyLoop.py](https://github.com/stevenrodriguezz/SEDS-PayloadRover2023/blob/main/Initial%20Test%20Python%20Scripts%20/teensyLoop.py). The purpose of each one was to create a way for a Linux computer to communicate via I2C and UART with the Teensy's sensors and the GPS respectively. These scripts are what can be considered initial first drafts of code which were tweaked and adjusted over time based on time constraints and desired outcomes. 


# 3.) Final Raspberry Pi Scripts 

This folder contains the final Python scripts called [SerialGPS.py](https://github.com/stevenrodriguezz/SEDS-PayloadRover2023/blob/main/Final%20Raspberry%20Pi%20Python%20Scripts%20/SerialGPS.py) and [SerialTeensy.py](https://github.com/stevenrodriguezz/SEDS-PayloadRover2023/blob/main/Final%20Raspberry%20Pi%20Python%20Scripts%20/SerialTeensy.py) that were imported onto a Raspberry Pi 4b using the 'git clone' command in a directory called SEDS. These scripts imported serial data from the Teensy's sensors and the GPS module and appended this data  to two separate files. These two scripts were automated with the help of Crontab and allowed the scripts to be executed 10 seconds after the Raspberry Pi was turned back on.

The cronjobs used on Crotab were the following:

@reboot sleep 10 && /bin/python / home/ seds/SEDS/SEDS-PayloadRover2023/SerialGPS.py

@reboot sleep 10 && /bin/python / home/ seds/SEDS/SEDS-PayloadRover2023/SerialTeensy.py



