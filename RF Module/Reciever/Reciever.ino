#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
Servo servo;
const int servoPin = 6; //digital pin
RF24 radio(40, 41); // CE, CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;
int value;
void setup() {
  Serial.begin(9600);
  // servo config
  servo.attach(servoPin);  
  servo.write(0);
  
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop() {
  if ( radio.available() )
  {
    radio.read( value, sizeof(value));
    Serial.print("original value = "); Serial.println(value);
    value = map(value, 200, 500, 0, 360);//Map value 0-1023 to 0-360 (degrees)
    //use the maapped value for the servo
    Serial.print("angle = "); Serial.println(value);
    servo.write(value);
  }
}
