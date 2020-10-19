#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <printf.h>
RF24 radio(9,10);
const uint64_t pipes[2] = { 0x0c0c0c0c0c, 0x0606070606 };
String uid = "GuiNo"; // unique id (5 char)

bool isOn = true;
int patern = 1;
int state = 0;
int timeFrame = 0;
float speedRatio = 1.0;

unsigned long d = 0;
unsigned int t = 250;

int ledPins[8] = {2, 4, 3, 5, A5, A4, A3, A2};
bool isLedOn[16];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  printf_begin();
  initRadio(); 
  initPins();
}

void initPins(){
  for(int i = 0 ; i < 8 ; i++){
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], ((i<4)?LOW:HIGH));
  }

  for(int i = 0 ; i < 16 ; i++){
    isLedOn[i] = false;
  }
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

void patern1(){
  if(timeFrame % (int)(20 / speedRatio) == 0){ // 20 * 10ms = 200ms
    //Serial.println(state);
    int lastState = (state > 0)?state-1:15;
    isLedOn[lastState] = false;
    isLedOn[state] = true;
    
    state++;
    if(state == 16) state = 0;
  }
}

void patern2(){
  if(timeFrame % (int)(33 / speedRatio) == 0){ // 33 * 10ms = 330ms
    //Serial.println(state);
    for(int i = 0 ; i < 16 ; i++){
      isLedOn[i] = i%4 == state;
    }
    
    state++;
    if(state == 4) state = 0;
  }
}

void patern3(){
  if(timeFrame % (int)(50 / speedRatio) == 0){ // 50 * 10ms = 500ms
    //Serial.println(state);
    for(int i = 0 ; i < 16 ; i++){
      isLedOn[i] = random(4) == 0;;
    }
  }
}

void patern4(){
  if(timeFrame % (int)(5 / speedRatio) == 0){ // 50 * 10ms = 500ms
    int pos = random(16);
    //Serial.println(state);
    for(int i = 0 ; i < 16 ; i++){
      isLedOn[i] = i == pos;
    }
  }
}

void patern5(){
  if(timeFrame % (int)(10 / speedRatio) == 0){ // 20 * 10ms = 200ms
    //Serial.println(state);
    isLedOn[state % 16] = state < 16;
    
    state++;
    if(state == 32) state = 0;
  }
}

void patern6(){
  if(timeFrame % (int)(10 / speedRatio) == 0){ // 20 * 10ms = 200ms
    //Serial.println(state);
    isLedOn[(state % 4 * 4) + (int)((state % 16) / 4)] = state < 16;
    
    state++;
    if(state == 32) state = 0;
  }
}

void displayLeds(){
  for(int i = 0 ; i < 4 ; i++){
    digitalWrite(ledPins[i+4], HIGH); // OFF
    for(int j = 0 ; j < 4 ; j++){
      digitalWrite(ledPins[j], isLedOn[j*4+i]?HIGH:LOW);
    }
    digitalWrite(ledPins[i+4], LOW); // ON
    delayMicroseconds(t);
    //delay(500);
    digitalWrite(ledPins[i+4], HIGH); // OFF
    //delayMicroseconds(d);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()){  
    char msg[32] = "";
    radio.read(&msg, sizeof(msg));
    String data = String(msg);    
    if (data.substring(0,5) == uid){ // if it's for me
      String cmd = data.substring(6,9);
      if(cmd == "POW"){ // what to do
        int _state = data.substring(10,11).toInt();
        isOn = _state == 1;
      }
      else if (cmd == "PAT"){
        int _patern = data.substring(10,11).toInt();
        patern = _patern;
        state = 0;
        timeFrame = 0;
      }
      else if (cmd == "SPD"){
        float _speed = data.substring(10,13).toFloat();
        if(_speed >= 0.1 && _speed <= 5.0) speedRatio = _speed;
      }
      else{
        
      }
    }
  }
  else{}

  if (Serial.available() > 0) {
    String msg = Serial.readString();
    int pin = msg.substring(0,1).toInt();
    int s = msg.substring(1,2).toInt();
    digitalWrite(ledPins[pin], s);
    Serial.println("set " + String(pin) + " to " + String(s));
  }

  if(patern == 1)patern1();
  else if(patern == 2)patern2();
  else if(patern == 3)patern3();
  else if(patern == 4)patern4();
  else if(patern == 5)patern5();
  else if(patern == 6)patern6();
  else patern1();

  if(isOn){
    //Serial.println(isLedOn[0]);
    for(int i = 0 ; i < 10 ; i++){ // 100 * 100ns =  10ms
      displayLeds();// 1 iter is 4 * d ns \\current 100ns
    }
    debugLedStates();
  }

  timeFrame++;
  //delay(10);
}

void debugLedStates(){
  for(int i = 0 ; i < 16 ; i++){
    Serial.print(isLedOn[i]);
  }
  Serial.println();
}

