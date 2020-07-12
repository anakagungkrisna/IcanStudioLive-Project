//ini define input joystick
#define joyX A1
#define joyY A0
int xValue,yValue,xValue2,yValue2;

//ini variabel untuk kontrol kecepatan motor
int enAkepala = 2,enBkepala = 2,enAbadan = 3,enBbadan = 3,enAkaki = 4;
int pot = A2,potValue,potValue2;


//ini define output joystick
int valueKepala,valueKepala2,valueBadan,valueBadan2;

//ini variabel untuk nyala matiin motor
int in1Kepala = 24,in2Kepala = 25,in3Kepala = 26,in4Kepala = 27;
int in1Badan = 32,in2Badan = 33,in3Badan = 34,in4Badan = 35;
int in1Kaki = 40,in2Kaki = 41;

//ini variabel untuk 2 tombol
int tombolKanan = 44, tombolKiri = 45;
int in1, in2;

//ini data hasil output sistem
int kepala, badan, kaki;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(pot, INPUT);
  pinMode(tombolKanan, INPUT);
  pinMode(tombolKiri, INPUT);
  pinMode(enAkaki, OUTPUT);

  //select all the motor control pins to output
  pinMode(in1Kepala, OUTPUT);
  pinMode(in2Kepala, OUTPUT);
  pinMode(in3Kepala, OUTPUT);
  pinMode(in4Kepala, OUTPUT);
  pinMode(in1Badan, OUTPUT);
  pinMode(in2Badan, OUTPUT);
  pinMode(in3Badan, OUTPUT);
  pinMode(in4Badan, OUTPUT);
  pinMode(in1Kaki, OUTPUT);
  pinMode(in2Kaki, OUTPUT);

  //turn off motor - Initial state
  digitalWrite(in1Kepala, LOW);
  digitalWrite(in2Kepala, LOW);
  digitalWrite(in3Kepala, LOW);
  digitalWrite(in4Kepala, LOW);
  digitalWrite(in1Badan, LOW);
  digitalWrite(in2Badan, LOW);
  digitalWrite(in3Badan, LOW);
  digitalWrite(in4Badan, LOW);
  digitalWrite(in1Kaki, LOW);
  digitalWrite(in2Kaki, LOW);


  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(potValue, OUTPUT);

}

int turnMotorKepala(int yValue2) {
  if(yValue2 >= 10 ) {
    digitalWrite(in1Kepala, HIGH);
    digitalWrite(in2Kepala, LOW);
    digitalWrite(in3Kepala, HIGH);
    digitalWrite(in4Kepala, LOW);
    analogWrite(enAkepala, yValue2);
    //analogWrite(enBkepala, yValue2);
    //Serial.print(yValue2);
    return 1;
  }
  else if(yValue2 <= -10) {
    digitalWrite(in1Kepala, LOW);
    digitalWrite(in2Kepala, HIGH);
    digitalWrite(in3Kepala, LOW);
    digitalWrite(in4Kepala, HIGH);
    analogWrite(enAkepala, yValue2*-1);
    //analogWrite(enBkepala, yValue2*-1);
    //Serial.print(yValue2*-1);
    return 2;
  }
  else {
    while (yValue2 >= 10) {
      analogWrite(enAkepala, yValue2);
      yValue2 -= 10;
      delay(50);
    }
    while (yValue2 <= -10) {
      analogWrite(enAkepala, yValue2);
      yValue2 += 10;
      delay(50);
    }

    digitalWrite(in1Kepala, LOW);
    digitalWrite(in2Kepala, LOW);
    digitalWrite(in3Kepala, LOW);
    digitalWrite(in4Kepala, LOW);
  }
  return 0;
  //Serial.println("motor diam");
}

int turnMotorBadan(int xValue2) {
    if(xValue2 >= 10 ) {
    digitalWrite(in1Badan, HIGH);
    digitalWrite(in2Badan, LOW);
    digitalWrite(in3Badan, HIGH);
    digitalWrite(in4Badan, LOW);
    analogWrite(enAbadan, xValue2);
    //analogWrite(enBbadan, xValue2);
    //Serial.print(xValue2);
    return 1;
  }
  else if(xValue2 <= -10) {
    digitalWrite(in1Badan, LOW);
    digitalWrite(in2Badan, HIGH);
    digitalWrite(in3Badan, LOW);
    digitalWrite(in4Badan, HIGH);
    analogWrite(enAbadan, xValue2*-1);
    //analogWrite(enBbadan, xValue2*-1);
    //Serial.print(xValue2*-1);
    return 2;
  }
  else {
    while (xValue2 >= 10) {
      analogWrite(enAbadan, xValue2);
      xValue2 -= 10;
      delay(50);
    }
    while (xValue2 <= -10) {
      analogWrite(enAbadan, xValue2);
      xValue2 += 10;
      delay(50);
    }

    digitalWrite(in1Badan, LOW);
    digitalWrite(in2Badan, LOW);
    digitalWrite(in3Badan, LOW);
    digitalWrite(in4Badan, LOW);
  }
  return 0;
}

int turnMotorKaki(int in1, int in2, int PWM) {
  if(digitalRead(in1) == HIGH && digitalRead(in2) == LOW) {
    digitalWrite(in1Kaki, HIGH);
    digitalWrite(in2Kaki, LOW);
    analogWrite(enAkaki, PWM);
    return 1;
  }
  else if(digitalRead(in1) == LOW && digitalRead(in2) == HIGH) {
    digitalWrite(in1Kaki, LOW);
    digitalWrite(in2Kaki, HIGH);
    analogWrite(enAkaki, PWM);
    return 2;
  }
  else { 
    while(PWM >= 10) {
        analogWrite(enAkaki, PWM);
        PWM -= 10;
        delay(50);
    }
 
    digitalWrite(in1Kaki, LOW);
    digitalWrite(in2Kaki, LOW);
    analogWrite(enAkaki, LOW);
  }
  return 0;
}

void displayOutput(int kepala, int badan, int kaki) {
  Serial.print("Output: ");
  if(kepala == 1) Serial.print("muter atas  ");
  if(kepala == 2) Serial.print("muter bawah  ");
  if(badan == 1) Serial.print("muter kanan  ");
  if(badan == 2) Serial.print("muter kiri  ");
  if(kaki == 1) Serial.print("ke kanan  ");
  if(kaki == 2) Serial.print("ke kiri  ");
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:

  //olah joystick input
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  yValue2 = map(yValue, 0,1023,-127.5,127.5);
  xValue2 = map(xValue, 0,1023,127.5 ,-127.5);

  //olah varistor input

  //int potValue3;
  
  //hasil output dari input joystick
  //yValue untuk kepala, xValue untuk badan

  
  kaki = turnMotorKaki(tombolKanan, tombolKiri, potValue2);
  if(digitalRead(tombolKanan) == HIGH || digitalRead(tombolKiri) == HIGH) {
    potValue = analogRead(pot);
    potValue2 = map(potValue, 0,1023,0,255);
  }

  else if(digitalRead(tombolKanan) == LOW && digitalRead(tombolKiri) == LOW) {
    potValue2 = 0;
  }
  
  kepala = turnMotorKepala(yValue2);
  badan = turnMotorBadan(xValue2);


  displayOutput(kepala, badan, kaki);
  /*
  analogWrite(LED_BUILTIN, value2);
  analogWrite(potValue, value2);
  Serial.println(value2);
  if(Serial.available()) {
    serial = Serial.read();
    if(serial == '1') {
      digitalWrite(52, HIGH);
      digitalWrite(53, LOW);
      Serial.print("right");
    }
    if(serial == '2') {
      digitalWrite(52, LOW);
      digitalWrite(53, HIGH);
      Serial.print("left");
    }
  }
  delay(100);
  */
  
}
