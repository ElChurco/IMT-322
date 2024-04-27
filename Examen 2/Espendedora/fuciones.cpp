#include "funciones.h"
#include <Arduino.h>

void mostrarBarraDeCarga(int t) {
  const int totalPasos = 30; 
  const int tiempoTotal = t;  
  const int tiempoPorPaso = tiempoTotal / totalPasos;  
  
  Serial.print("Progreso: [");
  for (int i = 0; i < totalPasos; ++i) {
    Serial.print("#");
    delay(tiempoPorPaso);
  }
  Serial.print("] Completo, duracion:");
  Serial.print(tiempoTotal/1000);
  Serial.println("s");
}