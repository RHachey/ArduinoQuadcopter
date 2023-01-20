#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define joystickX1 A0
#define joystickY1 A1
#define joystickX2 A2
#define joystickY2 A3

int x1;
int y1;
int x2;
int y2;
int outputInt;

#define CE_PIN  7
#define CSN_PIN 6

const byte address[5] = {'R','x','A','A','A'};
RF24 transmitter(7, 6);
char outputString[20];

int concat(int a, int b, int c, int d) {

  return a * 1000 + b * 100 + c * 10 + d;

}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  transmitter.begin();
  transmitter.openWritingPipe(address);
  transmitter.stopListening();

}

void loop() {
  // put your main code here, to run repeatedly:

  x1 = analogRead(joystickX1);
  y1 = analogRead(joystickY1);
  x2 = analogRead(joystickX2);
  y2 = analogRead(joystickY2);

  if (x1 > 500 && x1 < 512) {

    x1 = 512;

  }

  if (x2 > 500 && x2 < 512) {

    x2 = 512;

  }

  x1 = (int)map(x1, 0, 1023, 1, 9);
  y1 = (int)map(y1, 0, 1023, 1, 9);
  x2 = (int)map(x2, 0, 1023, 1, 9);
  y2 = (int)map(y2, 0, 1023, 1, 9);

  outputInt = concat(x1, y1, x2, y2);
  sprintf(outputString, "%d", outputInt);
  transmitter.write(&outputString, sizeof(outputString));
  Serial.println(outputString);

  delay(50);

}
