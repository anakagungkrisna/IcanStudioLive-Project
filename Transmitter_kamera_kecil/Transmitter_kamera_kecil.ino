//#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int pinCE = 7;
const int pinCSN = 8;

RF24 radio(pinCE, pinCSN);
//const uint64_t pAddress = 0xB00B1E5000LL;       
const byte pAddress[6] = "00002";

//ini variable untuk 2 tombol dan potentio
int button1 = 2, button2 = 4;
int pot = A2, potValue, potValue2;

//ini variable untuk joystick
#define joyX A1
#define joyY A0
int xValue,yValue,xValue2,yValue2;

//ini variable untuk tau rising edge tombol kiri
int buttonStateRising1= 0;
int buttonRisingEdge1 = 0;       
int lastButtonStateRising1 = 0; 

//ini variable untuk tau rising edge tombol kanan
int buttonStateRising2= 0;
int buttonRisingEdge2 = 0;       
int lastButtonStateRising2 = 0;   

//ini variable output
int risingKiri, risingKanan, potOutput, YaxisOut, XaxisOut;

//ini data yg bakal dikirim
int Data[10];

//ini fungsi buat mengetahui kondisi low ke high button kiri
int buttonKiri(int button1) {
  //Here starts the code for detecting a rising edge on pin 11
   buttonStateRising1 = digitalRead(button1);
   if (buttonStateRising1 != lastButtonStateRising1) {
     if (buttonStateRising1 == HIGH) {
          buttonRisingEdge1 += 1;
          Serial.println("There was a rising edge on left button");
      }
   }
   else{
          //buttonRisingEdge = 0;
          //Serial.println("There was no rising edge on left button");
   }   
   lastButtonStateRising1 = buttonStateRising1; 

   if(buttonRisingEdge1%2 != 0) return 1;
   return 0;
}


//ini fungsi buat mengetahui kondisi low ke high button kanan
int buttonKanan(int button2) {
  //Here starts the code for detecting a rising edge on pin 11
   buttonStateRising2 = digitalRead(button2);
   if (buttonStateRising2 != lastButtonStateRising2) {
     if (buttonStateRising2 == HIGH) {
          buttonRisingEdge2 += 1;
          Serial.println("There was a rising edge on left button");
      }
   }
   else{
          //buttonRisingEdge = 0;
          //Serial.println("There was no rising edge on left button");
   }   
   lastButtonStateRising2 = buttonStateRising2; 

   if(buttonRisingEdge2%2 != 0) return 1;
   return 0;
}

int potInput(int potValue ) {
  potValue = analogRead(pot);
  potValue2 = map(potValue, 0,1023,0,255);
  if(potValue2 >= 5 || potValue2 <= -5) return 1;
  return 0;
}

int Yaxis(int yValue) {
  yValue = analogRead(joyY);
  yValue2 = map(yValue, 0,1023,-127.5,127.5);
  //Serial.println(yValue2);
  if(yValue2 >= 5 || yValue2 <= -5) return 1;
  return 0;
}

int Xaxis(int xValue) {
  xValue = analogRead(joyX);
  //Serial.println(xValue);
  //delay(500);
  xValue2 = map(xValue, 0,1023,127.5 ,-127.5);
  if(xValue2 >= 5 || xValue2 <= -5) return 1;
  return 0;
}

void sendData( int buttonKiri, int buttonKanan, int potInput, int Yaxis, int Xaxis) {
  if(buttonKiri == 1) {
    Data[0] = 1;
    digitalWrite(3, HIGH);
  }
  else if(buttonKiri == 0) {
    Data[0] = 2;
    digitalWrite(3, LOW);
  }
  if(buttonKanan == 1) {
    Data[1] = 1;
    digitalWrite(5, HIGH);
  }
  else if(buttonKanan == 0) {
    Data[1] = 2;
    digitalWrite(5, LOW);
  }
  if(potInput == 1) Data[2] = potValue2;
  else if(potInput == 0) Data[2] = 0;
  if(Yaxis == 1) Data[3] = yValue2;
  else if(Yaxis == 0) Data[3] = 0;
  if(Xaxis == 1) Data[4] = xValue2;
  else if(Xaxis == 0) Data[4] = 0;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(pot, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  risingKiri = buttonKiri(button1);
  risingKanan = buttonKanan(button2);
  potOutput = potInput(potValue);
  YaxisOut = Yaxis(yValue);
  XaxisOut = Xaxis(xValue);
  sendData(risingKiri, risingKanan, potOutput, YaxisOut, XaxisOut);
  

  Serial.println("Now sending data... ");
   
  if (!radio.write( &Data, sizeof(Data))) {
      Serial.println("delivery failed");
      Serial.println();     
  }
  else {
      Serial.println("Send successful.");
      Serial.println();
      
  }
/*  
  if(risingKiri == 1) digitalWrite(3, HIGH);
  else if(risingKiri == 0) digitalWrite(3, LOW);

  if(risingKanan == 1) digitalWrite(5, HIGH);
  else if(risingKanan == 0) digitalWrite(5, LOW);
  
  //if(digitalRead(button1) == HIGH) digitalWrite(3, HIGH);
  //else digitalWrite(3, LOW);
*/
}
