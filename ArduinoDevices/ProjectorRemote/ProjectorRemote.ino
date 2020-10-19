#include <IRremote.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <printf.h>
RF24 radio(9,10);
const uint64_t pipes[2] = { 0x0c0c0c0c0c, 0x0606070606 };
String uid = "ProRm"; // unique id (5 char)

IRsend irsend;

long POWER_CMD = 16464071;
long MUTE_CMD = 16453871;
long SOUND_DOWN_CMD = 16507421;
long SOUND_UP_CMD = 16506911;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  printf_begin();
  initRadio(); 
}

void initRadio(){
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
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

void sendIRCmd(long cmd, int nbTimes, int intervals){
  for(int i = 0 ; i < nbTimes ; i++){
    irsend.sendNEC(cmd, 32);
    delay(intervals);
  }
}

void sendIRPowerCmd(int state){
  if(state == 1){
    sendIRCmd(POWER_CMD, 1, 0);
    Serial.println("power on");
  }
  else{
    sendIRCmd(POWER_CMD, 2, 500);
    Serial.println("power off");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()){  
    char msg[32] = "";
    radio.read(&msg, sizeof(msg));
    String data = String(msg);   
    if (data.substring(0,5) == uid){ // if it's for me
      String recvCmd = data.substring(6,9);
      if(recvCmd == "POW"){ // what to do
        int state = data.substring(10,11).toInt();
        sendIRPowerCmd(state);
      }
      else if(recvCmd == "MUT"){
        sendIRCmd(MUTE_CMD, 1, 0);
      }
      else if(recvCmd == "SO+"){
        int presses = data.substring(10,12).toInt();
        sendIRCmd(SOUND_UP_CMD, presses, 200);
      }
      else if(recvCmd == "SO-"){
        int presses = data.substring(10,12).toInt();
        sendIRCmd(SOUND_DOWN_CMD, presses, 200);
      }
      else{
        // treat other msg types
      }
    }
    
  }
  else{}
  delay(100);
}
