#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 53); // CE, CSN 
const byte addresses[][6] = {"00001", "00002"};

const int flexPin = A0; //analog pin

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  // flex config
  pinMode(flexPin,INPUT);
}

void loop() {
  int value = analogRead(flexPin);
  // check the least and greatest value for flex sensor
  value = map(value, 200, 500, 0, 180);//Map value 0-1023 to 0-180 (degrees)
  Serial.print("angle = "); Serial.println(value);

  radio.write(&value, sizeof(value));
  Serial.println("Data Sent");
}
