#include <Servo.h>

#define servoPin1 9 // Represents the PWM pin number each servo signal was connected to
#define servoPin2 10

Servo servo1; // Declare two servo objects called servo1 & servo2
Servo servo2; 



void SERVO_START() {
servo1.attach(servoPin1);
servo2.attach(servoPin2);
}

void SERVO_READ() {
  servo1.writeMicroseconds(700);
  servo2.writeMicroseconds(2300);

}
