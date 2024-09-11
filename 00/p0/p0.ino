int BUTTON_PIN = 7;
int LED_PIN_RED = 8; // red led
int LED_PIN_YLW = 12; // yellow led
int LED_PIN_GRN = 13; // green led

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_YLW, OUTPUT);
  pinMode(LED_PIN_GRN, OUTPUT);
}

void RED() {
  digitalWrite(LED_PIN_RED, HIGH);
  delay(50);
  digitalWrite(LED_PIN_RED, LOW);
  delay(500);
}

static void YELLOW_RED() {
  digitalWrite(LED_PIN_YLW, HIGH);
  digitalWrite(LED_PIN_RED, HIGH);
  delay(50);
  digitalWrite(LED_PIN_YLW, LOW); 
  digitalWrite(LED_PIN_RED, LOW);
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

  // if (button_state == LOW)
  // {
  //   digitalWrite(LED_PIN_GRN, LOW);
  //   digitalWrite(LED_PIN_RED, LOW);
  //   digitalWrite(LED_PIN_YLW, LOW);
  //   delay(100);

  //   digitalWrite(LED_PIN_RED, HIGH);
  //   digitalWrite(LED_PIN_YLW, HIGH);
  //   delay(100);
  // }  

  // if (button_state == LOW) // bonus 1
  // {
  //   digitalWrite(LED_PIN_GRN, LOW);
  //   digitalWrite(LED_PIN_YLW, HIGH);
  //   delay(100);
  //   digitalWrite(LED_PIN_YLW, LOW);
  //   delay(2000);
  //   digitalWrite(LED_PIN_RED, HIGH);
  //   delay(100);
  //   digitalWrite(LED_PIN_RED, LOW);
  //   delay(2000);
  // }  


  // if (button_state == LOW) // bonus 2
  // {
  //   digitalWrite(LED_PIN_GRN, LOW);
  //   RED();
  //   RED();
  //   RED();
  //   RED();
  //   YELLOW_RED();

  // }   

  // if (button_state == LOW) //bonus 3
  // {
  //   delay(50);
  //   digitalWrite(LED_PIN_GRN, HIGH);
  //   delay(50);
  //   digitalWrite(LED_PIN_YLW, HIGH);
  //   digitalWrite(LED_PIN_GRN, LOW);
  //   delay(50);
  //   digitalWrite(LED_PIN_YLW, LOW);
  //   digitalWrite(LED_PIN_RED, HIGH);
  //   delay(50);
  //   digitalWrite(LED_PIN_RED, LOW);
  //   delay(50);
  // }  

  if (button_state == LOW) //bonus police officer
  {
    int i = 300;
    while (i > 5)
    {
      delay(i);
      digitalWrite(LED_PIN_GRN, HIGH);
      delay(i);
      digitalWrite(LED_PIN_YLW, HIGH);
      digitalWrite(LED_PIN_GRN, LOW);
      delay(i);
      digitalWrite(LED_PIN_YLW, LOW);
      digitalWrite(LED_PIN_RED, HIGH);
      delay(i);
      digitalWrite(LED_PIN_RED, LOW);
      i -= 7;
    }
  }  

  // if (button_state == LOW) //bonus traffic light
  // {
  //   delay(500);
  //   digitalWrite(LED_PIN_YLW, HIGH);
  //   delay(3000);
  //   digitalWrite(LED_PIN_GRN, LOW);
  //   delay(200);
  //   digitalWrite(LED_PIN_RED, HIGH);
  //   delay(1000);
  //   digitalWrite(LED_PIN_YLW, LOW);
  //   delay(10000);
  //   delay(200);
  //   digitalWrite(LED_PIN_YLW, HIGH);
  //   delay(200);
  //   digitalWrite(LED_PIN_RED, LOW);
  //   delay(200);
  //   digitalWrite(LED_PIN_GRN, HIGH);
  //   delay(200);
  //   digitalWrite(LED_PIN_YLW, LOW);
  //   delay(5000);
  // }  

}


// // Flash all LEDs together
// void flashAllLEDs(int delayTime) {
//   digitalWrite(LED_PIN_GRN, HIGH);
//   digitalWrite(LED_PIN_YLW, HIGH);
//   digitalWrite(LED_PIN_RED, HIGH);
//   delay(delayTime);
//   digitalWrite(LED_PIN_GRN, LOW);
//   digitalWrite(LED_PIN_YLW, LOW);
//   digitalWrite(LED_PIN_RED, LOW);
//   delay(delayTime);
// }

// // Flash LEDs one by one in sequence
// void flashLEDsSequence(int delayTime) {
//   digitalWrite(LED_PIN_GRN, HIGH);
//   delay(delayTime);
//   digitalWrite(LED_PIN_GRN, LOW);

//   digitalWrite(LED_PIN_YLW, HIGH);
//   delay(delayTime);
//   digitalWrite(LED_PIN_YLW, LOW);

//   digitalWrite(LED_PIN_RED, HIGH);
//   delay(delayTime);
//   digitalWrite(LED_PIN_RED, LOW);
// }

// // Flash LEDs randomly
// void randomFlashes(int numFlashes, int delayTime) {
//   for (int i = 0; i < numFlashes; i++) {
//     int randomLED = random(LED_PIN_GRN, LED_PIN_RED + 1); // Random pin between GRN, YLW, RED
//     digitalWrite(randomLED, HIGH);
//     delay(delayTime);
//     digitalWrite(randomLED, LOW);
//     delay(delayTime);
//   }
// }

// // Slower chaotic flashes at the beginning
// void slowChaos(int delayTime) {
//   for (int i = 0; i < 10; i++) {
//     randomFlashes(1, delayTime);
//   }
// }

// // Faster, rhythmic flashes toward the end
// void fastChaos(int initialDelay, int finalDelay, int steps) {
//   int delayStep = (initialDelay - finalDelay) / steps;
//   int currentDelay = initialDelay;

//   for (int i = 0; i < steps; i++) {
//     // Decrease delay with each step for faster flashing
//     randomFlashes(1, currentDelay);
//     currentDelay -= delayStep; // Speed up gradually
//   }
// }

// void loop() {
//   int button_state = digitalRead(BUTTON_PIN);

//   // Button not pressed: Default state (Green LED ON)
//   if (button_state == HIGH) {
//     digitalWrite(LED_PIN_RED, LOW);
//     digitalWrite(LED_PIN_YLW, LOW);
//     digitalWrite(LED_PIN_GRN, HIGH);
//     delay(100);
//   } 
//   else if (button_state == LOW) {
//     // Button pressed: Start rhythmic, chaotic light show

//     // 1. Slow beginning with random chaos
//     slowChaos(200);  // Slow random flashes with 200ms delay

//     // 2. Gradual speed-up with rhythmic sequence
//     for (int i = 0; i < 5; i++) {
//       flashLEDsSequence(150 - i * 20); // Gradually decrease delay
//     }

//     // 3. Faster chaos as the light show progresses
//     for (int i = 0; i < 5; i++) {
//       flashAllLEDs(100 - i * 15); // Flash all LEDs with decreasing delay
//     }

//     // 4. End with fast, chaotic random flashes
//     fastChaos(80, 30, 10); // Start with 80ms delay and end with 30ms delay
//   }
// }
