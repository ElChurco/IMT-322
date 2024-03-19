#define PULSADOR1_PIN 2
#define PULSADOR2_PIN 3
#define LED_PIN 4

#define ANTIREBOTE 200
#define TIEMPOPULSACION 3000

int TD = 200;

int Contador = 0;
bool reinicioPulsado = false;

unsigned long tiempoEspera = 0;
unsigned long tiempoPulsado = 0;
unsigned long tiempoUltimaPulsacion = 0;

void setup() 
{
  pinMode(PULSADOR1_PIN, INPUT_PULLUP);
  pinMode(PULSADOR2_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PULSADOR1_PIN), incremento, FALLING);
  attachInterrupt(digitalPinToInterrupt(PULSADOR2_PIN), cambioDelay, FALLING);
  
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{

  Serial.println(Contador);
  digitalWrite(LED_PIN, HIGH);
  delay(TD);

  digitalWrite(LED_PIN, LOW);
  delay(TD);

  if (reinicioPulsado) 
  
  {
    Contador = 0;
    reinicioPulsado = false;
  }
}

void incremento()
{
  if (millis() - tiempoEspera > ANTIREBOTE)
  
  {
    unsigned long tiempoActual = millis();


    if (tiempoActual - tiempoUltimaPulsacion >= TIEMPOPULSACION) 
    {
      Contador = 0;
      Serial.println("Reiniciando contador");

    } 
    else 
    {
      Contador++;
    }
    tiempoUltimaPulsacion = tiempoActual;

  }

}

void cambioDelay()
{

  static unsigned long tiempoPulsacion2 = 0; // para almacenar el tiempo de inicio de la pulsación de PULSADOR2
  unsigned long tiempoActual = millis();

  if (digitalRead(PULSADOR2_PIN) == LOW) 
  {

    if (tiempoActual - tiempoPulsacion2 >= TIEMPOPULSACION) 

    {
      if (TD == 200)


      {
        TD = 800;

      } 
      else if (TD == 800) 

      {
        TD = 1500;
      } 
      else 
      {
        TD = 200;

      }

      tiempoPulsacion2 = tiempoActual;

    } 
    else 

    {
      Contador--;

    }

  } 
  else 

  {
    tiempoPulsacion2 = 0; 

  }


}
