#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> 
#endif

#define Neo1        9 
#define Neo2        10
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24

Adafruit_NeoPixel pixel1(NUMPIXELS, Neo1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel2(NUMPIXELS, Neo2, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 1 // Time (in milliseconds) to pause between pixels

int R = 10,G = 10,B = 10;
char RGB = 'R';
int i = 0;


#include <SPI.h>
#include "RF24.h"
RF24 myRadio (7, 8);

struct package {
  int msg[10] = {0};
};

byte addresses [] [6] = {"0"};

typedef struct package Package;
  Package data;

//input dari push button
#define btnKanan 2
#define btnKiri 4
int btnKananValue, btnKiriValue;

//ini variable untuk tau rising edge tombol kiri
int buttonStateRising1= 0;
int buttonRisingEdge1 = 0;       
int lastButtonStateRising1 = 0; 

//ini variable untuk tau rising edge tombol kanan
int buttonStateRising2= 0;
int buttonRisingEdge2 = 0;       
int lastButtonStateRising2 = 0;  

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


void WriteData () {
  myRadio.stopListening (); // Stop Receiving and start transminitng
  myRadio.openWritingPipe (0xF0F0F0F0AA); // Sends data on this 40-bit address
  myRadio.write (& data, sizeof (data));
  Serial.print ("\ nSent:");
  Serial.print (data.msg[0]);
  Serial.print (" ");
  Serial.print (data.msg[1]);
  Serial.print (" ");
  Serial.print (data.msg[2]);
  Serial.print (" ");
  Serial.print (data.msg[3]);
  Serial.print (" ");
  Serial.println(data.msg[4]);
  
  //delay (300);
}

void setup() {
  // put your setup code here, to run once:

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  pixel1.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixel2.begin();

  pinMode(6, OUTPUT);
  analogWrite(6, 85);
  pinMode(3, OUTPUT); //output led button
  pinMode(5, OUTPUT); //output led button
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  Serial.begin (9600);
  myRadio.begin ();
  myRadio.setChannel (115); // 115 band above WIFI signals
  myRadio.setPALevel (RF24_PA_MIN); // MIN power low rage
  myRadio.setDataRate (RF24_250KBPS); // Minimum speed
  delay (500);
  Serial.print ("Setup Initialized");

  pinMode(btnKanan, INPUT);
  pinMode(btnKiri, INPUT); //KENAPA KALO INI DIPAKE JADI GAJALAN!?

}

void loop() {
  // put your main code here, to run repeatedly:

//////////////////////buat neopixel///////////////////
    if(i<=NUMPIXELS) { 
    pixel1.setPixelColor(i, pixel1.Color(R, G, B));
    pixel1.show();   // Send the updated pixel colors to the hardware.
    pixel2.setPixelColor(i, pixel2.Color(R, G, B));
    pixel2.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop
    if (RGB == 'R') {
      R += 10 ;
    }
    else if (RGB == 'G'){
      G += 10;
    }
    else if (RGB == 'B'){
      B += 10;
    }
    i++;
  }
  else {
    //pixel1.clear();
    //pixel2.clear();
    Serial.print(R);
    if (R == 260){
      RGB = 'G';
    }
    else if (G == 260){
      RGB = 'B';
    }
    else {
      RGB = 'R';
    }
    R = 10;
    G = 10;
    B = 10;
    i = 0;
  }
 /////////////////////////////////////////////////
  
///////////////////////buat input////////////////
  btnKananValue = buttonKanan(btnKanan);
  btnKiriValue = buttonKiri(btnKiri);

  if(btnKananValue == 1) analogWrite(3, HIGH);
  else analogWrite(3, LOW);
  if(btnKiriValue == 1) analogWrite(5, HIGH);
  else analogWrite(5, LOW);

  int Read_ADC = analogRead (A0); //sumbu x
  int Read_ADC2 = analogRead (A1); //sumbu y
  int Read_ADC3 = analogRead (A2); //potentio
  int motor_atas = map (Read_ADC, 0, 1023, -127, 127);
  int motor_bawah = map (Read_ADC2, 0, 1023, -127,127);
  int potValue = map(Read_ADC3, 0, 1023, 0, 255);
///////////////////////////////////////////////////////

////////////////////buat kirim input/////////////////
    //Data
  data.msg[0] = btnKiriValue;
  data.msg[1] = btnKananValue;
  data.msg[2] = potValue;
  data.msg[3] = motor_bawah;
  data.msg[4] = motor_atas;
  data.msg[5] = 0;
  data.msg[6] = 0;
  data.msg[7] = 0;
  data.msg[8] = 0;
  WriteData ();
  delay (50);
//////////////////////////////////////////////////  
}
