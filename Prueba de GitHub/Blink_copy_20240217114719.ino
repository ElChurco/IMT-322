#define LED1 8
#define LED2 9
#define LED3 10
#define SPEED 200 
#define BOTON 11

bool A = true;

void setup() {

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BOTON, INPUT_PULLUP);

}
void loop() {
  if(digitalRead(BOTON) == 0){ 
    A = !E;
    delay(100);
  }
  if(A == true){
    digitalWrite(LED1, HIGH); 
    delay(SPEED);        

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH); 
    delay(SPEED);

    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH); 
    delay(SPEED);

    digitalWrite(LED3, LOW);
  }
  if(A == false){

    digitalWrite(LED3, HIGH); 
    delay(SPEED);         

    digitalWrite(LED3, LOW);
    digitalWrite(LED2, HIGH); 
    delay(SPEED);

    digitalWrite(LED2, LOW);
    digitalWrite(LED1, HIGH); 
    delay(SPEED);

    digitalWrite(LED1, LOW);
  }             
}