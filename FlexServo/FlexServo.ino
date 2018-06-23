#include <Servo.h>

//Servo Part
Servo servo;
const int servoPin = 6; //digital pin

//Flex Sensor Part
const int flexPin = A0; //analog pin

//Flex Sensor Parameters
int min_value = 2000;
int max_value = 0;

const int sampling_rate = 200;

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
  long value = movingAverageFilter();
  Serial.println("Average Sensor Value = " + String(value));

  // check the least and greatest value for flex sensor.
  min_value = min(min_value, value);
  max_value = max(max_value, value);
  Serial.println("Min Sensor Value = " + String(min_value));
  Serial.println("Max Sensor Value = " + String(max_value));
  
  // we find that minValue = 480 and maxValue = 650
  // then map the flex value to degree for the servo motor.
  int degree = map(value, 450, 680, 0, 180);
  
  //use the mapped value for the servo
  Serial.println("angle" + String(degree));
  servo.write(degree);
  
  // for stabilization make delay.
  delay(20);
}

long movingAverageFilter(){
  long value = 0;
  for(int sample = 1; sample <= sampling_rate; sample++){
    value += analogRead(flexPin);
  }
  value = value / sampling_rate;
  return value;
}

