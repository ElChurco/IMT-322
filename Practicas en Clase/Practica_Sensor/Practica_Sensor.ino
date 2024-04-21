#define pinTrigger 4
#define pinEcho 3
#define pinBoton 2

volatile bool botonPresionado = false;

typedef enum{
  ESPERA,
  SENSADO
}sensado;
sensado FSM = ESPERA;


void setup() 
{
    pinMode(pinTrigger, OUTPUT);
    pinMode(pinEcho, INPUT);
    pinMode(pinBoton, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(pinBoton), manejarBoton, FALLING);
    Serial.begin(9600);
}

void loop()
{
  switch(FSM) {
    case ESPERA:
      if (botonPresionado) {
          // si el botón fue presionado pasamos al siguiente estado
          FSM = SENSADO;
          botonPresionado = false;
      }
      break;
    case SENSADO:
        //estado de lectura del sensor ultrasónico durante 5 segundos
        unsigned long inicio = millis();
        while (millis() - inicio < 2500) {
            float distancia = medirDistancia();

            Serial.print("Distancia: ");
            Serial.print(distancia);

            Serial.println(" cm");

            // pausamos brevemente para evitar enviar muchas lecturas
            delay(100);
        }

        FSM = ESPERA;
        break;
    }
}

//función de interrupción para manejar el botón
void manejarBoton()
{
    //cambiamos la bandera para indicar que el botón fue presionado
    botonPresionado = true;
}

//medimos distancia sensor
float medirDistancia() 
{
    digitalWrite(pinTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrigger, LOW);

    //leemos el tiempo de retorno del pulso echo
    long duracion = pulseIn(pinEcho, HIGH);

    // Calculamos distancia en cm (sonido viaja 340 m/s, o 0.034 cm/us)
    float distancia = duracion * 0.034 / 2;

    return distancia;
}
