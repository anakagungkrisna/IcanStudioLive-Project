#include <SPI.h>
#include "RF24.h"
#include <PWM.h>

RF24 myRadio (7, 8);

struct package {
  int msg;
};
typedef struct package Package;
Package data[10];

byte addresses [] [6] = {"0"};

int dataIn;
//ini variable untuk kecepatan motor
int enAtas = 9, enBawah = 10;

//ini variable untuk nyala matiin motor
int in1Atas = 2 , in2Atas = 3, in3Bawah =4 , in4Bawah = 5;

//ini data hasil output sistem
int onMotorAtas, onMotorBawah;

int potValue;



void setup() {

  int32_t frequency = 5000;
  SetPinFrequency(enAtas, frequency);
  SetPinFrequency(enBawah, frequency);
  
  // put your setup code here, to run once:
  Serial.begin (9600);
  myRadio.begin ();
  myRadio.setChannel (115); // 115 band above WIFI signals
  myRadio.setPALevel (RF24_PA_MIN); // MIN power low rage
  myRadio.setDataRate (RF24_250KBPS); // Minimum speed
  Serial.print ("Setup Initialized");
  delay (500);

  pinMode(enAtas, OUTPUT);
  pinMode(enBawah, OUTPUT);
  pinMode(in1Atas, OUTPUT);
  pinMode(in2Atas, OUTPUT);
  pinMode(in3Bawah, OUTPUT);
  pinMode(in4Bawah, OUTPUT);

  digitalWrite(enAtas, LOW);
  digitalWrite(enBawah, LOW);
  digitalWrite(in1Atas, LOW);
  digitalWrite(in2Atas, LOW);
  digitalWrite(in3Bawah, LOW);
  digitalWrite(in4Bawah, LOW);
}


//////////////////fungsi olah input//////////////////
void tipeMotorAtas(int data0, int data2, int data3) {
  if(data0 == 0) {
    if(data3 >= 10) {
      digitalWrite(in1Atas, HIGH);
      digitalWrite(in2Atas, LOW);
      analogWrite(enAtas, data2);
      Serial.print(" A");
    }
    else if(data3 <= -10) {
      digitalWrite(in1Atas, LOW);
      digitalWrite(in2Atas, HIGH);
      analogWrite(enAtas, data2);
      Serial.print(" B");
    }
    else {
      digitalWrite(in1Atas, LOW);
      digitalWrite(in2Atas, LOW);
      analogWrite(enAtas, LOW); Serial.print(" atas DIEM");
    }
  }
  if(data0 == 1) {
    if(data3 >= 10) {
      digitalWrite(in1Atas, LOW);
      digitalWrite(in2Atas, HIGH);
      analogWrite(enAtas, data2);
      Serial.print(" C");
    }
    else if(data3 <= -10) {
      digitalWrite(in1Atas, HIGH);
      digitalWrite(in2Atas, LOW);
      analogWrite(enAtas, data2);
      Serial.print(" D");
    }
    else {
      digitalWrite(in1Atas, LOW);
      digitalWrite(in2Atas, LOW);
      analogWrite(enAtas, LOW); Serial.println(" atas DIEM");
    }
  }
}

void tipeMotorBawah(int data1, int data2, int data4) {
  if(data1 == 0) {
    if(data4 >= 10) {
      digitalWrite(in3Bawah, HIGH);
      digitalWrite(in4Bawah, LOW);
      analogWrite(enBawah, data2);
      Serial.print(" E");
    }
    else if(data4 <= -10) {
      digitalWrite(in3Bawah, LOW);
      digitalWrite(in4Bawah, HIGH);
      analogWrite(enBawah, data2);
      Serial.print(" F");
    }
    else {
      digitalWrite(in3Bawah, LOW);
      digitalWrite(in4Bawah, LOW);
      analogWrite(enBawah, LOW); Serial.println(" bawah DIEM");
    }
  }
  if(data1 == 1) {
    if(data4 >= 10) {
      digitalWrite(in3Bawah, LOW);
      digitalWrite(in4Bawah, HIGH);
      analogWrite(enBawah, data2);
      Serial.print(" G");
    }
    else if(data4 <= -10) {
      digitalWrite(in3Bawah, HIGH);
      digitalWrite(in4Bawah, LOW);
      analogWrite(enBawah, data2);
      Serial.print(" H");
    }
    else {
      digitalWrite(in3Bawah, LOW);
      digitalWrite(in4Bawah, LOW);
      analogWrite(enBawah, LOW); Serial.println(" bawah DIEM");
    }
  }
}

/*
void tipeMotorAtas1(int data2, int data3) {
  if(data3 >= 10) {
    digitalWrite(in1Atas, HIGH);
    digitalWrite(in2Atas, LOW);
    analogWrite(enAtas, data2);
    Serial.print("A");
  }
  else if(data3 <= -10) {
    digitalWrite(in1Atas, LOW);
    digitalWrite(in2Atas, HIGH);
    analogWrite(enAtas, data2);
    Serial.print("B");
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
*/

/////////////////////////////////////////////////////

int ReadData () {
  myRadio.openReadingPipe (1, 0xF0F0F0F0AA); // Which pipe to read, 40 bit address
  myRadio.startListening (); // Stop Transminting and start Reveicing
  if (myRadio.available ()) {
    while (myRadio.available ()) {
      myRadio.read (& data, sizeof (data));
    }
    for (byte i=0; i<9; i++){
      //Serial.println(data[i].msg);
    }
  //Serial.print ("\ nReceived:");
  //Serial.println (data.msg);
    Serial.println();
    return 1;
  }
  return 0;
}


void loop() {
  // put your main code here, to run repeatedly:
  dataIn = ReadData ();
  Serial.println(dataIn);

    if(dataIn == 1) {
      // = turnMotorAtas(data[0].msg, data[3].msg, data[2].msg);
      //onMotorBawah = turnMotorBawah(data[1].msg, data[4].msg, data[2].msg);
      //Serial.print(onMotorAtas);
      //Serial.print(onMotorBawah);
      //displayOutput(onMotorAtas, onMotorBawah, data[3].msg, data[4].msg);
      //tipeMotorAtas1(data[2].msg,data[3].msg);
      tipeMotorAtas(data[0].msg, data[2].msg, data[3].msg);
      tipeMotorBawah(data[1].msg, data[2].msg, data[4].msg);

    }
   
  if(dataIn == 0) {
    digitalWrite(in1Atas, LOW);
    digitalWrite(in2Atas, LOW);
    analogWrite(enAtas, LOW); //Serial.print("WAT");
    
    digitalWrite(in3Bawah, LOW);
    digitalWrite(in4Bawah, LOW);
    analogWrite(enBawah, LOW); //Serial.print("HE");
  } 
  delay(50);
}
