// #include <Adafruit_NeoPixel.h>
// #include <FS.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>

// const char *SSID = "SSid name";
// const char *PASSWORD = "password";
// WifiServer server(80);
// String header;

// String outputD5State = RED;
// String outputD5State = OFF;

// const int out1 = 23;
// const int out2 = 22;


// void setup()
// {
//     Serial.begin(115200);
//     WIFI.begin(ssid, password);
//     for (int i = 0; i < 64; i++) {

//     }
    
// }
#include <Adafruit_NeoPixel.h>
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* SSID = "SSid name";
const char* PASSWORD = "password";

// 2-dimensional array of row pin numbers:
const int row[8] = {2, 7, 19, 5, 13, 18, 12, 16};

// 2-dimensional array of column pin numbers:
const int col[8] = {6, 11, 10, 3, 17, 4, 8, 9};

// 2-dimensional array of pixels:
int pixels[8][8];

// cursor position:
int x = 5;
int y = 5;

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // initialize the I/O pins as outputs iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that the LEDs are off:
    digitalWrite(col[thisPin], HIGH);
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }
}

void loop() {
  // read input:
  readSensors();

  // draw the screen:
  refreshScreen();
}

void readSensors() {
  // turn off the last position:
  pixels[x][y] = HIGH;
  // read the sensors for X and Y values:
  x = 7 - map(analogRead(D7), 0, 1023, 0, 7);
  y = map(analogRead(D4), 0, 1023, 0, 7);
  // set the new pixel position low so that the LED will turn on in the next
  // screen refresh:
  pixels[x][y] = LOW;
}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}