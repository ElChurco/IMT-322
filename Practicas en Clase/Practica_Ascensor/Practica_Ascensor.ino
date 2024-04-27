const int pinBoton = 2;
const int costoBebida1 = 2;
const int costoBebida2 = 7;
const int costoBebida3 = 7;

const int tiempoLlenadoBebida1 = 2000; 
const int tiempoLlenadoBebida2 = 3000; 
const int tiempoLlenadoBebida3 = 4000; 


int dineroDisponible = 0;
int bebidaSeleccionada = 0;
int cambio = 0;

int estadoBoton = 0;

void setup() {
    Serial.begin(9600); //se usó 9600 por el uso de Arduino Uno
    pinMode(pinBoton, INPUT);

    Serial.println("Ingrese el monto de dinero disponible:");
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
    // Si hay una bebida seleccionada
    if (bebidaSeleccionada > 0) {
        procesarBebida();
    } else {
        // Espera la selección de bebida
        if (Serial.available() > 0) {
            bebidaSeleccionada = Serial.parseInt();
        }
    }
}

void mostrarMenu() {
    Serial.println("\nSeleccione una bebida:");
    Serial.println("1. Bebida 1 - Precio: 2");
    Serial.println("2. Bebida 2 - Precio: 7");
    Serial.println("3. Bebida 3 - Precio: 7");
}

void procesarBebida() {
    switch (bebidaSeleccionada) {
        case 1:
            if (dineroDisponible >= costoBebida1) {
                ejecutarCompra(costoBebida1, tiempoLlenadoBebida1, "Bebida 1");
            } else {
                Serial.println("Dinero insuficiente para la Bebida 1.");
                bebidaSeleccionada = 0;
            }
            break;
        case 2:
            if (dineroDisponible >= costoBebida2) {
                ejecutarCompra(costoBebida2, tiempoLlenadoBebida2, "Bebida 2");
            } else {
                Serial.println("Dinero insuficiente para la Bebida 2.");
                bebidaSeleccionada = 0;
            }
            break;
        case 3:
            if (dineroDisponible >= costoBebida3) {
                ejecutarCompra(costoBebida3, tiempoLlenadoBebida3, "Bebida 3");
            } else {
                Serial.println("Dinero insuficiente para la Bebida 3.");
                bebidaSeleccionada = 0;
            }
            break;
        default:
            Serial.println("Opción no válida. Por favor, seleccione una bebida válida.");
            bebidaSeleccionada = 0;
    }

    if (bebidaSeleccionada > 0) {
        Serial.print("Cambio devuelto: ");
        Serial.println(cambio);

        //esperamos a que el usuario retire el vaso presionando el botón
        esperarRetiroVaso();
        
        mostrarMenu();
    }
}

void ejecutarCompra(int costo, int tiempoLlenado, String bebida) {
    cambio = dineroDisponible - costo;
    Serial.print("Preparando ");
    Serial.print(bebida);
    Serial.println("...");
    delay(tiempoLlenado);
    Serial.println(bebida + " lista. Operación completada.");
    dineroDisponible -= costo;
}

void esperarRetiroVaso() {
    Serial.println("Presione el botón para retirar el vaso.");
    while (true) {
        estadoBoton = digitalRead(pinBoton);
        if (estadoBoton == HIGH) {
            Serial.println("Vaso retirado. Gracias por su compra.");
            bebidaSeleccionada = 0;
            cambio = 0;
            break;
        }
    }
}
