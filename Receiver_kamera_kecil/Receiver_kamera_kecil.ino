#include <PWM.h> //gara2 ini pakein capacitor di motornya

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//ini data yg didapat dari radio
int gotData[6] = {1};

//ini setting jadi receiver
const int pinCE = 7;
const int pinCSN = 8;
//RF24 wirelessSPI(pinCE, pinCSN); 
RF24 radio(pinCE, pinCSN); 
//const uint64_t pAddress = 0xB00B1E5000LL; 
const byte pAddress[6] = "00001";

//ini variable untuk kecepatan motor
int enAtas = 9, enBawah = 10;

//ini variable untuk nyala matiin motor
int in1Atas = 2 , in2Atas = 3, in3Bawah =4 , in4Bawah = 5;

//ini data hasil output sistem
int onMotorAtas, onMotorBawah;

int potValue;

void setup() {
  // put your setup code here, to run once:

  //untuk naikin frequency pwm
  int32_t frequency = 5000;
  SetPinFrequency(enAtas, frequency);
  SetPinFrequency(enBawah, frequency);

  /*setup NRF24L01*/
  radio.begin(); 
  //wirelessSPI.setAutoAck(1);             
  //wirelessSPI.enableAckPayload();       
  //wirelessSPI.setRetries(5,15);       
  //wirelessSPI.openReadingPipe(1,pAddress);
  radio.openReadingPipe(0,pAddress);   
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();     
  //wirelessSPI.printDetails(); 

  Serial.begin(9600);

  //select all the motor control pins to output
  pinMode(enAtas, OUTPUT);
  pinMode(enBawah, OUTPUT);
  pinMode(in1Atas, OUTPUT);
  pinMode(in2Atas, OUTPUT);
  pinMode(in3Bawah, OUTPUT);
  pinMode(in4Bawah, OUTPUT);

  //turn off motor - Initial state
  digitalWrite(enAtas, LOW);
  digitalWrite(enBawah, LOW);
  digitalWrite(in1Atas, LOW);
  digitalWrite(in2Atas, LOW);
  digitalWrite(in3Bawah, LOW);
  digitalWrite(in4Bawah, LOW);
}

void tipeMotorAtas1(int data2, int data3) {
  if(data3 >= 10) {
    digitalWrite(in1Atas, HIGH);
    digitalWrite(in2Atas, LOW);
    analogWrite(enAtas, data2);
    //Serial.print("A");
  }
  else if(data3 <= -10) {
    digitalWrite(in1Atas, LOW);
    digitalWrite(in2Atas, HIGH);
    analogWrite(enAtas, data2);
    //Serial.print("B");
  }
  else {
    digitalWrite(in1Atas, LOW);
    digitalWrite(in2Atas, LOW);
    analogWrite(enAtas, LOW); Serial.print("DIEM");
  }
}

void tipeMotorAtas2(int data2, int data3) {
  if(data3 >= 10) {
    digitalWrite(in1Atas, LOW);
    digitalWrite(in2Atas, HIGH);
    analogWrite(enAtas, data2);
    //Serial.print("C");
  }
  else if(data3 <= -10) {
    digitalWrite(in1Atas, HIGH);
    digitalWrite(in2Atas, LOW);
    analogWrite(enAtas, data2);
    //Serial.print("D");
  }
  else {
    digitalWrite(in1Atas, LOW);
    digitalWrite(in2Atas, LOW);
    analogWrite(enAtas, LOW); Serial.print("DIEM");
  }
}

void tipeMotorBawah1(int data2, int data4) {
  if(data4 >= 10) {
    digitalWrite(in3Bawah, HIGH);
    digitalWrite(in4Bawah, LOW);
    analogWrite(enBawah, data2);
    //Serial.print("E");
  }
  else if(data4 <= -10) {
    digitalWrite(in3Bawah, LOW);
    digitalWrite(in4Bawah, HIGH);
    analogWrite(enBawah, data2);
    //Serial.print("F");
  }
  else {
    digitalWrite(in3Bawah, LOW);
    digitalWrite(in4Bawah, LOW);
    analogWrite(enBawah, LOW); Serial.print("DIEM");
  }
}

void tipeMotorBawah2(int data2, int data4) {
  if(data4 >= 10) {
    digitalWrite(in3Bawah, LOW);
    digitalWrite(in4Bawah, HIGH);
    analogWrite(enBawah, data2);
    //Serial.print("G");
  }
  else if(data4 <= -10) {
    digitalWrite(in3Bawah, HIGH);
    digitalWrite(in4Bawah, LOW);
    analogWrite(enBawah, data2);
    //Serial.print("H");
  }
  else {
    digitalWrite(in3Bawah, LOW);
    digitalWrite(in4Bawah, LOW);
    analogWrite(enBawah, LOW); Serial.print("DIEM");
  }
}

int turnMotorAtas(int data0, int data3, int data2) {
  if(data3 >= 10 && data0 == 1) {
    tipeMotorAtas1(data2, data3); //Serial.println(">=10 1");
    return 1;
  }
  if(data3 <= -10 && data0 == 1) {
    tipeMotorAtas1(data2, data3); //Serial.println("<=-10 1");
    return 1;
  }
  if(data3 >= 10 && data0 == 2) {
    tipeMotorAtas2(data2, data3); //Serial.println(">=10 2");
    return 2;
  }
  if(data3 <= -10 && data0 == 2) {
    tipeMotorAtas2(data2, data3); //Serial.println("<=-10 2");
    return 2;
  }
  return 0;
}

int turnMotorBawah(int data1, int data4, int data2) {
  if(data4 >= 10 && data1 == 1) {
    tipeMotorBawah1(data2, data4);
    return 1;
  }
  if(data4 <= -10 && data1 == 1) {
    tipeMotorBawah1(data2, data4);
    return 1;
  }
  if(data4 >= 10 && data1 == 2) {
    tipeMotorBawah2(data2, data4);
    return 2;
  }
  if(data4 <= -10 && data1 == 2) {
    tipeMotorBawah2(data2, data4);
    return 2;
  }
  return 0;
}


void displayOutput(int onMotorAtas, int onMotorBawah, int data3, int data4) {
  Serial.print("Output: ");
  if(data3 >= 10) {
    if(onMotorAtas == 1) Serial.print("atas muter kanan origin kanan  ");
    else if(onMotorAtas == 2) Serial.print("atas muter kanan origin kiri  ");
  }
  if(data3 <= -10) {
    if(onMotorAtas == 1) Serial.print("atas muter kiri origin kanan  ");
    else if(onMotorAtas == 2) Serial.print("atas muter kiri origin kiri  ");
  }
  if(data4 >= 10) {
    if(onMotorBawah == 1) Serial.print("bawah muter CW origin CW  ");
    else if(onMotorBawah == 2) Serial.print("bawah muter CW origin CCW  ");
  }
  if(data4 <= -10) {
    if(onMotorBawah == 1) Serial.print("bawah muter CCW origin CW  ");
    else if(onMotorBawah == 2) Serial.print("bawah muter CCW origin CCW  ");
  }
  if(onMotorAtas == 0) {
    digitalWrite(in1Atas, LOW);
    digitalWrite(in2Atas, LOW);
    analogWrite(enAtas, LOW); Serial.print("WAT");
  }
  if(onMotorBawah == 0) {
    digitalWrite(in3Bawah, LOW);
    digitalWrite(in4Bawah, LOW);
    analogWrite(enBawah, LOW); Serial.print("HE");
  }
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:

  //ini buat nerima data dari NRF
   if(radio.available()){
    radio.read( &gotData, sizeof(gotData) );
    //Serial.print("Recieved data:");
    //Serial.println("");
    for (byte i=0; i<5; i++){
      //Serial.println(gotData[i]);
    }
    //Serial.println();
   }
    
   onMotorAtas = turnMotorAtas(gotData[0], gotData[3], gotData[2]);
   onMotorBawah = turnMotorBawah(gotData[1], gotData[4], gotData[2]);
   //Serial.print(onMotorAtas);
   //Serial.print(onMotorBawah);
   displayOutput(onMotorAtas, onMotorBawah, gotData[3], gotData[4]);

   
}
