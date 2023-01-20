#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN  2
#define CSN_PIN 3
#define motorPin 5

const byte address[5] = {'R','x','A','A','A'};
RF24 reciever(CE_PIN, CSN_PIN);
int inputInt = 5555;
int strength;

void setup() {

  Serial.begin(115200);
  Serial.println("test");
  reciever.begin();
  reciever.openReadingPipe(1, address);
  reciever.startListening();
  
}

void loop() {

  if (reciever.available()) {

    char input[20] = "";
    reciever.read(&input, sizeof(input));
    Serial.println(input);
    inputInt = atoi(input);
    
  }

  strength = map(inputInt / 1000, 1, 9, 0, 255);
  Serial.println(strength);

  analogWrite(motorPin, strength);

}
