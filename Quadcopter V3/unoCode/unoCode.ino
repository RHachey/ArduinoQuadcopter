#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define joystickX1 A0
#define joystickY1 A1
#define joystickX2 A2
#define joystickY2 A3

long x1;
long y1;
long x2;
long y2;
long outputInt;

#define CE_PIN  7
#define CSN_PIN 6

const byte address[5] = {'R','x','A','A','A'};
RF24 transmitter(7, 6);
char outputString[20];

long concat(long a, long b, long c, long d) {

  return a * 1000000 + b * 10000 + c * 100 + d;

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

  x1 = (long)map(x1, 0, 1023, 1, 99);
  y1 = (long)map(y1, 0, 1023, 1, 99);
  x2 = (long)map(x2, 0, 1023, 1, 99);
  y2 = (long)map(y2, 0, 1023, 1, 99);

  outputInt = concat(x1, y1, x2, y2);
  sprintf(outputString, "%ld", outputInt);
  transmitter.write(&outputString, sizeof(outputString));
  Serial.println(outputString);

  delay(50);

}
