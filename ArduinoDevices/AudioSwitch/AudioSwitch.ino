#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <printf.h>
RF24 radio(9,10);
const uint64_t pipes[2] = { 0x0c0c0c0c0c, 0x0606070606 };
String uid = "AudSw"; // unique id (5 char)


int relay1PIN = 2;
int relay2PIN = 3;
int led1PIN   = 4;
int led2PIN   = 5;
int currentRightChanel = 1;
int currentLeftChanel = 1;
int bluetoothPIN = 6;

void setChanel(int ri, int li){
  digitalWrite(led1PIN, LOW);
  digitalWrite(led2PIN, LOW);
  
  if(ri == 1){
    digitalWrite(relay1PIN, HIGH);
    digitalWrite(led1PIN, HIGH);
    Serial.println("Set right chanel to 1");
  }
  else{
    digitalWrite(relay1PIN, LOW);
    digitalWrite(led2PIN, HIGH);
    Serial.println("Set right chanel to 2");
  }

  if(li == 1){
    digitalWrite(relay2PIN, HIGH);
    digitalWrite(led1PIN, HIGH);
    Serial.println("Set left chanel to 1");
  }
  else{
    digitalWrite(relay2PIN, LOW);
    digitalWrite(led2PIN, HIGH);
    Serial.println("Set left chanel to 2");
  }
}

void switchBluetoothState(){
  digitalWrite(bluetoothPIN, HIGH);
  delay(3000);
  digitalWrite(bluetoothPIN, LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(relay1PIN, OUTPUT);
  pinMode(relay2PIN, OUTPUT);

  digitalWrite(relay1PIN, HIGH);
  digitalWrite(relay2PIN, HIGH);

  pinMode(led1PIN, OUTPUT);
  pinMode(led2PIN, OUTPUT);

  digitalWrite(led1PIN, HIGH);
  digitalWrite(led2PIN, LOW);

  pinMode(bluetoothPIN, OUTPUT);
  digitalWrite(bluetoothPIN, LOW);

  Serial.begin(115200);
  printf_begin();
  Serial.write("Setup\n");
  initRadio();
  Serial.write("Radio ready !\n");

  setChanel(1, 1);
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

void blinkLeds(){
  digitalWrite(led1PIN, LOW);
  digitalWrite(led2PIN, LOW);
  delay(100);
  digitalWrite(led1PIN, HIGH);
  digitalWrite(led2PIN, HIGH);
  delay(100);
  digitalWrite(led1PIN, LOW);
  digitalWrite(led2PIN, LOW);
  delay(100);
  digitalWrite(led1PIN, HIGH);
  digitalWrite(led2PIN, HIGH);
  delay(100);
  digitalWrite(led1PIN, LOW);
  digitalWrite(led2PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()){  
    //blinkLeds();
    char msg[32] = "";
    radio.read(&msg, sizeof(msg));
    String data = String(msg);    
    if (data.substring(0,5) == uid){ // if it's for me
      if(data.substring(6,9) == "SET"){ // what to do
        int ri = data.substring(10,11).toInt();
        int li = data.substring(11,12).toInt();
        setChanel(ri,li);
      }
      if(data.substring(6,9) == "SBT"){ // what to do
        switchBluetoothState();
      }
      else{
        // treat other msg types
      }
    }
    
  }
  else{}
  delay(100);
}

