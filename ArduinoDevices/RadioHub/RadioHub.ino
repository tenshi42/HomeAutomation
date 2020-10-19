#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
RF24 radio(9,10);
const uint64_t pipes[2] = { 0x0c0c0c0c0c, 0x0606070606 };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  printf_begin();
  Serial.write("Setup\n");
  initRadio();
  Serial.write("Radio ready !\n");
}

void initRadio(){
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.stopListening();
  radio.startListening();
  radio.printDetails();
}

void sendRF(String msg){
  radio.stopListening();
  
  char payload[32] = "";

  msg.toCharArray(payload, sizeof(payload));

  bool ok = radio.write(&payload, sizeof(payload));

  if (ok)
      Serial.println("ok...");
    else
      Serial.println("failed.");
      
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String msg = Serial.readString();
    sendRF(msg);
  }

  delay(1);

  //sendRF("AudSw:SET:11");
  //delay(1000);
}
