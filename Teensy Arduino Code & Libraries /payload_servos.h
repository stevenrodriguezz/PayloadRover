#include <Servo.h>

#define servoPin1 9
#define servoPin2 10

Servo servo1;
Servo servo2; 



void SERVO_START() {
servo1.attach(servoPin1);// put your setup code here, to run once:
servo2.attach(servoPin2);
}

void SERVO_READ() {
  //Serial.println("Writing to Servos");
  servo1.writeMicroseconds(700);
  servo2.writeMicroseconds(2300);

  // put your main code here, to run repeatedly:

}
