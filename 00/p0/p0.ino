int BUTTON_PIN = 7;
int LED_PIN_RED = 8; // red led
int LED_PIN_YLW = 13; // yellow led
int LED_PIN_GRN = 12; // green led

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_YLW, OUTPUT);
  pinMode(LED_PIN_GRN, OUTPUT);

}

void loop() {
  int button_state = digitalRead(BUTTON_PIN);

  if (button_state == HIGH)
  {
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(LED_PIN_YLW, LOW);
    digitalWrite(LED_PIN_GRN, HIGH);
    delay(100);
  }  

  if (button_state == LOW)
  {
    digitalWrite(LED_PIN_GRN, LOW);
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(LED_PIN_YLW, LOW);
    delay(100);

    digitalWrite(LED_PIN_RED, HIGH);
    digitalWrite(LED_PIN_YLW, HIGH);
    delay(100);
  }  
}
