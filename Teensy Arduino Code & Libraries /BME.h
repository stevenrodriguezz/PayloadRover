#include "Adafruit_BME280.h"


#define BME_SDA 18
#define BME_SCL 19

Adafruit_BME280 bme;

void BME_START() {
  Serial.println(F("BME280 test"));
  unsigned status;
  status = bme.begin();  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
}

void BME_READ() {
  Serial.println("1,BME,DATA," + String(bme.readTemperature()) +"," + String(bme.readPressure() / 100.0F)+"," + String(bme.readHumidity()) + ",1");
  
}




