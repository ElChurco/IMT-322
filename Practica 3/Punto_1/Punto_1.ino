#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 3 
unsigned long T_ant = 0;
int periodo = 1500;
volatile int counter = 0;

void setup() 
{
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP); 
  
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_1), incrementCounter, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_2), resetCounter, FALLING);
}

void loop() {
  Serial.println(counter);
  delay(500); // Periodo de espera para evitar lecturas rápidas de los botones
}

void incrementCounter() 
{
  unsigned long T_act = millis();
  if (T_act - T_ant > periodo){
    counter = counter + 1;
    T_ant = millis();
  }
}

void resetCounter()
 {
  counter = 0;
}
