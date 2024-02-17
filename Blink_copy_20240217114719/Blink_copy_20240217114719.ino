#include <PID_v1.h>
#include <Servo.h>
Servo myservo;
 
#define PIN_TRIG 7 // TRIG ultrasonido  (Amarillo)
#define PIN_ECHO 8 // ECHO ultrasonido (Rojo)
#define PIN_MOT 9 // PWM servo motor (Naranja)
#define Nivel_servo 90 //Posición del servo (0°)

double posicion, Setpoint, Output, error, ServoOutput; 
double Kp=4, Ki=1, Kd=0.3; // Define los valores de Kp, Ki, Kd
PID myPID(&posicion, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
 
 
void setup(){

  Serial.begin(9600);  //Iniciamos la comunicación con el puerto monitor serial

  myservo.attach(PIN_MOT); // Defino como pin de servo
  pinMode(PIN_TRIG, OUTPUT); // Defino como salida
  pinMode(PIN_ECHO, INPUT); // Defino como entrada
  
  Setpoint = 40; //posicion  de referencia de la PELOTA
  posicion = ping(PIN_TRIG, PIN_ECHO);
  
  myservo.write(Nivel_servo); // direccionamos el servo a la posición establecida
  myPID.SetMode(AUTOMATIC); //Inicia el PID 
  myPID.SetOutputLimits(-40,35); // Define sus limite (75°) - CAMBIAR 
  myPID.SetSampleTime(10); // Determinamos que tan rapido se ejecutara nuestro bucle PID
 
}
 
void loop(){
  
    posicion = ping(PIN_TRIG, PIN_ECHO);

   // VER QUE HACE SIN ESTA PARTE
   if (posicion < 220 && posicion > 140) {
      Ki=0.05;
      myPID.SetOutputLimits(-5,2.5);
    } else { 
      myPID.SetOutputLimits(-40,35);  
    }

    if(posicion > 190 || posicion < 170) {
      myPID.Compute(); // Realize una lectura 
      error = Setpoint - posicion; // Se usa para ver que tal alejados estamos de nuestra referencia o SETPOINT.
      ServoOutput = Nivel_servo - Output; 
      myservo.write(ServoOutput); 
    } else {
      myservo.write(Nivel_servo); 
    }
    Serial.print("Distancia en mm:");
    Serial.println(posicion); 
}
 
int ping(int TriggerPin, int EchoPin) {
 
   long distanciaMilimetros;
   delay(3);
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(2);
   digitalWrite(TriggerPin, HIGH); // Habilitamos la lectura del ultrasonido
   delayMicroseconds(5);
   digitalWrite(TriggerPin, LOW); // Apagamos la lectura del ultrasonido
   
   long duracion = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   distanciaMilimetros = duracion * 100 / 292/ 2;   //convertimos la distancia en cm
   
   return distanciaMilimetros; 
}