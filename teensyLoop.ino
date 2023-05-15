#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME280.h"
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BNO055.h> //ADXL
#include <utility/imumaths.h>  //ADXL
#include "BME.h"
#include "BNO.h"



void setup() {
  // put your setup code here, to run once:
  //Serial1.begin(9600);
  //Serial1.setTimeout(3000);
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("Beginning BME, ADXL Test: ");

  BME_START();
  BNO_START();

}

void loop() {
 BME_READ();
 BNO_READ();

 
 //GPS_READ();
}
