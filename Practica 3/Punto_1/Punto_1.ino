// Declaramos las variables
#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 3 
#define BUTTON_PIN_3 9
#define BUTTON_PIN_4 10
int bandera_b1;
int cancion = 0;
volatile int volumen = 5;
volatile int num_ale;
int temporizador = 0;
unsigned long T_ant = 0;
int periodo = 1500;
volatile int counter = 0;

void setup() 
{
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP); 
  randomSeed(analogRead(0));
  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_1), incrementCounter, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_2), resetCounter, FALLING);
}

void loop() 
{
  temporizador = temporizador +1;
  delay(500);
  Serial.println(temporizador);
  Serial.println("Tiempo de canción");
  if (temporizador>29) {
    cancion = cancion +1;
    Serial.println("CANCIÓN #");
     Serial.println(cancion);
      temporizador = 0;
  }
  bandera_b1 = digitalRead(BUTTON_PIN_3);
  if (bandera_b1 == HIGH){
    num_ale = random(0, 10);
  }
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
