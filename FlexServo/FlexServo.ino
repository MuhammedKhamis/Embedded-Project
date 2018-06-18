#include <Servo.h>
Servo servo;
const int servoPin = 6; //digital pin
const int flexPin = A0; //analog pin

void setup() {
  // servo config
  servo.attach(servoPin);  
  servo.write(0);
  
  // flex config
  pinMode(flexPin,INPUT);

  Serial.begin(9600);
}

void loop() {
  //Read and save analog value from potentiometer  
  int value = analogRead(flexPin);
  Serial.println(value);
  // check the lease and greatest value for flex sensor
  value = map(value, 700, 900, 0, 360);//Map value 0-1023 to 0-360 (degrees)
  //use the maapped value for the servo
  Serial.print("angle = "); Serial.println(value);
  servo.write(value);
  delay(20);
}
