#define rojo 2
#define amarillo 4
#define verde 7



typedef enum {
  ROJO,
  AMARILLO,
  VERDE
}semaforo;
semaforo FSM = VERDE;


void setup() 
{
  pinMode(verde, OUTPUT); 
  pinMode(amarillo, OUTPUT);
  pinMode(rojo, OUTPUT); 
}

void loop() 
{

  switch (FSM) 
  {
    case VERDE:
      digitalWrite(verde, HIGH);
      delay(2500);
      digitalWrite(verde, LOW);
      delay(100);
      // cambiamos al siguiente estado
      FSM = AMARILLO;
      break;
      

    case AMARILLO:
      digitalWrite(amarillo, HIGH);
      delay(1250);
      digitalWrite(amarillo, LOW);
      delay(90);

      FSM = ROJO;
      break;


    case ROJO:
      digitalWrite(rojo, HIGH);
      delay(3000);
      digitalWrite(rojo, LOW);
      delay(100);
      FSM = VERDE;
      break;

  }

}
