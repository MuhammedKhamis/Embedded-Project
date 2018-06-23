#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// Ardunio UNo
RF24 radio(9, 10); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

Servo servo;
const int servoPin = 6; //digital pin

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, addresses[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.println("Start Receiving");

  // servo config
  servo.attach(servoPin);  
  servo.write(0);
}

void loop() {
  if(radio.available()){
    int angle;
    radio.read(&angle, sizeof(angle));
    Serial.print("angle = ");
    Serial.println(angle);
    servo.write(angle);
  }
}
