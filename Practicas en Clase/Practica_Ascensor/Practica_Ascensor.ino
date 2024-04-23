#define tiempoEspera 2000

int pisoActual = 1;
int pisoDeseado = 1;

typedef enum{
  ESPERA,
  MOVIMIENTO,
  LLEGADA
}ascensor;
ascensor FSM = ESPERA;


void setup() 
{
    Serial.begin(9600);
    Serial.println("Ascensor en el piso 1.");
    Serial.println("Ingrese un piso para moverse:");
}

void loop() {
    switch (FSM) {
        case ESPERA:
            if (Serial.available() > 0) {
                int entrada = Serial.parseInt();
                if (entrada >= 1 && entrada <= 3) 
                {
                    //se sactualiza piso deseado
                    pisoDeseado = entrada;
                    FSM = MOVIMIENTO;
                } else {
                }
            }
            break;

        case MOVIMIENTO:
            // Estado de movimiento del ascensor
            moverAscensor();
            FSM = LLEGADA;
            break;

        case LLEGADA:
            // Estado de llegada
            Serial.println("Llegó al piso deseado.");
            Serial.println("Ingrese un piso (1-3) para moverse:");
            FSM = ESPERA;
            break;
    }
}

//simulamoción movimiento ascensor
void moverAscensor() 
{
    Serial.print("Moviendo ascensor al piso ");
    Serial.println(pisoDeseado);


    //calculamos la dirección del movimiento (arriba o abajo)
    int direccion = pisoDeseado - pisoActual;


    //el ascensor se mueve piso por piso hasta llegar al piso deseado
    while (pisoActual != pisoDeseado) 
    {
        Serial.print("Piso actual: ");
        Serial.println(pisoActual);

        // Mover el ascensor en la dirección calculada
        pisoActual += (direccion > 0) ? 1 : -1;

        delay(tiempoEspera);
    }
    
}
