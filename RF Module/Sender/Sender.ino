#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 53); // CE, CSN
const int flexPin = A0; //analog pin
const uint64_t pipe = 0xE8E8F0F0E1LL; //RF Channel Number

void setup() {
  pinMode(flexPin,INPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe); // 00002
}


void loop() {
  int value = analogRead(flexPin);
  radio.write(value, sizeof(value));
  Serial.println(value);
}
  
  
