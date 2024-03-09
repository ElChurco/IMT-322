#define BUTTON_PIN 2
#define LED_PIN 3

int counter = 0;

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), incrementCounter, FALLING);
}

void loop() 
{
  Serial.println(counter);  
  blinkBuiltInLED();       
}

void incrementCounter() 
{
  counter++;
  toggleLEDState();
}

void blinkBuiltInLED() 
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);     

  digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);
}

void toggleLEDState()
 {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}
