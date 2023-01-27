#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN  2
#define CSN_PIN 3
#define motorPin 5
#define motorPin2 6

const byte address[5] = {'R','x','A','A','A'};
RF24 reciever(CE_PIN, CSN_PIN);
long inputLong = 50505050;
int x1;
int y1;
int x2;
int y2;
long lastThree;
long lastTwo;
long lastOne;

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
    char *p;
    inputLong = strtol(input, &p, 10);
    
  }

  lastThree = inputLong - inputLong / 1000000 * 1000000;
  lastTwo = lastThree - lastThree / 10000 * 10000;
  lastOne = lastTwo - lastTwo / 100 * 100;

  x1 = map(inputLong / 1000000, 1, 99, 0, 255);
  y1 = map(lastThree / 10000, 1, 99, 0, 255);
  x2 = map(lastTwo / 100, 1, 99, 0, 255);
  y2 = map(lastOne, 1, 99, 0, 255);
  

  analogWrite(motorPin, x1);
  analogWrite(motorPin2, y1);

}
