
/***
 *      _____                
 *     |  __ \                  By Rafael Velasquez and William Ocampo          
 *     | |__) |__ _ __   ___    Copyright 2022 Roig Corporation of America
 *     |  ___/ _ \ '_ \ / _ \
 *     | |  |  __/ |_) |  __/
 *     |_|   \___| .__/ \___|
 *               | |         
 *               |_|         
 *     The ROiG Companion module      
 */



/*
 * Control Bit Values
 * 1 -> Motor control
 * 20 -> Full forward
 * 21 -> Full reverse
 * 99-> Force Reset
 * 
 * 
 * sysmsg_code
 * The idiot error reporitng way without sening string
 * 0
 * 1 -> starting up system
 * 2 -> set up complete
 * 3 -> Command recieved
 * 4
 * 5 -> BME initialization Error!
 * 6
 * 7
 * 8 -> Invalid string length detected
 * 9 -> Invalid Control Code
 * 10
 */


#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define pwmL 3
#define motorLpin1 5
#define motorLpin2 6

#define pwmR 4
#define motorRpin1 7
#define motorRpin2 8

#define data_delay_interval 10 //in ms
#define SEALEVELPRESSURE_HPA (1013.25)

#define SCB_AIRCR (*(volatile uint32_t *)0xE000ED0C) // Application Interrupt and Reset Control location


Adafruit_BME680 bme; 
const int MPU_addr=0x68;



void stringer();//turn all data into nice csv string
void serial_reader();
void setup_MPU();
void read_MPU(double* x,double* y,double* z,double* p_acx,double* p_acy,double* p_acz);
void motor_control(int L_motor_control, int R_motor_control);
void resetFunction_1()
{
  Serial.println("reboot");
  SCB_AIRCR = 0x05FA0004;
}

byte sysmsg_code = 0;


void setup() 
{
  
  Serial.begin(115200);
  Serial.setTimeout(100);
  Serial.println("0,0,0,0,0,0,0,0,0,0,0,1");
  

  setup_MPU();

  if (!bme.begin()) 
    Serial.println("0,0,0,0,0,0,0,0,0,0,0,5");

    
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms


  pinMode(pwmL, OUTPUT);
  pinMode(motorLpin1, OUTPUT);
  pinMode(motorLpin2, OUTPUT);
  
  pinMode(pwmR, OUTPUT);
  pinMode(motorRpin1, OUTPUT);
  pinMode(motorRpin2, OUTPUT);

  
  //Serial.println("start");
  Serial.println("0,0,0,0,0,0,0,0,0,0,0,2");
}


void loop() 
{
  serial_reader();
  stringer();
  //delay(data_delay_interval);
  sysmsg_code = 0;


}




void serial_reader()//Drives all the motors
{
      if (Serial.available() > 0) 
      {
          int Data_val_1 = 0, Data_val_2 = 0;
          int control_bit = 0;
          String raw_data = Serial.readString();
          //Serial.println(raw_data);
          
          const char* data_char = raw_data.c_str();
          //Serial.println(data_char);
          
           if(sscanf(data_char, "%d,%d,%d", &control_bit,&Data_val_1,&Data_val_2) == 3)
           {
            //Serial.println(control_bit);
            switch(control_bit)
              {
                case 0:
                  motor_control(0, 0);
                  break;
                case 1:
                  motor_control(Data_val_1, Data_val_2);
                  sysmsg_code = 3;
                  break;
    
                case 20:
                  motor_control(255, 255);
                  sysmsg_code = 3;
                  break;
                case 21:
                  motor_control(-255, -255);
                  sysmsg_code = 3;
                  break;
                case 99:
                  sysmsg_code = 3;
                  resetFunction_1();
                  break;
                default:
                  sysmsg_code = 9;
              }            
          }
          else
            sysmsg_code = 8;
            
      }
}




void motor_control(int L_motor_control, int R_motor_control)
{
  if((L_motor_control > 0 && L_motor_control <= 255))
    {
      digitalWrite(motorLpin1, HIGH);
      digitalWrite(motorLpin2, LOW);
      analogWrite(pwmL, L_motor_control);
    }
  else if(L_motor_control < 0 && L_motor_control >= -255)
    {
      digitalWrite(motorLpin1, LOW);
      digitalWrite(motorLpin2, HIGH);
      analogWrite(pwmL, -L_motor_control);
    }
  else //if (control_bit == 1 && (L_motor_control>=0 && L_motor_control < 25) && (R_motor_control>=0 && R_motor_control < 25))
    {
      digitalWrite(motorLpin1, LOW);
      digitalWrite(motorLpin2, LOW);
      analogWrite(pwmL, 0);
    }
    
  if((R_motor_control > 0 && R_motor_control <= 255))
    {
      digitalWrite(motorRpin1, HIGH);
      digitalWrite(motorRpin2, LOW);
      analogWrite(pwmR, R_motor_control);
    }
  else if(R_motor_control < 0 && R_motor_control >= -255)
    {
      digitalWrite(motorRpin1, LOW);
      digitalWrite(motorRpin2, HIGH);
      analogWrite(pwmR, -R_motor_control);
    }
  else //if (control_bit == 1 && (L_motor_control>=0 && L_motor_control < 25) && (R_motor_control>=0 && R_motor_control < 25))
    {
      digitalWrite(motorRpin1, LOW);
      digitalWrite(motorRpin2, LOW);
      analogWrite(pwmR, 0);
    }
}






void stringer()  //Compress all data to a single BIG string. They will be in the form of a csv
{
  double angle_x = 0,angle_y = 0,angle_z = 0,accel_x = 0,accel_y = 0,accel_z = 0;
  read_MPU(&angle_x,&angle_y,&angle_z,&accel_x,&accel_y,&accel_z);
  bme.performReading();
  //Order of data: Temperature Pressure Humidity Gas_Resistance  Pressure real_Altitude(See comment on top of code)  Acceleration_X_axis Acceleration_Y_axis Acceleration_Z_axis Gyro_x Gyro_y Gyro_z system_code
  Serial.println(String(String(bme.temperature,2) + "," //C
                     + String((bme.pressure / 100.0),2) + "," //hPa
                     + String(bme.humidity,2) + "," //%
                     + String((bme.gas_resistance / 1000.0),2) +"," //KOhms" 
                     + String(bme.readAltitude(SEALEVELPRESSURE_HPA),2)+ "," //m
                     //MPU
                     + String(angle_x,2)+ "," + String(angle_y,2) + "," + String(angle_z,2) + "," 
                     + String(accel_x,2)+ "," + String(accel_y,2) + "," + String(accel_z,2) + "," 
                     + String(sysmsg_code)));
}


void setup_MPU()
{
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);
  // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x10);                   // Set the register bits as 00010000 (1000deg/s full scale)
  Wire.endTransmission(true);
  delay(20);
}

void read_MPU(double* x,double* y,double* z,double* p_acx,double* p_acy,double* p_acz)
{
  int16_t AcX,AcY,AcZ;
  //int16_t Tmp,GyX,GyY,GyZ;
  int minVal=265;
  int maxVal=402;
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
   
  *x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  *y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  *z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  *p_acx= ((float)AcX) / 16384.0;
  *p_acy= ((float)AcY) / 16384.0;
  *p_acz= ((float)AcZ) / 16384.0;

  

}
