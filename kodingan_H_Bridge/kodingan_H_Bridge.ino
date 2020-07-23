int R4 = 4, R3 = 3, R2 = 2, R1 = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(R4, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R1, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);
  Serial.println("Forward");
  delay(3000);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);
  Serial.print("Reverse");
  delay(3000);
}
