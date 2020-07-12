/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int pinCE = 7;
const int pinCSN = 8;

RF24 radio(pinCE, pinCSN);
//const uint64_t pAddress = 0xB00B1E5000LL;       
const byte pAddress[6] = "00001";

//ini variable untuk 2 tombol dan potentio
int button1 = 2, button2 = 4;
int pot = A2, potValue, potValue2;

//ini variable untuk joystick
#define joyX A1
#define joyY A0
int xValue,yValue,xValue2,yValue2;

//ini variable output
int buttonOutput, potOutput, YaxisOut, XaxisOut;

//ini data yg bakal dikirim
int Data[10];

//ini fungsi buat mengetahui input yang dimasukkan
int buttonInput(int button1, int button2) {
  if(digitalRead(button1) == HIGH) {
    return 1;
    //Serial.write("1");
  }
  else if(digitalRead(button2) == HIGH) {
    return 2;
    //Serial.write("2");
  }
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
  xValue2 = map(xValue, 0,1023,127.5 ,-127.5);
  if(xValue2 >= 5 || xValue2 <= -5) return 1;
  return 0;
}

void sendData(int buttonInput, int potInput, int Yaxis, int Xaxis) {
  if(buttonInput == 1) {
    //Data[0] = "1";
    //Serial.print("1");
    //Button = "1";
    //Data *= 10 ;
    //int data = 1;
    //radio.write(&data, sizeof(data));
    Data[0] = 1;
  }
  else if(buttonInput == 2) {
    //Data[1] = "2";
    //Serial.print("2");
    //Button = "2";
    //Data *= 100;
    //int data = 2;
    //radio.write(&data, sizeof(data));
    Data[0] = 2;
  }
  else {
    //Data[1] = "0";
    //Serial.print("0");
    //Button = "0";
    //Data = Data;
    Data[0] = 0;
  }
  if(potInput == 1) {
    //char Buffer[3];
    //Data[2] = itoa(potValue2,Buffer,10);
    //Data[2] = "S";
    //Serial.print("pot");
    //Pot = "100";
    //Data += potValue2;
    //int data = potValue2;
    //radio.write(&data, sizeof(data));
    Data[1] = potValue2;
  }
  else {
    //Data[2] = "0";
    //Serial.print("0");
    //Pot = "0";
    //Data = Data;
    Data[1] = 0;
  }
  
  if(Yaxis == 1) {
    //char Buffer[3];
    //Data[3] = itoa(yValue2,Buffer,10);
    //Data[3] = "Y";
    //Serial.print("Yaxis");
    //YAxis = "200";
    //int data = yValue2;
    //radio.write(&data, sizeof(data));
    Data[2] = yValue2;
  }
  else {
    //Data[3] = "0";
    //Serial.print("0");
    //YAxis = "0";
    Data[2] = 0;
  }
  
  if(Xaxis == 1) {
    //char Buffer[3];
    //Data[4] = itoa(xValue2,Buffer,10);
    //Data[4] = "M";
    //Serial.print("Xaxis");
   // XAxis = "50";
    //int data = xValue2;
    //radio.write(&data, sizeof(data));
    Data[3] = xValue2;
  }
  else {
    //Data[4] = "0";
    //Serial.print("0");
    //XAxis = "0";
    Data[3] = 0;
  }
  //realData = Button + Pot + YAxis + XAxis;
  //Serial.write() gabisa di-increment kek Serial.print(); 
  //karna berupa bytes, klo increment Serial.write() 
  //hasilnya malah bytes nya nambah/ngurang.

  //Serial.write() dibawah ini berguna untuk nge-append bytes
  //kalo nge-append string gampang, tinggal StringA + StringB +..
  //return (Data[0] + Data[1] + Data[2] + Data[3] + Data[4]);
  //realData = Data[3] /*+ Data[1] + Data[2] + Data[3] + Data[4]*/;
  //delay(500);
  //ttn.sendBytes(Data, sizeof(Data));
  //Wire.write((Data[0]<<4) + (Data[1]<<4) + (Data[2]<<4) + (Data[3]<<4) + Data[4]);
}


void setup() {
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
  Serial.begin(9600);
}
void loop() {

  buttonOutput = buttonInput(button1, button2);
  potOutput = potInput(potValue);
  YaxisOut = Yaxis(yValue);
  XaxisOut = Xaxis(xValue);
  sendData(buttonOutput, potOutput, YaxisOut, XaxisOut);


   
  Serial.println("Now sending data... ");
   
  if (!radio.write( &Data, sizeof(Data))) {
      Serial.println("delivery failed");
      Serial.println();     
  }
  else {
      Serial.println("Send successful.");
      Serial.println();
  }
  //Serial.println(realData);
 // Serial.println("Hello");

 /*
 char text2[3];
 text2[0] = "M";
 char text3 = text2;
 //const char text2[] = "Hello";
 int num = 3;
  int text = num; 
  //radio.write(&text, sizeof(text));
   //radio.write(&text, sizeof(text));
   radio.write(&text2, sizeof(text2));
   Serial.println(text);
*/

  /*BUAT KIRIM CHAR
   * char text2[] = "M";
   * radio.write(&text2, sizeof(text2));
   */
   
  /*BUAT KIRIM STRING
   const char text = "HELLO WORLD";
   radio.write(&text, sizeof(text));
   */
   
  /*BUAT KIRIM INTEGER
  int num = 3;
  int text = num; 
  radio.write(&text, sizeof(text));
  */

  /*
  //radio.write(realData, sizeof(realData));
  //delay(1000);
  Data = 1;
  */
}
