#include <Adafruit_Sensor.h>

//Header files located in current github repository folder
#include "BME.h"
#include "BNO.h"
#include "payload_servos.h"
#include "gps.h"

//Constants representing delay period between sensor readings in milliseconds.
#define BNO055_SAMPLERATE_DELAY_MS 2000
#define BME280_SAMPLERATE_DELAY_MS 1000


void setup() {
  Serial.begin(9600); // Initiate serial communication with baud rate of 9600. 
  Serial.println("Beginning BME, BNO Test: ");

  BME_START(); // The BME_START() function and SERVO_START() function are called from the BME.h and payload_servo.h header files respectively. 
  SERVO_START();
}

void loop() {
  static unsigned long BNOTime = 0;
  static unsigned long BMETime = 0;
  //static unsigned long GPSTime = 0;
  if (millis()>BNOTime){
    BNO_READ();
    BNOTime = millis() + BNO055_SAMPLERATE_DELAY_MS;
  }
  
  if (millis()>BMETime){
    BME_READ();
    BMETime = millis() + BME280_SAMPLERATE_DELAY_MS;
  }
  
  SERVO_READ();
