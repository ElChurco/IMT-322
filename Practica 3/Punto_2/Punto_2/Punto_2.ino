#define BOTON_PIN 2
#define BOTON1_PIN 3
#define LED_PIN LED_BUILTIN

int cont = 0;
int cont2 = 500;
int periodo = 100;
bool t = false;

unsigned long tiempoAnterior = 0;

void setup() 
{
  pinMode(BOTON_PIN, INPUT_PULLUP);
  pinMode(BOTON1_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(BOTON_PIN), Incremento, FALLING);
  attachInterrupt(digitalPinToInterrupt(BOTON1_PIN), Reinicio, FALLING);

}

void loop()

 {
  
  digitalWrite(LED_PIN, HIGH);
  delay(cont2);
  digitalWrite(LED_PIN, LOW);

  delay(cont2);
  Serial.println(cont);
  delay(500);
}

void Incremento() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior > periodo) 
  {
    cont = cont + 1;
    Serial.println(tiempoActual - tiempoAnterior);

    tiempoAnterior = tiempoActual;

  }
}

void Reinicio() 
{
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior > periodo) 
  {
    cont = 0;
    EstadoLed();

    tiempoAnterior=tiempoActual;
  }

}

void EstadoLed() 
{

  if (cont2 ==1500) 
  {  
    cont2 =500;

    t = true;
  }
  if (cont2== 1000) 

  {    
    cont2= 1500; 

  }
  if (cont2== 500 && t== false) 
  {  

    cont2 = 1000; 
  }

  t = false;
}
