
const int L1 = 8;
const int L2 = 9;
const int L3 = 10;
const int speed = 200;

void setup() {

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
}
void loop() {

  encenderApagar(L1);
  encenderApagar(L2);
  encenderApagar(L3);
}
void encenderApagar(int pin) {

  digitalWrite(pin, HIGH); 
  delay(speed);        

  digitalWrite(pin, LOW);
}
