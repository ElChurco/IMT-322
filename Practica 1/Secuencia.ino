const int BOTON = 2;
int cont = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BOTON, INPUT_PULLUP);
  
  Serial.begin(9500); 
  attachInterrupt(digitalPinToInterrupt(BOTON), Incremento, FALLING);
}

void loop() 
{
  Serial.println(cont);
  parpadeoLED();

}

void Incremento() {
  cont++;
}

void parpadeoLED()
 {

  digitalWrite(LED_BUILTIN, HIGH);
  delay(900);

  digitalWrite(LED_BUILTIN, LOW);
  delay(900);
}