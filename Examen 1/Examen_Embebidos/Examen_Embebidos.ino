
#include <Adafruit_MCP4725.h>

const int botonSiguientePin = 2; 
const int botonAnteriorPin = 3; 
const int botonVolumenArribaPin = 4;
const int botonVolumenAbajoPin = 5;
const int botonPausaPin = 6;

unsigned long tiempoInicio = 0;
unsigned long duracionCancion = 30000;
int cancionActual = 0;
int volumen = 5; // volumen
bool aleatorio = false;
bool pausa = false;
bool pausaMostrada = false; // estado de pausa
unsigned long tiempoPausaMostrada = 0;

// control volumen
Adafruit_MCP4725 dac;

void siguienteCancion() {
  cancionActual++;
  if (cancionActual >= 10) 
  {

    cancionActual = 0;
  }
  tiempoInicio = millis();
}

void anteriorCancion() {
  cancionActual--;
  if (cancionActual < 0) 
  {
   
    cancionActual = 9;
  }
  tiempoInicio = millis();
}

void setup() {
  Serial.begin(9600);
  
  pinMode(botonSiguientePin, INPUT_PULLUP);
  pinMode(botonAnteriorPin, INPUT_PULLUP);
  pinMode(botonVolumenArribaPin, INPUT_PULLUP);

  pinMode(botonVolumenAbajoPin, INPUT_PULLUP);
  pinMode(botonPausaPin, INPUT_PULLUP);

  dac.begin(0x62);
  dac.setVoltage(volumen * 100,false);
  
  // temporizador
  tiempoInicio = millis();
}

void loop() 
{
  bool siguientePresionado = digitalRead(botonSiguientePin) == LOW;
  bool anteriorPresionado = digitalRead(botonAnteriorPin) == LOW;

  bool volumenArribaPresionado = digitalRead(botonVolumenArribaPin) == LOW;
  bool volumenAbajoPresionado = digitalRead(botonVolumenAbajoPin) == LOW;
  bool pausaPresionada = digitalRead(botonPausaPin) == LOW;

  if (siguientePresionado) {
    delay(50);

    if (digitalRead(botonSiguientePin) == LOW) 

    {
      // boton 3 segundos
      Serial.println("Siguiente canción");
      siguienteCancion();
    }
  }

  // cancion anterior
  if (anteriorPresionado) 
  {
    delay(50); // Debounce
    if (digitalRead(botonAnteriorPin) == LOW) 
    {
      // Boton 3 segundos

      Serial.println("Canción anterior");
      anteriorCancion();
    }
  }

  if (volumenArribaPresionado) {
    delay(50);
    
    if (digitalRead(botonVolumenArribaPin) == LOW) 

    {

      // Boton presionado
      if (volumen < 10) {
        volumen++;

        dac.setVoltage(volumen * 100, false);
        Serial.print("Volumen");
        Serial.println(volumen);
      }

    }
  }

  if (volumenAbajoPresionado)
  {
    delay(50);
    if (digitalRead(botonVolumenAbajoPin) == LOW) 
    {
      
      // boton presionado
      if (volumen > 0) {
        volumen--;

        dac.setVoltage(volumen * 100, false);
        Serial.print("Volumen: ");
        Serial.println(volumen);
      }
    }

  }

  if (pausaPresionada) 
  {
    delay(50);

    if (digitalRead(botonPausaPin) == LOW) 
    
    {
      // Botón presionado

      pausa = !pausa;
      Serial.print("Pausa");
      Serial.println(pausa? "Activada" : "Desactivada");
    }
  }

  if (!pausa && millis()-tiempoInicio>=duracionCancion)

  {
    siguienteCancion();

  }

  if (millis()-tiempoPausaMostrada>=1500) 
  {

    tiempoPausaMostrada = millis();
    Serial.print("Pausa:");

    Serial.println(pausa ? "Activada" : "Desactivada");

  }


}
