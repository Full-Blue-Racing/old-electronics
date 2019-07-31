/*
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN <- This is important for the wiring

const byte address[6] = "fullb";  // Setting the address of the radio, it is just a unique 6 digit code that both the transmittor and reciever must have
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);  // Sets the gain of the radio, if not properly shielded may need to reduce this to get the modules to work
  radio.startListening();
}
void loop() {
  if (radio.available()) {
  char text[140] = "";     //this number of zeros has to match the number of characters of the data being sent
  radio.read(&text[0], sizeof(text));

  Serial.println(text);

  delay(1); // This is in microseconds, just adding a delay so that we dont log too much data (may not be a bad thing was just experimenting with it) 
  }
}
