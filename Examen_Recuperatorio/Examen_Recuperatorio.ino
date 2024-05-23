const int ledRedPin = 4;  
const int ledGreenPin = 5;  
const int resetButtonPin = 2; 
const int enterButtonPin = 3; 

const char* password = "UCB.2024"; 
char inputPassword[9];  //buffer para almacenar la contraseña
int inputIndex = 0; //indice para la posición actual en el buffer

enum State 
{
  ESPERA,
  VERIFICACION,
  ACCESO,
  DENEGAR,
  REINICIO
};

State currentState = ESPERA;

void setup() 
{
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(enterButtonPin, INPUT_PULLUP);

  digitalWrite(ledRedPin, HIGH); 
  digitalWrite(ledGreenPin, LOW); 

  Serial.begin(9600); //uso de Arduino uno
  Serial.println("Ingrese la contraseña:");
}

void loop(){
  switch (currentState) 
  {
    case ESPERA:
      if (Serial.available() > 0){
        char key = Serial.read();
        Serial.print(key); //mostramos caracter

        if (key=='\n') break; //se ignora caracteres de nueva linea

        inputPassword[inputIndex++] =key;

        if (inputIndex >= sizeof(inputPassword) - 1){
          inputPassword[inputIndex] = '\0'; //se termina la cadena
          currentState = VERIFICACION;
        }
      }
      if (digitalRead(resetButtonPin) == LOW){
        currentState = REINICIO;
      }
      break;
    
    case VERIFICACION:
      if (strcmp(inputPassword, password)==0)
      {
        currentState=ACCESO;
      } else{

        currentState=DENEGAR;
      }

      break;
    
    case ACCESO:
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledGreenPin, HIGH);

      Serial.println("\nAcceso concedido");

      delay(5000); //mantenemos el acceso por 5 segundos para simule que la persona pase la puerta
      currentState= REINICIO;

      break;
    
    case DENEGAR:
      Serial.println("\nACCESO DENEGADO");

      delay(2000); //pausamoos por 2 segundos antes de resetear para cerrar nuevamente la puerta
      currentState= REINICIO;
      break;
    
    case REINICIO:
      inputIndex = 0; //se reinicia indice del buffer
      memset(inputPassword,0,sizeof(inputPassword)); // borrams el buffer de contraseña

      digitalWrite(ledRedPin, HIGH); 
      digitalWrite(ledGreenPin, LOW); 

      Serial.println("SISTEMA REINICIADO. Ingrese la Contraseña:");

      currentState = ESPERA;
      break;
  }
}

