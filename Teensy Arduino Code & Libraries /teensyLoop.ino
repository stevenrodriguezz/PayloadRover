#include <Adafruit_Sensor.h>

//Header files located in current github repository folder
#include "BME.h"
#include "BNO.h"
#include "payload_servos.h"

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
// Two static variables are declared and initialized to zero to keep track of the last time the BNO and BME sensors were read. 
  static unsigned long BNOTime = 0;
  static unsigned long BMETime = 0;

// Both conditional statements call the BNO_READ() and BME_READ() functions if their current times obtained using millis() are greater than zero.
// Both functioned that are called are derived from the BNO.h and BME.h header files and start reading their corrresponding sensors data when called, update to their current time plus the delay period. 
  if (millis()>BNOTime){
    BNO_READ();
    BNOTime = millis() + BNO055_SAMPLERATE_DELAY_MS;
  }
  
  if (millis()>BMETime){
    BME_READ();
    BMETime = millis() + BME280_SAMPLERATE_DELAY_MS;
  }
  
  SERVO_READ(); //This function is called in every iteration of the loop from the payload_servo.h file. 
