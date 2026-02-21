const int BUTTON_PIN = 2; 
const int LED1_PIN   = 8;
const int LED2_PIN   = 9;

int ledState = HIGH;         
int currentButtonState = LOW; 
int lastButtonReading = LOW;  

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  digitalWrite(LED1_PIN, ledState);
  digitalWrite(LED2_PIN, !ledState);
}

void loop() {
  int rawReading = digitalRead(BUTTON_PIN);

  if (rawReading != currentButtonState) {
    
    int confidenceCounter = 0;
    for (int i = 0; i < 10; i++) {
      if (digitalRead(BUTTON_PIN) == rawReading) {
        confidenceCounter++;
      }
      delay(5); 
    }

    if (confidenceCounter == 10) {
      currentButtonState = rawReading; 
      
      ledState = !ledState;
      digitalWrite(LED1_PIN, ledState);
      digitalWrite(LED2_PIN, !ledState);
      
      Serial.print("State changed to: ");
      Serial.println(currentButtonState == HIGH ? "PRESSED" : "RELEASED");
    }
  }
}