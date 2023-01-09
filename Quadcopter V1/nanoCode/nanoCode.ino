#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 reciever(2,3);
const byte address[6] = "12345";

void setup() {

  Serial.begin(115200);

  reciever.begin();
  reciever.openReadingPipe(0, address);
  reciever.setPALevel(RF24_PA_MIN);
  reciever.startListening();
  
}

void loop() {

  if (reciever.available()) {

    char input[32] = "";
    reciever.read(&input, sizeof(input));
    Serial.println(input);
    
  }

}
