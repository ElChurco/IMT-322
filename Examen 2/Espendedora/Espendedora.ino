#define pinBoton 2
#define costoBebida1 2
#define costoBebida2 5
#define costoBebida3 7
#define tiempoLlenadoBebida1 2000
#define tiempoLlenadoBebida2 3000
#define tiempoLlenadoBebida3 4000

int dineroDisponible = 0;
int bebidaSeleccionada = 0;
int cambio = 0;
int estadoBoton = 0;

typedef enum{
    BEBIDA1,
    BEBIDA2,
    BEBIDA3,
    FINALIZAR
} maquina;
maquina FSM;

void setup() {
    Serial.begin(9600); //9600 por Arduino Uno
    pinMode(pinBoton, INPUT);

    Serial.println("Cuánto dinero dispone?:");
    while (dineroDisponible == 0) {
        if (Serial.available() > 0) {
            dineroDisponible = Serial.parseInt();
            Serial.print("Dinero disponible: ");
            Serial.println(dineroDisponible);
        }
    }

    mostrarMenu();
}

void loop() {
    //si hay bebida seleccionada
    if (bebidaSeleccionada > 0){
        //actualizamos el estado según bebida seleccionada
        FSM = static_cast<maquina>(bebidaSeleccionada-1);
        procesarBebida();
    } else {

        //esperamos la selección de bebida
        if (Serial.available() > 0){

            bebidaSeleccionada = Serial.parseInt();
        }

    }
}

void mostrarMenu()
{
    Serial.println("\nSeleccione una bebida:");
    Serial.println("1. KARPIL - Precio: 2");
    Serial.println("2. POWERRADE - Precio: 7");
    Serial.println("3. RED BULL - Precio: 7");
    Serial.println("4. Finalizar el programa");


}

void procesarBebida()
{
    switch (FSM){
        case BEBIDA1:
            if (dineroDisponible >= costoBebida1){
                ejecutarCompra(costoBebida1, tiempoLlenadoBebida1, "KARPIL");
            } else {
                Serial.println("Dinero insuficiente para KARPIL.");
                bebidaSeleccionada=0;
            }
            break;
        case BEBIDA2:
            if (dineroDisponible >= costoBebida2) {
                ejecutarCompra(costoBebida2, tiempoLlenadoBebida2, "POWERRADE");
            } else {
                Serial.println("Dinero insuficiente para POWERRADE.");
                bebidaSeleccionada=0;
            }
            break;
        case BEBIDA3:
            if (dineroDisponible >= costoBebida3) {
                ejecutarCompra(costoBebida3, tiempoLlenadoBebida3, "RED BULL");
            } else {
                Serial.println("Dinero insuficiente para RED BULL.");
                bebidaSeleccionada=0;
            }

            break;

        case FINALIZAR:
            Serial.println("Finalizando el programa. Gracias por su participación.");
            bebidaSeleccionada = 0;
            //termina loop
            while (true){
            }
            break;
        default:
            Serial.println("Opción no válida. Por favor, seleccione una bebida válida.");
            bebidaSeleccionada = 0;
    }

    if (bebidaSeleccionada > 0) {
        Serial.print("Cambio devuelto: ");
        Serial.println(cambio);


        //esperamos usuario retire el vaso con botón
        esperarRetiroVaso();
        
        mostrarMenu();
    }
}

void ejecutarCompra(int costo, int tiempoLlenado, String bebida){
    cambio =dineroDisponible-costo;
    Serial.print("Preparando ");
    Serial.print(bebida);
    Serial.println("...");

    delay(tiempoLlenado);
    Serial.println(bebida+" lista.");
    dineroDisponible-=costo;
}

void esperarRetiroVaso(){
    Serial.println("Presione el botón para retirar el vaso.");
    while (true){
        estadoBoton = digitalRead(pinBoton);
        if (estadoBoton == HIGH){

            // Botón presionado
            Serial.println("Operación completada. Gracias por su compra.");
            bebidaSeleccionada = 0;
            cambio = 0;

            break;
        }

    }

}
